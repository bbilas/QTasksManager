// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#include "TaskModel.h"

#include <QJSEngine>
#include <algorithm>
#include "TaskStorage.h"

namespace {

constexpr int kEditSaveDelayMs = 1500;
constexpr int kTickSaveDelayMs = 15000;

}  // namespace

TaskModel::TaskModel(bool restoreRunning, QObject *parent)
    : QAbstractListModel(parent) {
    Q_ASSERT(!sInstance);
    sInstance = this;

    mTasks = TaskStorage::load(mSettings);
    if (!restoreRunning) {
        for (Task &task : mTasks)
            task.running = false;
    }
    if (mTasks.isEmpty())
        mTasks.append(Task());

    mSaveTimer.setSingleShot(true);
    connect(&mSaveTimer, &QTimer::timeout, this, &TaskModel::save);
}

TaskModel::~TaskModel() {
    if (mSaveTimer.isActive())
        save();
    sInstance = nullptr;
}

TaskModel *TaskModel::create(QQmlEngine *, QJSEngine *) {
    Q_ASSERT(sInstance);
    QJSEngine::setObjectOwnership(sInstance, QJSEngine::CppOwnership);
    return sInstance;
}

int TaskModel::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : int(mTasks.size());
}

QVariant TaskModel::data(const QModelIndex &index, int role) const {
    if (!checkIndex(index, CheckIndexOption::IndexIsValid | CheckIndexOption::ParentIsInvalid))
        return QVariant();

    const Task &task = mTasks.at(index.row());
    switch (role) {
    case IdRole:
        return task.id.toString(QUuid::WithoutBraces);
    case Qt::DisplayRole:
    case NameRole:
        return task.name;
    case ProjectRole:
        return task.project;
    case SecondsRole:
        return task.seconds;
    case ElapsedRole:
        return formatDuration(task.seconds);
    case RunningRole:
        return task.running;
    case SelectedRole:
        return task.selected;
    }

    return QVariant();
}

bool TaskModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!checkIndex(index, CheckIndexOption::IndexIsValid | CheckIndexOption::ParentIsInvalid))
        return false;

    Task &task = mTasks[index.row()];
    switch (role) {
    case ProjectRole:
        if (task.project == value.toString())
            return false;
        task.project = value.toString();
        scheduleSave(kEditSaveDelayMs);
        break;
    case NameRole:
        if (task.name == value.toString())
            return false;
        task.name = value.toString();
        scheduleSave(kEditSaveDelayMs);
        break;
    case RunningRole:
        setRunning(index.row(), value.toBool());
        return true;
    case SelectedRole:
        if (task.selected == value.toBool())
            return false;
        task.selected = value.toBool();
        emit selectedCountChanged();
        break;
    default:
        return false;
    }

    emit dataChanged(index, index, {role});
    return true;
}

Qt::ItemFlags TaskModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemNeverHasChildren;
}

QHash<int, QByteArray> TaskModel::roleNames() const {
    return {
        {IdRole, "taskId"},
        {ProjectRole, "project"},
        {NameRole, "name"},
        {SecondsRole, "seconds"},
        {ElapsedRole, "elapsed"},
        {RunningRole, "running"},
        {SelectedRole, "selected"},
    };
}

int TaskModel::count() const {
    return int(mTasks.size());
}

qint64 TaskModel::totalSeconds() const {
    qint64 total = 0;
    for (const Task &task : mTasks)
        total += task.seconds;
    return total;
}

int TaskModel::runningCount() const {
    return int(std::count_if(mTasks.cbegin(), mTasks.cend(), [](const Task &t) { return t.running; }));
}

int TaskModel::selectedCount() const {
    return int(std::count_if(mTasks.cbegin(), mTasks.cend(), [](const Task &t) { return t.selected; }));
}

int TaskModel::addTask(const QString &project, const QString &name) {
    Task task;
    task.project = project;
    task.name = name;

    beginInsertRows(QModelIndex(), 0, 0);
    mTasks.prepend(task);
    endInsertRows();

    emit countChanged();
    scheduleSave(kEditSaveDelayMs);
    return 0;
}

void TaskModel::removeTask(const QString &id) {
    const int row = rowOf(id);
    if (row >= 0)
        removeRows({row});
}

void TaskModel::removeSelected() {
    QList<int> rows;
    for (int i = 0; i < mTasks.size(); ++i) {
        if (mTasks.at(i).selected)
            rows.append(i);
    }
    removeRows(rows);
}

void TaskModel::resetTime(const QString &id) {
    const int row = rowOf(id);
    if (row < 0 || mTasks.at(row).seconds == 0)
        return;

    mTasks[row].seconds = 0;
    const QModelIndex idx = index(row);
    emit dataChanged(idx, idx, {SecondsRole, ElapsedRole});
    emit totalSecondsChanged();
    scheduleSave(kEditSaveDelayMs);
}

void TaskModel::toggleRunning(const QString &id) {
    const int row = rowOf(id);
    if (row >= 0)
        setRunning(row, !mTasks.at(row).running);
}

void TaskModel::setSelected(const QStringList &ids, bool selected) {
    bool changed = false;
    for (const QString &id : ids) {
        const int row = rowOf(id);
        if (row < 0 || mTasks.at(row).selected == selected)
            continue;

        mTasks[row].selected = selected;
        const QModelIndex idx = index(row);
        emit dataChanged(idx, idx, {SelectedRole});
        changed = true;
    }

    if (changed)
        emit selectedCountChanged();
}

void TaskModel::clearSelection() {
    bool changed = false;
    for (int i = 0; i < mTasks.size(); ++i) {
        if (!mTasks.at(i).selected)
            continue;

        mTasks[i].selected = false;
        emit dataChanged(index(i), index(i), {SelectedRole});
        changed = true;
    }

    if (changed)
        emit selectedCountChanged();
}

QString TaskModel::formatDuration(qint64 seconds) {
    seconds = std::max<qint64>(seconds, 0);
    return QStringLiteral("%1:%2:%3")
        .arg(seconds / 3600, 2, 10, QLatin1Char('0'))
        .arg((seconds / 60) % 60, 2, 10, QLatin1Char('0'))
        .arg(seconds % 60, 2, 10, QLatin1Char('0'));
}

void TaskModel::addElapsed(qint64 seconds) {
    if (seconds <= 0)
        return;

    bool changed = false;
    for (int i = 0; i < mTasks.size(); ++i) {
        if (!mTasks.at(i).running)
            continue;

        mTasks[i].seconds += seconds;
        emit dataChanged(index(i), index(i), {SecondsRole, ElapsedRole});
        changed = true;
    }

    if (changed) {
        emit totalSecondsChanged();
        scheduleSave(kTickSaveDelayMs);
    }
}

QList<QUuid> TaskModel::pauseAll() {
    QList<QUuid> paused;
    for (int i = 0; i < mTasks.size(); ++i) {
        if (mTasks.at(i).running) {
            paused.append(mTasks.at(i).id);
            setRunning(i, false);
        }
    }
    return paused;
}

void TaskModel::resume(const QList<QUuid> &ids) {
    for (const QUuid &id : ids) {
        const int row = rowOf(id);
        if (row >= 0)
            setRunning(row, true);
    }
}

void TaskModel::save() {
    mSaveTimer.stop();
    TaskStorage::save(mSettings, mTasks);
    mSettings.sync();
}

int TaskModel::rowOf(const QString &id) const {
    return rowOf(QUuid::fromString(id));
}

int TaskModel::rowOf(const QUuid &id) const {
    if (id.isNull())
        return -1;

    for (int i = 0; i < mTasks.size(); ++i) {
        if (mTasks.at(i).id == id)
            return i;
    }
    return -1;
}

void TaskModel::setRunning(int row, bool running) {
    if (mTasks.at(row).running == running)
        return;

    mTasks[row].running = running;
    const QModelIndex idx = index(row);
    emit dataChanged(idx, idx, {RunningRole});
    emit runningCountChanged();
    scheduleSave(kEditSaveDelayMs);
}

void TaskModel::removeRows(const QList<int> &rows) {
    if (rows.isEmpty())
        return;

    const int runningBefore = runningCount();
    const int selectedBefore = selectedCount();

    // Remove from the bottom up, collapsing contiguous rows into one range.
    QList<int> sorted = rows;
    std::sort(sorted.begin(), sorted.end());
    int i = int(sorted.size()) - 1;
    while (i >= 0) {
        const int last = sorted.at(i);
        int first = last;
        while (i > 0 && sorted.at(i - 1) == first - 1)
            first = sorted.at(--i);
        --i;

        beginRemoveRows(QModelIndex(), first, last);
        mTasks.remove(first, last - first + 1);
        endRemoveRows();
    }

    emit countChanged();
    emit totalSecondsChanged();
    if (runningCount() != runningBefore)
        emit runningCountChanged();
    if (selectedCount() != selectedBefore)
        emit selectedCountChanged();
    scheduleSave(kEditSaveDelayMs);
}

void TaskModel::scheduleSave(int delayMs) {
    if (!mSaveTimer.isActive() || mSaveTimer.remainingTime() > delayMs)
        mSaveTimer.start(delayMs);
}
