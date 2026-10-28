// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#ifndef TASKMODEL_H
#define TASKMODEL_H

#include <QAbstractListModel>
#include <QSettings>
#include <QTimer>
#include <QtQml/qqmlregistration.h>
#include "Task.h"

class QJSEngine;
class QQmlEngine;

class TaskModel : public QAbstractListModel {
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(qint64 totalSeconds READ totalSeconds NOTIFY totalSecondsChanged)
    Q_PROPERTY(int runningCount READ runningCount NOTIFY runningCountChanged)
    Q_PROPERTY(int selectedCount READ selectedCount NOTIFY selectedCountChanged)

 public:
    enum Role {
        IdRole = Qt::UserRole + 1,
        ProjectRole,
        NameRole,
        SecondsRole,
        ElapsedRole,
        RunningRole,
        SelectedRole,
    };
    Q_ENUM(Role)

    // Not default-constructible on purpose, see AppSettings.
    explicit TaskModel(bool restoreRunning, QObject *parent = nullptr);
    ~TaskModel() override;

    static TaskModel *create(QQmlEngine *, QJSEngine *);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QHash<int, QByteArray> roleNames() const override;

    int count() const;
    qint64 totalSeconds() const;
    int runningCount() const;
    int selectedCount() const;

    // Returns the row of the newly created task.
    Q_INVOKABLE int addTask(const QString &project = QString(), const QString &name = QString());
    Q_INVOKABLE void removeTask(const QString &id);
    Q_INVOKABLE void removeSelected();
    Q_INVOKABLE void resetTime(const QString &id);
    Q_INVOKABLE void toggleRunning(const QString &id);
    Q_INVOKABLE void setSelected(const QStringList &ids, bool selected);
    Q_INVOKABLE void clearSelection();

    Q_INVOKABLE static QString formatDuration(qint64 seconds);

    // Adds elapsed time to every running task.
    void addElapsed(qint64 seconds);
    // Stops all running tasks and returns their ids so they can be resumed.
    QList<QUuid> pauseAll();
    void resume(const QList<QUuid> &ids);

 public slots:
    void save();

 signals:
    void countChanged();
    void totalSecondsChanged();
    void runningCountChanged();
    void selectedCountChanged();

 private:
    int rowOf(const QString &id) const;
    int rowOf(const QUuid &id) const;
    void setRunning(int row, bool running);
    void removeRows(const QList<int> &rows);
    void scheduleSave(int delayMs);

    QList<Task> mTasks;
    QSettings mSettings;
    QTimer mSaveTimer;

    static inline TaskModel *sInstance = nullptr;
};

#endif  // TASKMODEL_H
