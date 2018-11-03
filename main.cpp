
#include <iostream>
//#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QtPlugin>
#include <QDebug>
#include <QDir>
#include <QWidget>
#include <QDesktopWidget>
#include <QDialog>
#include <QtLocation/private/qdeclarativegeomap_p.h>
#include "tool.h"
#include "test/tool_test.h"
int main(int argc, char *argv[])
{

    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);
    //get file path
    QString runPath = QCoreApplication::applicationFilePath();
    qDebug()<<runPath;
    qDebug()<<QDir::currentPath();
    //use Plugin
    Q_IMPORT_PLUGIN(GeoServiceProviderFactory);
    //add qucik
    QQmlApplicationEngine engine;
    //load qml file
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();

}

