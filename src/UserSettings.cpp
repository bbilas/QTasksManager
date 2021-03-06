// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#include <QDateTime>
#include "UserSettings.h"

#define DEFAULT_DAILY_WORKING_TIME  QStringLiteral("08:00:00")

UserSettings::UserSettings(QObject* parent) : QSettings(parent) {
}

bool UserSettings::restoreTaskSwitchStateAtStartUp() const {
    return value("restoreTaskSwitchStateAtStartUp", false).toBool();
}

void UserSettings::setTaskSwitchStateAtStartUp(const bool enabled) {
    setValue("restoreTaskSwitchStateAtStartUp", QVariant::fromValue(enabled));
    emit taskSwitchStateAtStartUpChanged();
}

QString UserSettings::dailyWorkingTime() const {
    return value("dailyWorkingTime", DEFAULT_DAILY_WORKING_TIME).toString();
}

void UserSettings::setDailyWorkingTime(const QString &dailyWorkingTime) {
    QTime time = QDateTime::fromString(dailyWorkingTime, "hh:mm:ss").time();
    if (time.isValid() == false)
        return;

    setValue("dailyWorkingTime", QVariant::fromValue(time.toString("hh:mm:ss")));
    emit dailyWorkingTimeChanged(time.hour(), time.minute(), time.second());
}
