#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QtPlugin>
#include <QDebug>
#include <QDir>
#include <QWidget>
#include <QDesktopWidget>
#include <QDialog>

//使用location 注册类
#include <QtLocation/private/qdeclarativegeomap_p.h>
#include <QtLocation/private/qdeclarativecirclemapitem_p.h>
#include <QtLocation/private/qdeclarativegeomapquickitem_p.h>
//引入tool类
#include <QtQuick/private/qquickimage_p.h>
#include "src/tool.h"
#include "src/busstation.h"
#include "test/busstationtest.h"
int main(int argc, char *argv[])
{

    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);
    //use Plugin
    Q_IMPORT_PLUGIN(GeoServiceProviderFactory);
    //add qucik
    QQmlApplicationEngine engine;
    //load qml file
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    //创建tool工具类
    BusStationTest test;
    test.MainTest();
    BusStation *station1=new BusStation();

    //qt 获取qml第一个对象：
    QObject *pRoot=engine.rootObjects().first();
    //找到map节点
    QDeclarativeGeoMap *qMap=pRoot->findChild<QDeclarativeGeoMap *>("maptest1");
        if(qMap!=0){
            qMap->addMapItem(station1);
           }else {
               qDebug("Can not get this Object");
           }

    return app.exec();

}

