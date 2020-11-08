// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#include <QCoreApplication>
#include <QMessageBox>
#include "TrayIcon.h"

TrayIcon::TrayIcon(QQuickWindow *window) :
    mWindow(window) {
    mMinimizeWindowAction.reset(new QAction(QStringLiteral("Minimize"), this));
    mRestoreWindowAction.reset(new QAction(QStringLiteral("Restore"), this));
    mQuitWindowAction.reset(new QAction(QStringLiteral("Quit"), this));
    connect(mMinimizeWindowAction.data(), &QAction::triggered, window, &QQuickWindow::hide);
    connect(mRestoreWindowAction.data(), &QAction::triggered, window, &QQuickWindow::showNormal);
    connect(mQuitWindowAction.data(), &QAction::triggered, QCoreApplication::instance(), &QCoreApplication::quit);
    connect(this, &QSystemTrayIcon::activated, this, &TrayIcon::iconActivated);

    mTrayIconMenu.reset(new QMenu());
    mTrayIconMenu->addAction(mMinimizeWindowAction.data());
    mTrayIconMenu->addAction(mRestoreWindowAction.data());
    mTrayIconMenu->addSeparator();
    mTrayIconMenu->addAction(mQuitWindowAction.data());
    setContextMenu(mTrayIconMenu.data());

    setIcon(QIcon(":/media/icons/tray_icon.png"));
    show();
}

void TrayIcon::onShowOverHoursMessage(const QString &totalActivityTime) {
    if (QSystemTrayIcon::supportsMessages() == false)
        return;

    const QString msg("Time worked: " + totalActivityTime);
    QSystemTrayIcon::MessageIcon msgIcon = QSystemTrayIcon::MessageIcon(0);
    showMessage("You have started overhours!", msg, msgIcon, 3000);
}

void TrayIcon::iconActivated(QSystemTrayIcon::ActivationReason reason) {
    switch (reason) {
    case QSystemTrayIcon::DoubleClick:
        if (mWindow->isVisible())
            mWindow->hide();
        else
            mWindow->showNormal();
        break;
    default:
        ;
    }
}
