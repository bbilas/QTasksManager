// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#ifndef SCREENLOCKMONITOR_H
#define SCREENLOCKMONITOR_H

#include <QObject>
#include <QVariantMap>

// Tracks whether the session is locked / the screensaver is active.
//
// Signals are subscribed without binding to a bus name owner, because
// cinnamon-screensaver is D-Bus activated: it is usually not running when the
// application starts and is re-spawned on every lock. Several sources are
// listened to (Cinnamon, freedesktop/GNOME screensavers and logind); their
// edges are merged into a single de-duplicated lockedChanged() signal.
class ScreenLockMonitor : public QObject {
    Q_OBJECT

 public:
    explicit ScreenLockMonitor(QObject *parent = nullptr);

    bool isLocked() const;

 signals:
    void lockedChanged(bool locked);

 private slots:
    void onScreenSaverActiveChanged(bool active);
    void onSessionLock();
    void onSessionUnlock();
    void onSessionPropertiesChanged(const QString &interface, const QVariantMap &changed,
                                    const QStringList &invalidated);

 private:
    void connectScreenSavers();
    void connectLogind();
    void queryCinnamonState();
    void setLocked(bool locked);

    bool mLocked = false;
};

#endif  // SCREENLOCKMONITOR_H
