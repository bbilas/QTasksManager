// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#include <QQmlEngine>
#include "WorkPackage.h"

WorkPackage::WorkPackage(QObject *parent) : QObject(parent) {
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

WorkPackage::WorkPackage(const WorkPackage &other) : QObject(NULL) {
    memcpy(&mConfig, &other.mConfig, sizeof(mConfig));
}

WorkPackage::~WorkPackage() {
}

QString WorkPackage::projectName() const {
    return mConfig.projectName;
}

void WorkPackage::setProjectName(const QString &projectName) {
    mConfig.projectName = projectName;
    emit projectNameChanged();
}

QString WorkPackage::taskName() const {
    return mConfig.taskName;
}

void WorkPackage::setTaskName(const QString &taskName) {
    mConfig.taskName = taskName;
    emit taskNameChanged();
}

int WorkPackage::activityTime() const {
    return mConfig.activityTime;
}

void WorkPackage::setActivityTime(const int activityTime) {
    mConfig.activityTime = activityTime;
    emit activityTimeChanged();
}

bool WorkPackage::timerState() const {
    return mConfig.timerState;
}

void WorkPackage::setTimerState(const bool timerState) {
    mConfig.timerState = timerState;
    emit timerStateChanged();
}

const WorkPackageDescription* WorkPackage::config() {
    return &mConfig;
}

QDataStream &operator<<(QDataStream &out, const WorkPackageDescription &v) {
    out << v.projectName << v.taskName << v.activityTime << v.timerState;
    return out;
}

QDataStream &operator>>(QDataStream &in, WorkPackageDescription &v) {
    in >> v.projectName >> v.taskName >> v.activityTime >> v.timerState;
    return in;
}
