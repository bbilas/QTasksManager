// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#include "WorkPackagesManager.h"
#include <QDebug>
#include <QDateTime>

WorkPackagesManager::WorkPackagesManager(WorkPackagesModel *model) : QObject(),
    mWorkPackagesModel(model) {
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
}
