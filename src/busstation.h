#ifndef BUSSTATION_H
#define BUSSTATION_H

/****************************************************************************
** @projectName   OfflineMapTest
** QT Version     5.11.1
** This file is part of the OfflineMapTest project.
** @file          busstation.h
** @brief         BusStation class
** @details       BusStation class inhert QDeclarativeGeoMapQuickItem ;So
**                it can be used in the QDeclarativeGeoMap to add bus station
** @author        wangpengcheng
** @QQ            673018396
** @email         wangpengcheng2018@gmail.com
** @address       https://github.com/wangpengcheng/OfflineMapTest
** @date          2018-11-7 周三  20:48:43
** @example
**
** QQmlApplicationEngine engine; //load qml file
** engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
** Tool tool;//创建tool工具类
** QObject *pRoot=engine.rootObjects().first();//获取qml第一个对象：
** QDeclarativeGeoMap *qMap=pRoot->findChild<QDeclarativeGeoMap *>("maptest1"); //找到map节点
** if(qMap!=0)
** {
**    QGeoCoordinate station_1=tool.WPS84ToGCJ02(30.5565134000,103.9940400000);
**    QString station1_id="station1";
**    qDebug()<<station1_id;
**    BusStation *station1=new BusStation(station_1);
**    qMap->addMapItem(station1);
** }else
** {
**    qDebug("Can not get this Object");
** }
**
*****************************************************************************/

#ifndef  QDECLARATIVEGEOMAPQUICKITEM_H
#include <QtLocation/private/qdeclarativegeomapquickitem_p.h>
#endif
class QQuickImage;
class QQuickText;
class BusStation :public QDeclarativeGeoMapQuickItem
{
public:
    BusStation();//空构造函数
    ~BusStation();//析构函数；主要负责销毁指针
    BusStation(const QGeoCoordinate coordinate);
    BusStation(const QGeoCoordinate coordinate,
               const QString station_id);//二参数构造函数
    BusStation(const QGeoCoordinate coordinate,
               const QString station_id,
               const QString station_name);//构造函数
    BusStation(const QGeoCoordinate coordinate,//坐标
               const QString station_id, //站点ID编号
               const QString station_name,//站点名称
               const QUrl iocn_url);//设置站点坐标名称和图标iocn_url
   // BusStation(const QGeoCoordinate coordinate)
    void SetBusStationId(const QString station_id);
    QString bus_station_id();
    void SetBusStationName(const QString station_name);
    QString bus_station_name();
    void SetBusStationIocn(QQuickImage *iocn);
    QQuickImage *bus_station_iocn();
    void SetBusStationInformation(QQuickText *station_information);//暂时设置公交车基本信息
    QQuickText *bus_station_information();
    void SetIocnScale(double Scale);
    void StationInit();//初始化相关参数；
    void Update();//更新数据

private:
    QString bus_station_id_;//公交站编号
    QString bus_station_name_;//公交站名称
    QQuickImage *bus_station_iocn_;//公交车站点图标指针
    QQuickText  *bus_station_information_;//公交车基本信息



};

#endif // BUSSTATION_H
