// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#ifndef WORKPACKAGESMANAGER_H
#define WORKPACKAGESMANAGER_H

#include <QObject>
#include <QScopedPointer>
#include <QTimer>
#include <QTime>
#include "WorkPackagesModel.h"
#include "UserSettings.h"

class WorkPackagesManager : public QObject {
    Q_OBJECT

 public:
   explicit WorkPackagesManager(WorkPackagesModel *model);

 signals:
   void overHoursDetected(const QString &activityTime);

 public slots:
   void onUpdateActivityTime();
   void onSetDailyWorkingTime(int hour, int minute, int seconds);

 private:
   bool isDailyWorkingTimeExceeded(const QTime &totalActivityTime);
   void showOverHoursMessagePopUp(const QString &totalActivityTime);

   QScopedPointer<QTimer> mActivityTimeTimer;
   UserSettings mUserSettings;
   WorkPackagesModel *mWorkPackagesModel;
   QTime mDailyWorkingTime;
   bool mOverHoursMessagePupUpShowed;

};

#endif // WORKPACKAGESMANAGER_H
