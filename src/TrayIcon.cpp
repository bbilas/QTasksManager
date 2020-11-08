// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#include <QCoreApplication>
#include "TrayIcon.h"

TrayIcon::TrayIcon(QQuickWindow *window) {
    mMinimizeWindowAction.reset(new QAction(QStringLiteral("Minimize"), this));
    mRestoreWindowAction.reset(new QAction(QStringLiteral("Restore"), this));
    mQuitWindowAction.reset(new QAction(QStringLiteral("Quit"), this));
    connect(mMinimizeWindowAction.data(), &QAction::triggered, window, &QQuickWindow::hide);
    connect(mRestoreWindowAction.data(), &QAction::triggered, window, &QQuickWindow::showNormal);
    connect(mQuitWindowAction.data(), &QAction::triggered, QCoreApplication::instance(), &QCoreApplication::quit);

    mTrayIconMenu.reset(new QMenu());
    mTrayIconMenu->addAction(mMinimizeWindowAction.data());
    mTrayIconMenu->addAction(mRestoreWindowAction.data());
    mTrayIconMenu->addSeparator();
    mTrayIconMenu->addAction(mQuitWindowAction.data());
    setContextMenu(mTrayIconMenu.data());

    setIcon(QIcon(":/media/icons/tray_icon.png"));
    show();
}

