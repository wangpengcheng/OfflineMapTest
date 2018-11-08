#include "busstation.h"
#ifndef QURL_H
#include <QUrl>
#endif
BusStation::BusStation()
{

}
BusStation:: BusStation(const QGeoCoordinate coordinate)
{
    setCoordinate(coordinate);
    bus_station_id_="";//station_id;//设置站点图标；
    bus_station_iocn_->setSource(QUrl("qrc:/img/bus_station.png"));
    bus_station_iocn_->setSize(QSize(50,50));//设置默认大小
     qDebug()<<bus_station_iocn_->height();
    Update();
}
BusStation:: BusStation(const QGeoCoordinate coordinate,
                        const QString station_id)
{
    setCoordinate(coordinate);
    bus_station_id_=station_id;//station_id;//设置站点图标；
    qDebug()<<bus_station_id_;
    bus_station_iocn_=new QQuickImage();

    bus_station_iocn_->setSource(QUrl("qrc:/img/bus_station.png"));
    bus_station_iocn_->setSize(QSize(50,50));//设置默认大小
    Update();
}
BusStation::BusStation(const QGeoCoordinate coordinate,
                       const QString station_id,
                       const QString station_name)
{
    setCoordinate(coordinate);//设置站点坐标
    bus_station_id_=station_id;//设置站点图标；
    bus_station_name_=station_name;//设置站点名称
    bus_station_iocn_->setSource(QUrl("qrc:/img/bus_station.png"));
    bus_station_iocn_->setSize(QSize(50,50));
    Update();

}
BusStation:: BusStation(const QGeoCoordinate coordinate,//坐标
                        const QString station_id, //站点ID编号
                        const QString station_name,//站点名称
                        const QUrl iocn_url)//设置站点坐标名称和图标iocn_url

{
    setCoordinate(coordinate);//设置站点坐标
    bus_station_id_=station_id;//设置站点图标；
    bus_station_name_=station_name;//设置站点名称
    bus_station_iocn_->setSource(iocn_url);//设置iocn
    bus_station_iocn_->setSize(QSize(50,50));
    Update();
}
void BusStation::setBusStationId(const QString station_id)
{
    bus_station_id_=station_id;
}
QString BusStation::bus_station_id()
{
    return bus_station_id_;
}
void BusStation::setBusStationName(const QString station_name)
{
    bus_station_name_=station_name;
}
QString BusStation::bus_station_name()
{
    return bus_station_name_;
}
void BusStation::setBusStationIocn(QQuickImage *iocn)
{
    bus_station_iocn_=iocn;
}
QQuickImage* BusStation::bus_station_iocn()
{
    return bus_station_iocn_;
}
void BusStation::setBusStationInformation(QQuickText *station_information)
{
    bus_station_information_=station_information;
}
QQuickText *BusStation::bus_station_information()
{
    return bus_station_information_;
}
void BusStation::setIocnScale(double scale)
{
    bus_station_iocn_->setSourceSize(QSize(bus_station_iocn_->width()*scale,
                                           bus_station_iocn_->height()*scale));
}
void BusStation::Update()
{
    setSourceItem(bus_station_iocn_);//将图片添加到Item
    setAnchorPoint(QPointF(bus_station_iocn_->width()*0.5,
                           bus_station_iocn_->height()*0.5));//设置偏移

}

