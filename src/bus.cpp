#include "bus.h"
#ifndef QMATH_H
#include <QtMath>
#endif
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
    };
    if(bus_time_line_!=NULL)
    {
        delete[] bus_time_line_;
        bus_time_line_=NULL;
    };
    if(bus_timer_!=NULL)
    {
        delete[] bus_timer_;
        bus_timer_=NULL;
    };
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
    setRotation(90);//设置图片旋转90度
    bus_time_line_=NULL;
    bus_timer_=NULL;
}
void Bus::Updata()
{
    setSourceItem(bus_iocn_);//将图片添加到Item
    setAnchorPoint(QPointF(bus_iocn_->width()*0.5,
                           bus_iocn_->height()*0.5));//设置偏移
}
/*网络位置请求 start*/
void Bus::UpdataPosition()
{
    //设置默认时钟,请求网络
    /*利用QTimeLine 进行请求*/
    /*
    bus_time_line_ = new QTimeLine(100000, this);
    bus_time_line_->setFrameRange(0, 100);
    connect(bus_time_line_, SIGNAL(frameChanged(int)),this, SLOT(UpdataCoordinatesByNet()));
    bus_time_line_->start();
    */
    /*利用QTimer 进行请求*/
    bus_timer_=new QTimer(this);
    connect(bus_timer_, SIGNAL(timeout()), this, SLOT(UpdataCoordinatesByNet()));
    bus_timer_->start(5000);//设置更新间隔为5s
}
void Bus::UpdataCoordinatesByNet()
{
    //设置网络请求
    QNetworkAccessManager *manage = new QNetworkAccessManager(this);
    QNetworkRequest network_request;
    network_request.setUrl(QUrl(QString("http://118.24.113.233/location_point_simulation.php")));
    /*建立connect，ReplyFinished为自定义槽函数,*/
    connect(manage,SIGNAL(finished(QNetworkReply *)),this,SLOT(GetReplyFinished(QNetworkReply *)));

    /*发送get网络请求*/
   manage->get(network_request);
}
void Bus::GetReplyFinished(QNetworkReply *reply)
{
    QJsonObject data = QJsonDocument::fromJson(reply->readAll()).object();
    double x=data.value(QString("bus_position")).toObject().value("x").toDouble();
    double y=data.value(QString("bus_position")).toObject().value("y").toDouble();
    setCoordinate(QGeoCoordinate(x,y));
   // MoveNextPoint(this->coordinate(),QGeoCoordinate(x,y));
    qDebug()<<this->coordinate();
}
/*网络位置请求 end*/
double Bus::GetPixelDistance(const QGeoCoordinate coordinate1,
                             const QGeoCoordinate coordinate2)
{
    QPointF point1,point2;
    auto parent_map=this->quickMap();
    point1=parent_map->fromCoordinate(coordinate1);
    point2=parent_map->fromCoordinate(coordinate2);
    double result=qSqrt(qPow((point1.x()-point2.x()),2)+qPow((point1.y()-point2.y()),2));
    return result;
}
void Bus::Move(const double dx,
               const double dy)
{
    QGeoCoordinate old_point,new_point;
    double temp_rotation=NULL;//转动角度;-180~180,
    old_point=this->coordinate();//获取中心点
    qDebug()<<old_point;
    double x,y;
    x=old_point.latitude()+dx;
    y=old_point.longitude()+dy;
    qDebug()<<"x:"<<x<<"y:"<<y;
    qDebug()<<"dx:"<<dx<<"dy:"<<dy;
    new_point=QGeoCoordinate(x,y);
    qDebug()<<new_point;
    this->setCoordinate(new_point);
    //计算转动方向
    if(dx==0&&dy==0){
        qDebug()<<"no move ";
    }else
    {
        temp_rotation=-qRadiansToDegrees(qAtan2(dx,dy));//注意坐标体系转换变号，负号反向
        qDebug()<<temp_rotation;
    }
    if(temp_rotation!=NULL)
    {
        setRotation(temp_rotation);
    }
}
void Bus::MoveNextPoint(const QGeoCoordinate coordinate1,
                        const QGeoCoordinate coordinate2)
{

    if(coordinate1==coordinate2)
    {
        qDebug()<<"the same point ";
        return ;
    }
    double dx=0.000005,dy=0.000005;//设置步长间隔
    int step_num;//统计步长
    //计算差值
    double diff_x=coordinate1.latitude()-coordinate2.latitude();
    double diff_y=coordinate1.longitude()-coordinate2.longitude();//注意地图坐标体系变化
    //设置基本方向
//    if(diff_x<0)
//    {
//        dx=-dx;
//    }
//    if(diff_y<0)
//    {
//        dy=-dy;
//    }
    //计算步长和转动角度
    if(diff_y<=0.000005&&diff_y>=-0.000005&&
       diff_x<=0.000005&&diff_x>=-0.000005){
        dx=0;
        dy=0;
        //ToDo 计算转动角度
    }else if(diff_x<=0.000005&&diff_x>=-0.000005){
        step_num=floor(qAbs(diff_y/dy));
        dx=0;
    }else if(diff_y<=0.000005&&diff_y>=-0.000005) {
        step_num=floor(qAbs(diff_x/dx));
        dy=0;
    }else {//x,y都不为0
        step_num=floor(qAbs(diff_x/dx));
        //计算斜率K
        dy=dx*(diff_y/diff_x);
    }
    //设置动画时钟
    bus_time_line_=new QTimeLine(100*step_num,this);
    bus_time_line_->setFrameRange(0,step_num);
    connect(bus_time_line_,&QTimeLine::frameChanged,this, [=](int value) {
        qDebug() << value;
        this->Move(dx,dy);
    });
    //更改地图起点坐标
    this->setCoordinate(coordinate1);
    bus_time_line_->start();
}
void Bus::LuShu()
{
    tool.TestNoteTool("LuShu",0);
    MoveNextPoint(tool.WPS84ToGCJ02(30.5563134000,103.9938400000),
                  tool.WPS84ToGCJ02(30.5571043000,103.9934402500));
    tool.TestNoteTool("LuShu ",1);
}
