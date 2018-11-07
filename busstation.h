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
#endif  QQUICKTEXT_P_H
#include <QtQuick/private/qquicktext_p.h>
#endif
//class QDeclarativeGeoMapQuickItem;
class BusStation :public QDeclarativeGeoMapQuickItem
{
public:
    BusStation();//空构造函数
    BusStation(const QGeoCoordinate coordinate);
    BusStation(const QGeoCoordinate coordinate,
               const QString station_name);//构造函数
   // BusStation(const QGeoCoordinate coordinate)
    void set_bus_station_name(const QString station_name);
    QString bus_station_name();
    void set_bus_station_id(const int station_id);
    int bus_station_id();
    void set_bus_station_iocn(QQuickImage *iocn);
    QQuickImage *bus_iocn();
    void set_bus_station_imformation(QQuickText);
    QQuickText *bus_station_imformation();

private:
    QString bus_station_name_;//公交站名称
    int bus_station_id_;//公交站编号
    QQuickImage *bus_station_iocn_;//公交车站点图标指针
    QQuickText  *bus_station_imformation;//公交车基本信息



};

#endif // BUSSTATION_H
