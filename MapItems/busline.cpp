#include "busline.h"
#include "MapItems/busstation.h"
#include "MapItems/tool.h"
BusLine::BusLine()
{
    Init();
    Updata();
}
BusLine::BusLine(QList<QGeoCoordinate> line_coordinates,
                 QList<QGeoCoordinate> station_coordinates)
{
    line_coordinate_list_ = line_coordinates;
    //设置站点队列坐标
    for (int i = 0; i < station_coordinates.size(); ++i)
    {
        BusStation *temp_station = new BusStation(station_coordinates.at(i));
        bus_station_list_.append(temp_station);
    }
    Init();
    Updata();
}
BusLine::~BusLine()
{
    DELETE_QOBJECT(bus_poly_line_);
}
void BusLine::set_bus_stations_fromcoordinate(const QList<QGeoCoordinate> station_coordinates)
{
    if (station_coordinates.isEmpty())
    {
        qDebug() << "please check station coordinates length again!!!";
    }
    else
    {
        //清空原来列表
        if (!bus_station_list_.isEmpty())
        {
            bus_station_list_.clear();
        };
        for (int i = 0; i < station_coordinates.length(); ++i)
        {
            BusStation *temp_station = new BusStation(station_coordinates.at(i));
            bus_station_list_.append(temp_station);
        }
    }
}
void BusLine::Updata() //更新数据
{
    bus_poly_line_->setPath(line_coordinate_list_);
    /*绑定子节点-start*/
    bus_poly_line_->setParentItem(this);
    for (int i = 0; i < bus_station_list_.size(); ++i)
    {
        bus_station_list_.at(i)->setParentItem(this);
    }
    /*绑定子节点-end*/
}
void BusLine::Init() //初始化数据
{
    /*初始化基本信息-start*/
    bus_line_id_ = "";
    bus_line_name_ = "";
    bus_line_information_ = "";
    bus_poly_line_ = nullptr;
    if (bus_poly_line_ == nullptr)
    {
        bus_poly_line_ = new QDeclarativePolylineMapItem();
    }
    if (line_coordinate_list_.isEmpty())
    {
        line_coordinate_list_.append(Tool::WPS84ToGCJ02(30.5594483655, 103.9976232481));
    }
    bus_poly_line_->line()->setColor("red");
    bus_poly_line_->line()->setWidth(3.5);
    /*初始化基本信息-end*/
}
