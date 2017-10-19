#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QDir>
#include "devicecommunicator.h"
#include "ProfileManager.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<DeviceCommunicator>("dslul.devicecomm", 1,0, "DevCom");
    qmlRegisterType<ProfileManager>("dslul.ProfileManager", 1,0, "ProfileManager");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
