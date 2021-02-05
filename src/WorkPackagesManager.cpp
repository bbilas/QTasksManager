// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#include "WorkPackagesManager.h"
#include <QDebug>
#include <QDateTime>

WorkPackagesManager::WorkPackagesManager(WorkPackagesModel *model) : QObject(),
    mWorkPackagesModel(model),
    mOverHoursMessagePupUpShowed(false) {
    QTime dailyWorkingTime = QTime::fromString(mUserSettings.dailyWorkingTime(), "hh:mm:ss");
    onSetDailyWorkingTime(dailyWorkingTime.hour(), dailyWorkingTime.minute(), dailyWorkingTime.second());
    mActivityTimeTimer.reset(new QTimer);
    mActivityTimeTimer->setInterval(1000);
    mActivityTimeTimer->start();
    connect(mActivityTimeTimer.data(), SIGNAL(timeout()), this, SLOT(onUpdateActivityTime()));
    connect(&mScreenSaver, &ScreenSaver::activeChanged, this, &WorkPackagesManager::onScreenSaverActiveChanged);
}

void WorkPackagesManager::onUpdateActivityTime() {
    const WorkPackagesList *workPackagesList = mWorkPackagesModel->getWorkPackagesList();
    for (int i = 0; i < workPackagesList->size(); i++) {
        WorkPackage *workPackage = workPackagesList->at(i);
        int activityTime = workPackage->activityTime() + mActivityTimeTimer->interval() / 1000;
        if (workPackage->active()) {
            mWorkPackagesModel->setData(mWorkPackagesModel->index(i, 0), activityTime, WorkPackagesModel::ActivityTime);
        }
    }

    QTime totalActivityTime = QDateTime::fromString(mWorkPackagesModel->totalActivityTime(), "hh:mm:ss").time();
    if (isDailyWorkingTimeExceeded(totalActivityTime))
        showOverHoursMessagePopUp(totalActivityTime.toString("hh:mm:ss"));
}

bool WorkPackagesManager::isDailyWorkingTimeExceeded(const QTime &totalActivityTime) {
    return totalActivityTime > mDailyWorkingTime;
}

void WorkPackagesManager::showOverHoursMessagePopUp(const QString &totalActivityTime) {
    if (mOverHoursMessagePupUpShowed)   // prevent to show it multiple times
        return;

    emit overHoursDetected(totalActivityTime);
    mOverHoursMessagePupUpShowed = true;
}

void WorkPackagesManager::onSetDailyWorkingTime(int hour, int minute, int seconds) {
    if (mDailyWorkingTime.setHMS(hour, minute, seconds) == false)
        return;

    mOverHoursMessagePupUpShowed = false;
}

void WorkPackagesManager::onScreenSaverActiveChanged(bool active) {
    static QList<bool> workPackagesStates;
    const WorkPackagesList *workPackagesList = mWorkPackagesModel->getWorkPackagesList();

    for (int i = 0; i < workPackagesList->size(); i++) {
        if (active) {
            workPackagesStates.insert(i, workPackagesList->at(i)->active());
            mWorkPackagesModel->setData(mWorkPackagesModel->index(i, 0), false, WorkPackagesModel::Active);
        } else {
            mWorkPackagesModel->setData(mWorkPackagesModel->index(i, 0), workPackagesStates.at(i), WorkPackagesModel::Active);
        }
    }
}
