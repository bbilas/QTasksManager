// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include "WorkPackagesModel.h"
#include "UserSettings.h"
#include "WorkPackagesManager.h"
#include "TrayIcon.h"

int main(int argc, char *argv[]) {

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setQuitOnLastWindowClosed(false);
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qRegisterMetaTypeStreamOperators<WorkPackagesDescription>("WorkPackagesDescription");
    WorkPackagesModel workPackagesModel;
    UserSettings userSettings;
    WorkPackagesManager workPackagesManager(&workPackagesModel);

    engine.rootContext()->setContextProperty("taskModel", &workPackagesModel);
    engine.rootContext()->setContextProperty("userSettings", &userSettings);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    TrayIcon trayIcon(qobject_cast<QQuickWindow *>(engine.rootObjects().value(0)));

    return app.exec();
}
