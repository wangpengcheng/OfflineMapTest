
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
// use test
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
    /*
    //use Plugin
    Q_IMPORT_PLUGIN(GeoServiceProviderFactory);
    //add qucik
    QQmlApplicationEngine engine;
    //load qml file
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    */
    //temp_test=new tool_test();
    Tool temp_tool1();
    Tool temp_tool=temp_tool1();
    tool_test temp_test1();
    tool_test* temp_test=new tool_test();
    temp_test->WPS84Test();


    return app.exec();


}

