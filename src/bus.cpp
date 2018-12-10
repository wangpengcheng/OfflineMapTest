#include "bus.h"

Bus::Bus()
{
    Init();
    Updata();
}
Bus::~Bus()
{
    if(bus_iocn_!=NULL)
    {
        delete[] bus_iocn_;
        bus_iocn_=NULL;
    }
}
Bus::Bus(const QGeoCoordinate new_coordinate)
{
    Init();
    Updata();
    if(new_coordinate.isValid()){
        setCoordinate(new_coordinate);
    }
}
Bus::Bus(const QGeoCoordinate new_coordinate,
         QList<QGeoCoordinate> new_path)
{
    Init();
    Updata();
    if(new_coordinate.isValid()&&!new_path.isEmpty()){
        setCoordinate(new_coordinate);
        set_bus_path_coordinates(new_path);
    }else {
        qDebug()<<"input object is empty ,please check again";
    }
}
Bus::Bus(const QGeoCoordinate new_coordinate,
         QList<QGeoCoordinate> new_path,
         const QUrl iocn_path)
{
    Init();
    Updata();
    if(new_coordinate.isValid()
       &&!new_path.isEmpty()
       &&!iocn_path.isEmpty())
    {
        setCoordinate(new_coordinate);
        set_bus_path_coordinates(new_path);
        set_bus_iocn(iocn_path);
    }else {
        qDebug()<<"input object is empty ,please check again";
    }
}
QString Bus::bus_id()
{
    return bus_id_;
}
void Bus::set_bus_id(const QString input_bus_id)
{
    bus_id_=input_bus_id;
}
QString Bus::bus_name()
{
    return bus_name_;
}
void Bus::set_bus_name(const QString input_name)
{
    bus_name_=input_name;
}
QString Bus::bus_line_number()
{
    return bus_line_number_;
}
void Bus::set_bus_line_number(const QString input_bus_number)
{
    bus_line_number_=input_bus_number;
}
QString Bus::bus_information()
{
    return bus_information_;
}
void Bus::set_bus_information(const QString input_bus_information)
{
    bus_information_=input_bus_information;
}
QString Bus::bus_diver()
{
    return bus_diver_;
}
void Bus::set_bus_diver(const QString input_bus_diver)
{
    bus_diver_=input_bus_diver;
}

QList<QGeoCoordinate> Bus::bus_path_coordinates()
{
    return bus_path_coordinates_;
}
void Bus::set_bus_path_coordinates(QList<QGeoCoordinate> new_path)
{
    bus_path_coordinates_=new_path;
}
QQuickImage *Bus::bus_iocn()
{
    return bus_iocn_;
}
void Bus::set_bus_iocn(QQuickImage *iocn_image)
{
    bus_iocn_=iocn_image;
}
void Bus::set_bus_iocn(const QUrl iocn_source_url)
{
    bus_iocn_->setSource(iocn_source_url);
}
void Bus::Init()
{
    bus_id_="";//公交站编号
    bus_name_="";//公交站名称
    bus_line_number_="";//公交线路编号
    bus_information_="";//公交信息
    bus_diver_="";//公交驾驶人员信息
    QGeoCoordinate InitCoordinate(30.5567330000,103.9997920000);
    bus_path_coordinates_.append(InitCoordinate);
    bus_iocn_=NULL;//防止内存分配失败
    bus_iocn_=new QQuickImage();
    bus_iocn_->setSource(QUrl("qrc:/img/car_up.png"));
    //bus_station_iocn_->setSize(QSize(50,50));//设置默认大小
    setCoordinate(InitCoordinate);//设置默认位置
}
void Bus::Updata()
{
    setSourceItem(bus_iocn_);//将图片添加到Item
    setAnchorPoint(QPointF(bus_iocn_->width()*0.5,
                           bus_iocn_->height()*0.5));//设置偏移
}
