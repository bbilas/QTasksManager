// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include "WorkPackagesModel.h"
#include "UserSettings.h"
#include "WorkPackagesManager.h"
#include "TrayIcon.h"
#include "DateTimeValidator.h"

#define STRINGIZE(x) #x
#define STRINGIZE_VALUE_OF(x) STRINGIZE(x)

int main(int argc, char *argv[]) {

    qDebug() << STRINGIZE_VALUE_OF(CONFIG_SW_VERSION);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setQuitOnLastWindowClosed(false);
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qRegisterMetaTypeStreamOperators<WorkPackagesDescription>("WorkPackagesDescription");
    WorkPackagesModel workPackagesModel;
    UserSettings userSettings;
    WorkPackagesManager workPackagesManager(&workPackagesModel);
    QObject::connect(&userSettings, &UserSettings::dailyWorkingTimeChanged, &workPackagesManager, &WorkPackagesManager::onSetDailyWorkingTime);

    engine.rootContext()->setContextProperty("taskModel", &workPackagesModel);
    engine.rootContext()->setContextProperty("userSettings", &userSettings);
    qmlRegisterType<DateTimeValidator>("DateTimeValidator", 1, 0, "DateTimeValidator");
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    TrayIcon trayIcon(qobject_cast<QQuickWindow *>(engine.rootObjects().value(0)));
    QObject::connect(&workPackagesManager, &WorkPackagesManager::overHoursDetected, &trayIcon, &TrayIcon::onShowOverHoursMessage);

    return app.exec();
}
