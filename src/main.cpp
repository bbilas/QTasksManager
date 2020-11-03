// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "WorkPackagesModel.h"
#include "UserSettings.h"

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qRegisterMetaTypeStreamOperators<WorkPackagesDescription>("WorkPackagesDescription");
    WorkPackagesModel workPackagesModel;
    UserSettings userSettings;

    engine.rootContext()->setContextProperty("taskModel", &workPackagesModel);
    engine.rootContext()->setContextProperty("userSettings", &userSettings);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
