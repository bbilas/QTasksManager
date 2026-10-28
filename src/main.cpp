// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#include <QApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQuickWindow>
#include <QSystemTrayIcon>
#include "AppSettings.h"
#include "ScreenLockMonitor.h"
#include "TaskModel.h"
#include "TimeTracker.h"
#include "TrayIcon.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    // Keep the 1.x settings location ("Unknown Organization/QTasksManager.conf").
    QApplication::setApplicationName(QStringLiteral("QTasksManager"));
    QApplication::setApplicationVersion(QStringLiteral(QTASKSMANAGER_VERSION));
    QApplication::setDesktopFileName(QStringLiteral("qtasksmanager"));
    QApplication::setWindowIcon(QIcon(QStringLiteral(":/media/icons/tray_icon.png")));
    // Without a tray there is no way back to a hidden window, so quit on close.
    QApplication::setQuitOnLastWindowClosed(!QSystemTrayIcon::isSystemTrayAvailable());
    QQuickStyle::setStyle(QStringLiteral("Basic"));

    AppSettings settings(nullptr);
    TaskModel tasks(settings.restoreRunningOnStartup());
    ScreenLockMonitor screenLock;
    TimeTracker tracker(&tasks, &settings, &screenLock);
    QObject::connect(&app, &QCoreApplication::aboutToQuit, &tasks, &TaskModel::save);

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed, &app,
                     [] { QCoreApplication::exit(EXIT_FAILURE); }, Qt::QueuedConnection);
    engine.loadFromModule("TasksManager", "Main");
    if (engine.rootObjects().isEmpty())
        return EXIT_FAILURE;

    TrayIcon trayIcon(qobject_cast<QQuickWindow *>(engine.rootObjects().constFirst()), &tasks);
    QObject::connect(&tracker, &TimeTracker::overtimeStarted, &trayIcon, &TrayIcon::showOvertimeMessage);

    return app.exec();
}
