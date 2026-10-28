// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#include "TrayIcon.h"

#include <QCoreApplication>
#include <QWindow>
#include "TaskModel.h"

TrayIcon::TrayIcon(QWindow *window, TaskModel *model, QObject *parent)
    : QSystemTrayIcon(parent), mWindow(window), mModel(model) {
    mToggleAction = mMenu.addAction(tr("Hide"), this, &TrayIcon::toggleWindow);
    mMenu.addSeparator();
    mMenu.addAction(tr("Quit"), QCoreApplication::instance(), &QCoreApplication::quit);
    setContextMenu(&mMenu);

    connect(&mMenu, &QMenu::aboutToShow, this, [this] {
        mToggleAction->setText(mWindow && mWindow->isVisible() ? tr("Hide") : tr("Show"));
    });
    connect(this, &QSystemTrayIcon::activated, this, &TrayIcon::onActivated);
    connect(mModel, &TaskModel::totalSecondsChanged, this, &TrayIcon::updateToolTip);
    connect(mModel, &TaskModel::runningCountChanged, this, &TrayIcon::updateToolTip);

    setIcon(QIcon(QStringLiteral(":/media/icons/tray_icon.png")));
    updateToolTip();
    show();
}

void TrayIcon::showOvertimeMessage(const QString &totalTime) {
    if (!QSystemTrayIcon::supportsMessages())
        return;

    showMessage(tr("You have started overtime"), tr("Time worked: %1").arg(totalTime),
                QSystemTrayIcon::Information, 5000);
}

void TrayIcon::onActivated(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::Trigger || reason == QSystemTrayIcon::DoubleClick)
        toggleWindow();
}

void TrayIcon::toggleWindow() {
    if (!mWindow)
        return;

    if (mWindow->isVisible() && mWindow->isActive()) {
        mWindow->hide();
    } else {
        mWindow->showNormal();
        mWindow->raise();
        mWindow->requestActivate();
    }
}

void TrayIcon::updateToolTip() {
    const int running = mModel->runningCount();
    QString text = tr("QTasksManager — %1 tracked").arg(TaskModel::formatDuration(mModel->totalSeconds()));
    if (running > 0)
        text += QLatin1Char('\n') + tr("%n task(s) running", nullptr, running);
    setToolTip(text);
}
