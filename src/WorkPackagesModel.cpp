// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#include <QDateTime>
#include "WorkPackagesModel.h"

WorkPackagesModel::WorkPackagesModel(QObject *parent)
    : QAbstractListModel(parent) {
    loadData();
}

WorkPackagesModel::~WorkPackagesModel() {
    for (WorkPackage *workPackage : mWorkPackages) {
        workPackage->deleteLater();
    }
}

int WorkPackagesModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;

    return mWorkPackages.size();
}

QVariant WorkPackagesModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    WorkPackage *workPackage = mWorkPackages.at(index.row());

    switch (role) {
    case ProjectName:
        return QVariant::fromValue(workPackage->projectName());
    case TaskName:
        return QVariant::fromValue(workPackage->taskName());
    case ActivityTime:
        return QVariant::fromValue(QDateTime::fromSecsSinceEpoch(workPackage->activityTime()).toUTC().toString("hh:mm:ss"));
    case Active:
        return QVariant::fromValue(workPackage->active());
    }

    return QVariant();
}

bool WorkPackagesModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (data(index, role) != value) {
        if (index.row() > mWorkPackages.size())
            return false;

        WorkPackage *workPackage = mWorkPackages.at(index.row());

        switch (role) {
        case ProjectName:
            workPackage->setProjectName(QVariant(value).toString());
            break;
        case TaskName:
            workPackage->setTaskName(QVariant(value).toString());
            break;
        case ActivityTime:
            workPackage->setActivityTime(QVariant(value).toInt());
            emit totalActivityTimeChanged();
            break;
        case Active:
            workPackage->setActive(QVariant(value).toBool());
            break;
        }

        saveData();
        emit dataChanged(index, index, QVector<int>() << role);

        return true;
    }

    return false;
}

Qt::ItemFlags WorkPackagesModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> WorkPackagesModel::roleNames() const {
    QHash<int, QByteArray> names;
    names[ProjectName] = "projectName";
    names[TaskName] = "taskName";
    names[ActivityTime] = "activityTime";
    names[Active] = "active";

    return names;
}

bool WorkPackagesModel::removeWorkPackage(int idx) {
    if (idx < 0 || idx > mWorkPackages.size())
        return false;

    beginRemoveRows(QModelIndex(), idx, idx);
    mWorkPackages.removeAt(idx);
    endRemoveRows();
    saveData();

    return true;
}

QString WorkPackagesModel::totalActivityTime() const {
    int totalActivityTime = 0;
    for (const auto &item : mWorkPackages)
        totalActivityTime += item->activityTime();

    return QDateTime::fromSecsSinceEpoch(totalActivityTime).toUTC().toString("hh:mm:ss");
}

const WorkPackagesList *WorkPackagesModel::getWorkPackagesList() {
    return &mWorkPackages;
}

bool WorkPackagesModel::addNewEmptyTask(void) {
    beginInsertRows(QModelIndex(), mWorkPackages.size(), mWorkPackages.size());
    WorkPackage *workPackage = new WorkPackage;
    Q_ASSERT(workPackage != nullptr);
    mWorkPackages.append(workPackage);
    endInsertRows();

    return true;
}

bool WorkPackagesModel::reloadActivityTime(int idx) {
    if (idx < 0 || idx > mWorkPackages.size())
        return false;

    setData(index(idx, 0), 0, ActivityTime);

    return true;
}

void WorkPackagesModel::loadData() {
    WorkPackagesDescription workPackages = mUserSettings.value("workPackages").value<WorkPackagesDescription>();

    if (workPackages.isEmpty()) {
        addNewEmptyTask();
        return;
    }

    for (WorkPackageDescription item : workPackages) {
        WorkPackage *workPackage = new WorkPackage(item);
        if (mUserSettings.restoreTaskSwitchStateAtStartUp() == false)
            workPackage->setActive(false);
        mWorkPackages.append(workPackage);
    }
}

void WorkPackagesModel::saveData() {
    WorkPackagesDescription workPackages;

    for (WorkPackage *workPackage : mWorkPackages) {
        workPackages.append(*workPackage->config());
    }

    mUserSettings.setValue("workPackages", QVariant::fromValue(workPackages));
}

QDataStream& operator<<(QDataStream& out, const WorkPackagesDescription& workPackagesDescription) {
    out << workPackagesDescription.size();

    for (WorkPackageDescription workPackageDescription : workPackagesDescription) {
        out << workPackageDescription;
    }
    return out;
}

QDataStream& operator>>(QDataStream& in, WorkPackagesDescription& v) {
    int size;
    in >> size;

    for (int i=0; i < size; i++) {
        WorkPackageDescription workPackageDescription;
        in >> workPackageDescription;

        v.append(workPackageDescription);
    }

    return in;
}
