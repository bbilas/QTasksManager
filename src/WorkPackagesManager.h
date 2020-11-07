// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#ifndef WORKPACKAGESMANAGER_H
#define WORKPACKAGESMANAGER_H

#include <QObject>
#include <QScopedPointer>
#include <QTimer>
#include "WorkPackagesModel.h"

class WorkPackagesManager : public QObject {
    Q_OBJECT

 public:
   explicit WorkPackagesManager(WorkPackagesModel *model);

 public slots:
   void onUpdateActivityTime();

 private:
   QScopedPointer<QTimer> mActivityTimeTimer;
   WorkPackagesModel *mWorkPackagesModel;

};

#endif // WORKPACKAGESMANAGER_H
