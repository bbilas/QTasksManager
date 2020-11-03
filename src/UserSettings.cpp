// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#include "UserSettings.h"

UserSettings::UserSettings(QObject* parent) : QSettings(parent) {
}

bool UserSettings::restoreTaskSwitchStateAtStartUp() const {
    return value("restoreTaskSwitchStateAtStartUp", false).toBool();
}

void UserSettings::setTaskSwitchStateAtStartUp(const bool enabled) {
    setValue("restoreTaskSwitchStateAtStartUp", QVariant::fromValue(enabled));
    emit taskSwitchStateAtStartUpChanged();
}
