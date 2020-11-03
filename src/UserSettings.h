// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include <QSettings>
#include <QObject>

class UserSettings : public QSettings {
    Q_OBJECT

    Q_PROPERTY(bool taskSwitchStateAtStartUp READ restoreTaskSwitchStateAtStartUp WRITE setTaskSwitchStateAtStartUp NOTIFY taskSwitchStateAtStartUpChanged)

 public:
    explicit UserSettings(QObject* parent = nullptr);

    bool restoreTaskSwitchStateAtStartUp() const;
    void setTaskSwitchStateAtStartUp(const bool enabled = false);

 signals:
    void taskSwitchStateAtStartUpChanged();
};

#endif // USERSETTINGS_H
