// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#include "TaskFilterModel.h"

#include "TaskModel.h"

TaskFilterModel::TaskFilterModel(QObject *parent) : QSortFilterProxyModel(parent) {
    connect(this, &QAbstractItemModel::rowsInserted, this, &TaskFilterModel::updateCounts);
    connect(this, &QAbstractItemModel::rowsRemoved, this, &TaskFilterModel::updateCounts);
    connect(this, &QAbstractItemModel::modelReset, this, &TaskFilterModel::updateCounts);
    connect(this, &QAbstractItemModel::layoutChanged, this, &TaskFilterModel::updateCounts);
    connect(this, &QAbstractItemModel::dataChanged, this,
            [this](const QModelIndex &, const QModelIndex &, const QList<int> &roles) {
                if (roles.isEmpty() || roles.contains(TaskModel::SelectedRole))
                    updateCounts();
            });
}

QString TaskFilterModel::filterText() const {
    return mFilterText;
}

void TaskFilterModel::setFilterText(const QString &text) {
    const QString trimmed = text.trimmed();
    if (trimmed == mFilterText)
        return;

#if QT_VERSION >= QT_VERSION_CHECK(6, 10, 0)
    beginFilterChange();
    mFilterText = trimmed;
    endFilterChange(Direction::Rows);
#else
    mFilterText = trimmed;
    invalidateRowsFilter();
#endif
    emit filterTextChanged();
}

int TaskFilterModel::count() const {
    return mCount;
}

int TaskFilterModel::selectedCount() const {
    return mSelectedCount;
}

void TaskFilterModel::selectAll(bool selected) {
    auto *tasks = qobject_cast<TaskModel *>(sourceModel());
    if (!tasks)
        return;

    QStringList ids;
    ids.reserve(rowCount());
    for (int row = 0; row < rowCount(); ++row)
        ids.append(index(row, 0).data(TaskModel::IdRole).toString());
    tasks->setSelected(ids, selected);
}

bool TaskFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    if (mFilterText.isEmpty())
        return true;

    const QModelIndex idx = sourceModel()->index(sourceRow, 0, sourceParent);
    return idx.data(TaskModel::NameRole).toString().contains(mFilterText, Qt::CaseInsensitive)
        || idx.data(TaskModel::ProjectRole).toString().contains(mFilterText, Qt::CaseInsensitive);
}

void TaskFilterModel::updateCounts() {
    int selected = 0;
    for (int row = 0; row < rowCount(); ++row) {
        if (index(row, 0).data(TaskModel::SelectedRole).toBool())
            ++selected;
    }

    if (mCount != rowCount()) {
        mCount = rowCount();
        emit countChanged();
    }
    if (mSelectedCount != selected) {
        mSelectedCount = selected;
        emit selectedCountChanged();
    }
}
