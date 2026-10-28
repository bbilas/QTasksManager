// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QObject>
#include <QSettings>
#include <QtQml/qqmlregistration.h>

class QJSEngine;
class QQmlEngine;

class AppSettings : public QObject {
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(bool restoreRunningOnStartup READ restoreRunningOnStartup WRITE setRestoreRunningOnStartup NOTIFY restoreRunningOnStartupChanged)
    Q_PROPERTY(bool pauseOnScreenLock READ pauseOnScreenLock WRITE setPauseOnScreenLock NOTIFY pauseOnScreenLockChanged)
    Q_PROPERTY(QString dailyWorkingTime READ dailyWorkingTime WRITE setDailyWorkingTime NOTIFY dailyWorkingTimeChanged)
    Q_PROPERTY(qint64 dailyWorkingSeconds READ dailyWorkingSeconds NOTIFY dailyWorkingTimeChanged)
    Q_PROPERTY(Theme theme READ theme WRITE setTheme NOTIFY themeChanged)
    Q_PROPERTY(QString version READ version CONSTANT)

 public:
    enum class Theme { System, Light, Dark };
    Q_ENUM(Theme)

    // Not default-constructible on purpose: QML must use create() to get the
    // instance owned by main() instead of constructing its own.
    explicit AppSettings(QObject *parent);
    ~AppSettings() override;

    static AppSettings *create(QQmlEngine *, QJSEngine *);

    bool restoreRunningOnStartup() const;
    void setRestoreRunningOnStartup(bool enabled);

    bool pauseOnScreenLock() const;
    void setPauseOnScreenLock(bool enabled);

    QString dailyWorkingTime() const;
    void setDailyWorkingTime(const QString &time);
    qint64 dailyWorkingSeconds() const;

    Theme theme() const;
    void setTheme(Theme theme);

    QString version() const;

 signals:
    void restoreRunningOnStartupChanged();
    void pauseOnScreenLockChanged();
    void dailyWorkingTimeChanged();
    void themeChanged();

 private:
    QSettings mSettings;
    static inline AppSettings *sInstance = nullptr;
};

#endif  // APPSETTINGS_H
