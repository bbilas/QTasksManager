// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#include "TimeTracker.h"

#include "AppSettings.h"
#include "ScreenLockMonitor.h"
#include "TaskModel.h"

TimeTracker::TimeTracker(TaskModel *model, AppSettings *settings, ScreenLockMonitor *screenLock,
                         QObject *parent)
    : QObject(parent), mModel(model), mSettings(settings) {
    // Measure real elapsed time instead of counting ticks, so a busy event loop
    // does not make timers drift. The monotonic clock skips system suspend.
    mClock.start();
    mTimer.setInterval(1000);
    mTimer.setTimerType(Qt::CoarseTimer);
    connect(&mTimer, &QTimer::timeout, this, &TimeTracker::tick);
    mTimer.start();

    connect(screenLock, &ScreenLockMonitor::lockedChanged, this, &TimeTracker::onScreenLockedChanged);
    connect(mSettings, &AppSettings::dailyWorkingTimeChanged, this, [this] {
        mOvertimeNotified = false;
        checkOvertime();
    });
    connect(mModel, &TaskModel::totalSecondsChanged, this, &TimeTracker::checkOvertime);
    // Do not notify right at startup when yesterday's total is already over.
    mOvertimeNotified = mModel->totalSeconds() > mSettings->dailyWorkingSeconds();
}

void TimeTracker::tick() {
    const qint64 elapsedMs = mClock.restart();
    if (mModel->runningCount() == 0) {
        mPendingMs = 0;
        return;
    }

    mPendingMs += elapsedMs;
    const qint64 seconds = mPendingMs / 1000;
    mPendingMs %= 1000;
    mModel->addElapsed(seconds);
}

void TimeTracker::onScreenLockedChanged(bool locked) {
    if (locked) {
        if (mPausedForLock || !mSettings->pauseOnScreenLock())
            return;

        tick();
        mPausedByLock = mModel->pauseAll();
        mPausedForLock = true;
    } else if (mPausedForLock) {
        mClock.restart();
        mModel->resume(mPausedByLock);
        mPausedByLock.clear();
        mPausedForLock = false;
    }
}

void TimeTracker::checkOvertime() {
    const qint64 total = mModel->totalSeconds();
    if (total <= mSettings->dailyWorkingSeconds()) {
        mOvertimeNotified = false;  // e.g. after the timers were reset
        return;
    }

    if (mOvertimeNotified)
        return;

    mOvertimeNotified = true;
    emit overtimeStarted(TaskModel::formatDuration(total));
}
