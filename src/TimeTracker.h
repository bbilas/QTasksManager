// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#ifndef TIMETRACKER_H
#define TIMETRACKER_H

#include <QElapsedTimer>
#include <QObject>
#include <QTimer>
#include <QUuid>

class AppSettings;
class ScreenLockMonitor;
class TaskModel;

// Advances running tasks, pauses them while the screen is locked and reports
// when the total tracked time goes past the daily working time.
class TimeTracker : public QObject {
    Q_OBJECT

 public:
    TimeTracker(TaskModel *model, AppSettings *settings, ScreenLockMonitor *screenLock,
                QObject *parent = nullptr);

 signals:
    void overtimeStarted(const QString &totalTime);

 private:
    void tick();
    void onScreenLockedChanged(bool locked);
    void checkOvertime();

    TaskModel *mModel;
    AppSettings *mSettings;
    QTimer mTimer;
    QElapsedTimer mClock;
    qint64 mPendingMs = 0;
    QList<QUuid> mPausedByLock;
    bool mPausedForLock = false;
    bool mOvertimeNotified = false;
};

#endif  // TIMETRACKER_H
