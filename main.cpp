#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStringList>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

//    QStringList dataList;
//    dataList.append("Item 2");
//    dataList.append("Item 1");
//    dataList.append("Item 3");
//    dataList.append("Item 4");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
