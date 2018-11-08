#ifndef BUSSTATION_H
#define BUSSTATION_H

/*
 *BusStation类 继承自QDeclarativeGeoMapQuickItem
 * 定义公交车站点基本类
 *成员信息函数，包括：站点名称、站点坐标、
 *站点编号、站点图标、站点信息
 *  王鹏程 2018-11-7 20:48
 * 完整项目地址：
 * https://github.com/wangpengcheng/OfflineMapTest
 *
 */
#ifndef  QDECLARATIVEGEOMAPQUICKITEM_H
#include <QtLocation/private/qdeclarativegeomapquickitem_p.h>
#endif
#ifndef  QSTRING_H
#include <QString>
#endif
#ifndef QGEOCOORDINATE_H
#include <QGeoCoordinate>
#endif
#ifndef  QQUICKIMAGE_P_H
#include <QtQuick/private/qquickimage_p.h>
#endif
#ifndef QQUICKTEXT_P_H
#include <QtQuick/private/qquicktext_p.h>
#endif
class BusStation :public QDeclarativeGeoMapQuickItem
{
public:
    BusStation();//空构造函数
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
    void setBusStationId(const QString station_id);
    QString bus_station_id();
    void setBusStationName(const QString station_name);
    QString bus_station_name();
    void setBusStationIocn(QQuickImage *iocn);
    QQuickImage *bus_station_iocn();
    void setBusStationInformation(QQuickText *station_information);//暂时设置公交车基本信息
    QQuickText *bus_station_information();
    void setIocnScale(double Scale);
     void Update();//更新数据

private:
    QString bus_station_id_;//公交站编号
    QString bus_station_name_;//公交站名称
    QQuickImage *bus_station_iocn_=new QQuickImage();//公交车站点图标指针
    QQuickText  *bus_station_information_;//公交车基本信息



};

#endif // BUSSTATION_H
