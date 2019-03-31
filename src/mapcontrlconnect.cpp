#include "mapcontrlconnect.h"

MapContrlConnect::MapContrlConnect()
{

}
MapContrlConnect::MapContrlConnect(QDeclarativeGeoMap *show_map,
                                   QDeclarativeGeoMap *control_map)
{
    show_map_ptr_=show_map;
    control_map_ptr_=control_map;
    Init();
}

//MapContrlConnect::~MapContrlConnect()
//{

//}
void MapContrlConnect::Init()
{
    if(control_map_ptr_!=nullptr&&
            show_map_ptr_!=nullptr){

    connect(control_map_ptr_,SIGNAL(zoomLevelChanged(qreal)),this,SLOT(change_show_zoom(qreal)));
    connect(control_map_ptr_,SIGNAL(centerChanged(const QGeoCoordinate)),this,SLOT(change_show_center(const QGeoCoordinate)));
    qDebug()<<&control_map_ptr_;
    qDebug()<<&show_map_ptr_;
    }else {
        qDebug()<<"no point";
    }

}
void MapContrlConnect::change_show_zoom(qreal zoomLevel)
{
    show_map_ptr_->setZoomLevel(zoomLevel);
    qDebug()<<"hello word!";
}
void MapContrlConnect::change_show_center(const QGeoCoordinate &center)
{
    //show_map_ptr_->setCenter(center);
    show_map_ptr_->setCenter(center);
    qDebug()<<"hello word!123";
}
