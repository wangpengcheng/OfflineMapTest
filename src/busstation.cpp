#include "busstation.h"

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
#ifndef QURL_H
#include <QUrl>
#endif

BusStation::BusStation()
{
     StationInit();
     Update();
}
BusStation::~BusStation()
{
    if(bus_station_iocn_!=NULL)
    {
        delete[] bus_station_iocn_;//防止产生指针数组时，没有调用析构函数
        bus_station_iocn_=NULL;
    }
    if(bus_station_information_!=NULL)
    {
        delete[] bus_station_information_;
        bus_station_information_=NULL;
    }
}
BusStation:: BusStation(const QGeoCoordinate coordinate)
{
    //初始化相关参数；
    StationInit();
    setCoordinate(coordinate);
    Update();
}
BusStation:: BusStation(const QGeoCoordinate coordinate,
                        const QString station_id)
{
    StationInit();
    setCoordinate(coordinate);
    bus_station_id_=station_id;//station_id;//设置站点图标；
    Update();
}
BusStation::BusStation(const QGeoCoordinate coordinate,
                       const QString station_id,
                       const QString station_name)
{
    StationInit();//初始化
    setCoordinate(coordinate);//设置站点坐标
    bus_station_id_=station_id;//设置站点id；
    bus_station_name_=station_name;//设置站点名称
    Update();

}
BusStation:: BusStation(const QGeoCoordinate coordinate,//坐标
                        const QString station_id, //站点ID编号
                        const QString station_name,//站点名称
                        const QUrl iocn_url)//设置站点坐标名称和图标iocn_url

{
    StationInit();//初始化
    setCoordinate(coordinate);//设置站点坐标
    bus_station_id_=station_id;//设置站点图标；
    bus_station_name_=station_name;//设置站点名称
    bus_station_iocn_->setSource(iocn_url);//设置iocn
    bus_station_iocn_->setSize(QSize(50,50));
    Update();
}
void BusStation::SetBusStationId(const QString station_id)
{
    bus_station_id_=station_id;
}
QString BusStation::bus_station_id()
{
    return bus_station_id_;
}
void BusStation::SetBusStationName(const QString station_name)
{
    bus_station_name_=station_name;
}
QString BusStation::bus_station_name()
{
    return bus_station_name_;
}
void BusStation::SetBusStationIocn(QQuickImage *iocn)
{
    bus_station_iocn_=iocn;
}
QQuickImage* BusStation::bus_station_iocn()
{
    return bus_station_iocn_;
}
void BusStation::SetBusStationInformation(QQuickText *station_information)
{
    bus_station_information_=station_information;
}
QQuickText *BusStation::bus_station_information()
{
    return bus_station_information_;
}
void BusStation::SetIocnScale(double scale)
{
    bus_station_iocn_->setSize(QSize(bus_station_iocn_->width()*scale,
                                     bus_station_iocn_->height()*scale));
}
void BusStation::StationInit()
{

    QString bus_station_id_="";//公交站编号
    QString bus_station_name_="";//公交站名称
    QGeoCoordinate InitCoordinate(30.5568330000,103.9997920000);
    bus_station_information_=NULL;//防止内存分配失败
    bus_station_information_=new QQuickText();
    bus_station_iocn_=NULL;
    bus_station_iocn_=new QQuickImage();
    bus_station_iocn_->setSource(QUrl("qrc:/img/bus_station.png"));
    bus_station_iocn_->setSize(QSize(50,50));//设置默认大小
    setCoordinate(InitCoordinate);//设置默认位置
}
void BusStation::Update()
{
    setSourceItem(bus_station_iocn_);//将图片添加到Item
    setAnchorPoint(QPointF(bus_station_iocn_->width()*0.5,
                           bus_station_iocn_->height()*0.5));//设置偏移

}

