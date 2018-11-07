#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QtPlugin>
#include <QDebug>
#include <QDir>
#include <QWidget>
#include <QDesktopWidget>
#include <QDialog>
#include <QtLocation/private/qdeclarativegeomap_p.h>
#include <QtLocation/private/qdeclarativecirclemapitem_p.h>
/*
 * tool 测试类
 *
 * #include "tool.h"
 * #include "test/tool_test.h"
*/
#include "tool.h"
#include "test/tool_test.h"

#include "test/screencontroltest.h"

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

    // tool_test temp_test; //main function
     //temp_test.WPS84Test();//wps84Test tool

    return app.exec();

}

