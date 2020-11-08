// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include <QSettings>
#include <QObject>

class UserSettings : public QSettings {
    Q_OBJECT

    Q_PROPERTY(bool taskSwitchStateAtStartUp READ restoreTaskSwitchStateAtStartUp WRITE setTaskSwitchStateAtStartUp NOTIFY taskSwitchStateAtStartUpChanged)
    Q_PROPERTY(QString dailyWorkingTime READ dailyWorkingTime WRITE setDailyWorkingTime NOTIFY dailyWorkingTimeChanged)

 public:
    explicit UserSettings(QObject* parent = nullptr);

    bool restoreTaskSwitchStateAtStartUp() const;
    void setTaskSwitchStateAtStartUp(const bool enabled = false);
    QString dailyWorkingTime() const;
    void setDailyWorkingTime(const QString &dailyWorkingTime);

 signals:
    void taskSwitchStateAtStartUpChanged();
    void dailyWorkingTimeChanged(int hour, int minute, int seconds);
};

#endif // USERSETTINGS_H
