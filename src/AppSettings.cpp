// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#include "AppSettings.h"

#include <QJSEngine>
#include <QTime>

namespace {

constexpr auto kRestoreRunningKey = "restoreTaskSwitchStateAtStartUp";
constexpr auto kPauseOnLockKey = "pauseOnScreenLock";
constexpr auto kDailyWorkingTimeKey = "dailyWorkingTime";
constexpr auto kThemeKey = "theme";
constexpr auto kTimeFormat = "hh:mm:ss";
const QString kDefaultDailyWorkingTime = QStringLiteral("08:00:00");

}  // namespace

AppSettings::AppSettings(QObject *parent) : QObject(parent) {
    Q_ASSERT(!sInstance);
    sInstance = this;
}

AppSettings::~AppSettings() {
    sInstance = nullptr;
}

AppSettings *AppSettings::create(QQmlEngine *, QJSEngine *) {
    Q_ASSERT(sInstance);
    QJSEngine::setObjectOwnership(sInstance, QJSEngine::CppOwnership);
    return sInstance;
}

bool AppSettings::restoreRunningOnStartup() const {
    return mSettings.value(kRestoreRunningKey, false).toBool();
}

void AppSettings::setRestoreRunningOnStartup(bool enabled) {
    if (enabled == restoreRunningOnStartup())
        return;

    mSettings.setValue(kRestoreRunningKey, enabled);
    emit restoreRunningOnStartupChanged();
}

bool AppSettings::pauseOnScreenLock() const {
    return mSettings.value(kPauseOnLockKey, true).toBool();
}

void AppSettings::setPauseOnScreenLock(bool enabled) {
    if (enabled == pauseOnScreenLock())
        return;

    mSettings.setValue(kPauseOnLockKey, enabled);
    emit pauseOnScreenLockChanged();
}

QString AppSettings::dailyWorkingTime() const {
    const QString value = mSettings.value(kDailyWorkingTimeKey).toString();
    return QTime::fromString(value, kTimeFormat).isValid() ? value : kDefaultDailyWorkingTime;
}

void AppSettings::setDailyWorkingTime(const QString &time) {
    const QTime parsed = QTime::fromString(time, kTimeFormat);
    if (!parsed.isValid() || time == dailyWorkingTime())
        return;

    mSettings.setValue(kDailyWorkingTimeKey, parsed.toString(kTimeFormat));
    emit dailyWorkingTimeChanged();
}

qint64 AppSettings::dailyWorkingSeconds() const {
    return QTime(0, 0).secsTo(QTime::fromString(dailyWorkingTime(), kTimeFormat));
}

AppSettings::Theme AppSettings::theme() const {
    const int value = mSettings.value(kThemeKey, int(Theme::System)).toInt();
    if (value < int(Theme::System) || value > int(Theme::Dark))
        return Theme::System;
    return Theme(value);
}

void AppSettings::setTheme(Theme theme) {
    if (theme == this->theme())
        return;

    mSettings.setValue(kThemeKey, int(theme));
    emit themeChanged();
}

QString AppSettings::version() const {
    return QStringLiteral(QTASKSMANAGER_VERSION);
}
