#include <iostream>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include "devicecommunicator.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);


    qmlRegisterSingletonType<DeviceCommunicator>("dslul.devicecomm", 1,0, "DevCom", [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)
        DeviceCommunicator *devcomm = new DeviceCommunicator();
        return devcomm;
    });

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
