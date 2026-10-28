// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#include "ScreenLockMonitor.h"

#include <QDBusConnection>
#include <QDBusConnectionInterface>
#include <QDBusMessage>
#include <QDBusObjectPath>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QLoggingCategory>
#include <unistd.h>

Q_LOGGING_CATEGORY(lcScreenLock, "qtasksmanager.screenlock")

namespace {

struct ScreenSaverEndpoint {
    const char *service;
    const char *path;
    const char *interface;
};

constexpr ScreenSaverEndpoint kCinnamon = {"org.cinnamon.ScreenSaver", "/org/cinnamon/ScreenSaver",
                                           "org.cinnamon.ScreenSaver"};

constexpr ScreenSaverEndpoint kScreenSavers[] = {
    kCinnamon,
    {"org.gnome.ScreenSaver", "/org/gnome/ScreenSaver", "org.gnome.ScreenSaver"},
    {"org.freedesktop.ScreenSaver", "/org/freedesktop/ScreenSaver", "org.freedesktop.ScreenSaver"},
    {"org.freedesktop.ScreenSaver", "/ScreenSaver", "org.freedesktop.ScreenSaver"},
};

constexpr auto kLogindService = "org.freedesktop.login1";
constexpr auto kLogindManagerPath = "/org/freedesktop/login1";
constexpr auto kLogindManagerInterface = "org.freedesktop.login1.Manager";
constexpr auto kLogindSessionInterface = "org.freedesktop.login1.Session";
constexpr auto kPropertiesInterface = "org.freedesktop.DBus.Properties";
constexpr int kLogindTimeoutMs = 2000;

}  // namespace

ScreenLockMonitor::ScreenLockMonitor(QObject *parent) : QObject(parent) {
    connectScreenSavers();
    connectLogind();
    queryCinnamonState();
}

bool ScreenLockMonitor::isLocked() const {
    return mLocked;
}

void ScreenLockMonitor::connectScreenSavers() {
    QDBusConnection bus = QDBusConnection::sessionBus();
    if (!bus.isConnected()) {
        qCWarning(lcScreenLock) << "Session bus unavailable, screen lock detection disabled";
        return;
    }

    for (const ScreenSaverEndpoint &endpoint : kScreenSavers) {
        // An empty service matches any sender, so the subscription survives the
        // screensaver process being started, restarted or replaced.
        const bool ok = bus.connect(QString(), endpoint.path, endpoint.interface,
                                    QStringLiteral("ActiveChanged"), this,
                                    SLOT(onScreenSaverActiveChanged(bool)));
        if (!ok)
            qCWarning(lcScreenLock) << "Cannot subscribe to" << endpoint.interface << bus.lastError().message();
    }
}

void ScreenLockMonitor::connectLogind() {
    QDBusConnection bus = QDBusConnection::systemBus();
    if (!bus.isConnected())
        return;

    QDBusMessage call = QDBusMessage::createMethodCall(kLogindService, kLogindManagerPath,
                                                       kLogindManagerInterface,
                                                       QStringLiteral("GetSessionByPID"));
    call << quint32(::getpid());
    const QDBusMessage reply = bus.call(call, QDBus::Block, kLogindTimeoutMs);
    if (reply.type() != QDBusMessage::ReplyMessage || reply.arguments().isEmpty()) {
        qCDebug(lcScreenLock) << "No logind session found:" << reply.errorMessage();
        return;
    }

    const QString sessionPath = reply.arguments().constFirst().value<QDBusObjectPath>().path();
    bus.connect(kLogindService, sessionPath, kLogindSessionInterface, QStringLiteral("Lock"),
                this, SLOT(onSessionLock()));
    bus.connect(kLogindService, sessionPath, kLogindSessionInterface, QStringLiteral("Unlock"),
                this, SLOT(onSessionUnlock()));
    bus.connect(kLogindService, sessionPath, kPropertiesInterface, QStringLiteral("PropertiesChanged"),
                this, SLOT(onSessionPropertiesChanged(QString, QVariantMap, QStringList)));
}

void ScreenLockMonitor::queryCinnamonState() {
    QDBusConnection bus = QDBusConnection::sessionBus();
    if (!bus.isConnected() || !bus.interface()->isServiceRegistered(kCinnamon.service))
        return;

    QDBusMessage call = QDBusMessage::createMethodCall(kCinnamon.service, kCinnamon.path,
                                                       kCinnamon.interface, QStringLiteral("GetActive"));
    // Never spawn the screensaver just to ask whether it is active.
    call.setAutoStartService(false);

    auto *watcher = new QDBusPendingCallWatcher(bus.asyncCall(call), this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this, [this](QDBusPendingCallWatcher *w) {
        const QDBusPendingReply<bool> reply = *w;
        if (reply.isValid())
            setLocked(reply.value());
        w->deleteLater();
    });
}

void ScreenLockMonitor::onScreenSaverActiveChanged(bool active) {
    qCDebug(lcScreenLock) << "Screensaver active:" << active;
    setLocked(active);
}

void ScreenLockMonitor::onSessionLock() {
    qCDebug(lcScreenLock) << "logind: session locked";
    setLocked(true);
}

void ScreenLockMonitor::onSessionUnlock() {
    qCDebug(lcScreenLock) << "logind: session unlocked";
    setLocked(false);
}

void ScreenLockMonitor::onSessionPropertiesChanged(const QString &interface, const QVariantMap &changed,
                                                   const QStringList &invalidated) {
    Q_UNUSED(invalidated);
    if (interface != QLatin1String(kLogindSessionInterface))
        return;

    const auto it = changed.constFind(QStringLiteral("LockedHint"));
    if (it != changed.constEnd()) {
        qCDebug(lcScreenLock) << "logind: LockedHint" << it->toBool();
        setLocked(it->toBool());
    }
}

void ScreenLockMonitor::setLocked(bool locked) {
    if (mLocked == locked)
        return;

    mLocked = locked;
    emit lockedChanged(locked);
}
