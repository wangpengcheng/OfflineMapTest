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
#include "tool.h"
#include "busstation.h"
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
    Tool tool;
    //qt 获取qml第一个对象：
    QObject *pRoot=engine.rootObjects().first();
    //找到map节点
    QDeclarativeGeoMap *qMap=pRoot->findChild<QDeclarativeGeoMap *>("maptest1");
        if(qMap!=0){
            QGeoCoordinate station_1=tool.WPS84ToGCJ02(30.5565134000,103.9940400000);
            QString station1_id="station1";
            qDebug()<<station1_id;
            BusStation *station1=new BusStation(station_1);
            QQuickImage *test_image=new QQuickImage();
                 //   QQuickItem test_Item=new QQuickItem();
                   // test_Item=test_image;
                    test_image->setSource(QUrl("qrc:/img/bus_station.png"));
                    test_image->setHeight(100);
                    test_image->setWidth(100);
           // station1->setCoordinate(tool.WPS84ToGCJ02(30.5565134000,103.9940400000));
           // station1->setSourceItem(test_image);
            station1->setScale(2);
            QDeclarativeGeoMapQuickItem *MapQuickItem1=new QDeclarativeGeoMapQuickItem;

                  QQuickImage *test_image2=new QQuickImage();
               //   QQuickItem test_Item=new QQuickItem();
                 // test_Item=test_image;
                  test_image2->setSource(QUrl("qrc:/img/bus_station.png"));
                  test_image2->setHeight(100);
                  test_image2->setWidth(100);

                  MapQuickItem1->setCoordinate(tool.WPS84ToGCJ02(30.5565134000,103.9940400000));
                  MapQuickItem1->setSourceItem(test_image2);


            qMap->addMapItem(station1);
            //添加对象
            qMap->addMapItem(MapQuickItem1);

           }else {
               qDebug("Can not get this Object");
           }

    return app.exec();

}

