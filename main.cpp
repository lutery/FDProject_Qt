#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStringList>
#include <QQmlContext>
#include "fdobject.h"
#include "fdservice.h"
#include "testthread.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

//    TestThread testThread;
//    testThread.start();

    qmlRegisterType<FDService>("one.chchy.FDService", 1, 2, "FDService");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
