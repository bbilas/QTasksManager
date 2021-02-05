// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#ifndef WORKPACKAGESMODEL_H_
#define WORKPACKAGESMODEL_H_

#include <QAbstractListModel>
#include <QSettings>
#include "WorkPackage.h"
#include "UserSettings.h"

typedef QList<WorkPackage*> WorkPackagesList;
typedef QList<WorkPackageDescription> WorkPackagesDescription;

class WorkPackagesModel : public QAbstractListModel {
    Q_OBJECT

    Q_PROPERTY(QString totalActivityTime READ totalActivityTime NOTIFY totalActivityTimeChanged)

 public:
    explicit WorkPackagesModel(QObject *parent = nullptr);
    ~WorkPackagesModel();

    enum {
        ProjectName = Qt::UserRole + 1,
        TaskName,
        ActivityTime,
        Active,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE bool reloadActivityTime(int idx);
    Q_INVOKABLE bool addNewEmptyTask(void);
    Q_INVOKABLE bool removeWorkPackage(int idx);

    QString totalActivityTime() const;
    const WorkPackagesList *getWorkPackagesList();

 signals:
    void totalActivityTimeChanged();

 private:
    void loadData();
    void saveData();

    WorkPackagesList mWorkPackages;
    UserSettings mUserSettings;

};

QDataStream& operator<<(QDataStream& out, const WorkPackagesDescription& v);
QDataStream& operator>>(QDataStream& in, WorkPackagesDescription& v);

Q_DECLARE_METATYPE(WorkPackagesDescription)

#endif  // WORKPACKAGESMODEL_H_
