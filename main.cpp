//#include <QGuiApplication>
//#include <QQmlApplicationEngine>

//int main(int argc, char *argv[])
//{
//    QGuiApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;

//    return app.exec();
//}

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtPlugin>
#include <QDebug>
#include <QDir>
int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);
    //get file path
    QString runPath = QCoreApplication::applicationFilePath();
    qDebug()<<runPath;
    qDebug()<<QDir::currentPath();
    //use Plugin
    Q_IMPORT_PLUGIN(GeoServiceProviderFactory)
    //add qucik
    QQmlApplicationEngine engine;
    //load qml file
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();


}

