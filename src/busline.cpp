#include "busline.h"
#include "src/busstation.h"
#ifndef TOOL_H
#include "src/tool.h"
#endif
BusLine::BusLine()
{
    Init();
    Updata();
}
BusLine::BusLine(QList<QGeoCoordinate> line_coordinates,
                 QList<QGeoCoordinate> station_coordinates)//线路坐标和站点坐标构造函数
{
    line_coordinate_list_=line_coordinates;
    //设置站点队列坐标
    for(int i=0;i<station_coordinates.size();++i)
    {
        BusStation *temp_station=new BusStation(station_coordinates.at(i));
        bus_station_list_.append(temp_station);
    }
     Init();
     Updata();
}
BusLine::~BusLine()
{
    if(bus_poly_line_!=NULL)
    {
        delete[] bus_poly_line_;
        bus_poly_line_=NULL;
    }
}
QList<QGeoCoordinate> BusLine::line_coordinate_list()
{
    return line_coordinate_list_;
}
//QGeoPath BusLine::bus_polyline_path()
//{
//    return bus_polyline_path_;
//}
//void BusLine::set_bus_polyline_path(QList<QGeoCoordinate> new_path)
//{
//    bus_polyline_path_.setPath(new_path);
//}
QList<BusStation *> BusLine::bus_station_list()
{
    return bus_station_list_;
}
void BusLine::set_bus_station_list(QList<BusStation *> stations)
{
    bus_station_list_=stations;
}
void BusLine::set_bus_stations_fromcoordinate(const QList<QGeoCoordinate> station_coordinates)
{
    if(station_coordinates.isEmpty())
    {
        qDebug()<<"please check station coordinates length again!!!";
    }else {
        //清空原来列表
        if(!bus_station_list_.isEmpty())
        {
            bus_station_list_.clear();
        };
        for(int i=0;i<station_coordinates.length();++i)
        {
            BusStation *temp_station=new BusStation(station_coordinates.at(i));
            bus_station_list_.append(temp_station);
        }
    }
}

QString BusLine::bus_line_id()
{
    return bus_line_id_;
}
void BusLine::set_bus_line_id(const QString line_id)
{
    bus_line_id_=line_id;
}
QString BusLine::bus_line_name()
{
    return bus_line_name_;
}
void BusLine::set_bus_line_name(const QString temp_string)
{
    bus_line_name_=temp_string;
}
QString BusLine::bus_line_information()
{
    return bus_line_information_;
}
void BusLine::set_bus_line_information(const QString line_information)
{
    bus_line_information_=line_information;
}
QDeclarativePolylineMapItem *BusLine::bus_poly_line()
{
    return bus_poly_line_;
}
void BusLine::Updata()//更新数据
{
    bus_poly_line_->setPath(line_coordinate_list_);
    /*绑定子节点-start*/
    bus_poly_line_->setParentItem(this);
    for(int i=0;i<bus_station_list_.size();++i)
    {
        bus_station_list_.at(i)->setParentItem(this);
    }
    /*绑定子节点-end*/
   // bus_polyline_path_.setPath(line_coordinate_list_);
}
void BusLine::Init()//初始化数据
{
    /*初始化基本信息-start*/
    bus_line_id_="";
    bus_line_name_="";
    bus_line_information_="";
    bus_poly_line_=NULL;
    if(bus_poly_line_==NULL)
    {
        bus_poly_line_=new QDeclarativePolylineMapItem();
    }
    if(line_coordinate_list_.isEmpty())
    {
        line_coordinate_list_.append(tool.WPS84ToGCJ02(30.5594483655,103.9976232481));
    }
  //  bus_polyline_path_.setPath(line_coordinate_list_);
  //  bus_polyline_path_.setWidth(3.5);
    bus_poly_line_->line()->setColor("red");
    bus_poly_line_->line()->setWidth(3.5);
    /*初始化基本信息-end*/

}

