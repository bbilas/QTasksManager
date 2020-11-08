// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#include "WorkPackagesManager.h"
#include <QDebug>
#include <QDateTime>

WorkPackagesManager::WorkPackagesManager(WorkPackagesModel *model) : QObject(),
    mWorkPackagesModel(model),
    mOverHoursMessagePupUpShowed(false) {
    mDailyWorkingTime.setHMS(8, 0, 0); // TODO: add possibility to change these values via the settings screen // default 08:00:00h
    mActivityTimeTimer.reset(new QTimer);
    mActivityTimeTimer->setInterval(1000);
    mActivityTimeTimer->start();
    connect(mActivityTimeTimer.data(), SIGNAL(timeout()), this, SLOT(onUpdateActivityTime()));
}

void WorkPackagesManager::onUpdateActivityTime() {
    const WorkPackagesList *workPackagesList = mWorkPackagesModel->getWorkPackagesList();
    for (int i = 0; i < workPackagesList->size(); i++) {
        WorkPackage *workPackage = workPackagesList->at(i);
        int activityTime = workPackage->activityTime() + mActivityTimeTimer->interval() / 1000;
        if (workPackage->timerState()) {
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
