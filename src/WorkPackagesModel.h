// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#ifndef WORKPACKAGESMODEL_H_
#define WORKPACKAGESMODEL_H_

#include <QAbstractListModel>
#include <QTimer>
#include <QSettings>
#include "WorkPackage.h"
#include "UserSettings.h"

typedef QList<WorkPackage*> WorkPackagesList;
typedef QList<WorkPackageDescription> WorkPackagesDescription;

class WorkPackagesModel : public QAbstractListModel {
    Q_OBJECT

 public:
    explicit WorkPackagesModel(QObject *parent = nullptr);
    ~WorkPackagesModel();

    enum {
        ProjectName = Qt::UserRole + 1,
        TaskName,
        ActivityTime,
        TimerState,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE bool reloadActivityTime(int idx);
    Q_INVOKABLE bool addNewEmptyTask(void);
    Q_INVOKABLE bool removeWorkPackage(int idx);

 public slots:
    void onTimerTimeouted();

 private:
    void loadData();
    void saveData();

    WorkPackagesList mWorkPackages;
    QScopedPointer<QTimer> mTimer;
    UserSettings mUserSettings;

};

QDataStream& operator<<(QDataStream& out, const WorkPackagesDescription& v);
QDataStream& operator>>(QDataStream& in, WorkPackagesDescription& v);

Q_DECLARE_METATYPE(WorkPackagesDescription)

#endif  // WORKPACKAGESMODEL_H_
