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
void Bus::SetBusIocnScale(double Scale)
{
    bus_iocn_->setSize(QSize(this->bus_iocn_->width()*Scale,
                             this->bus_iocn_->height()*Scale));
}
void Bus::Init()
{
    bus_id_="";//公交站编号
    bus_name_="";//公交站名称
    bus_line_number_="";//公交线路编号
    bus_information_="";//公交信息
    bus_diver_="";//公交驾驶人员信息
    QGeoCoordinate InitCoordinate(30.5567330000,103.9997920000);
//    bus_path_coordinates_.append(InitCoordinate);
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
//计算像素点差距
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
    //qDebug()<<old_point;
    double x,y;
    x=old_point.latitude()+dx;
    y=old_point.longitude()+dy;
    //qDebug()<<"x:"<<x<<"y:"<<y;
    //qDebug()<<"dx:"<<dx<<"dy:"<<dy;
    new_point=QGeoCoordinate(x,y);
    qDebug()<<new_point;
    this->setCoordinate(new_point);
    //计算转动方向
    if(dx==0&&dy==0){
        qDebug()<<"no move ";
    }else
    {
        temp_rotation=-qRadiansToDegrees(qAtan2(dx,dy));//注意坐标体系转换变号，负号反向
        //qDebug()<<temp_rotation;
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
    //更改地图起点坐标
    //this->setCoordinate(coordinate1);
    //步长，米/秒
    int timer = 10;
    double step = this->bus_speed_/(1000/timer);//根据速度计算每步步长
    //根据速度计算时间
    if(bus_speed_==0)
    {
        bus_speed_=10;
    }
    //计算所需时间
    int total_time=qFloor(1000*(tool.GetDistance(coordinate1,coordinate2)/bus_speed_));
    //总的步长
    int count =qFloor(this->GetPixelDistance(coordinate1, coordinate2)/step);
    //如果小于1直接移动到下一点
    if (count < 1)
    {
        this->MoveNextIndex(++this->line_index_);//直接移动到下一个
        return;
    }
    //设置动画时钟
    QTimeLine *temp_timeline=new QTimeLine(total_time,this);
    temp_timeline->setFrameRange(0,count);
    //设置时间变化曲线
    temp_timeline->setCurveShape(QTimeLine::LinearCurve);
    //将计时器添加到队列中
    this->bus_time_line_list_.append(temp_timeline);
    //绑定运动事件
    connect(temp_timeline,&QTimeLine::frameChanged,this, [=](int value) {
            qDebug() << value;
        //计算步长
         double pixe_point_x=LinearInterpolation(coordinate1.latitude(),coordinate2.latitude(),value,count);
         double pixe_point_y=LinearInterpolation(coordinate1.longitude(),coordinate2.longitude(),value,count);
         QGeoCoordinate temp_result(pixe_point_x,pixe_point_y);//输出坐标值
         this->setCoordinate(temp_result);
    });
    //绑定结束事件
    connect(temp_timeline,&QTimeLine::finished,this,[=]()
    {
        MoveNextIndex(++this->line_index_);//移动到下一个点
    });
    //计算转向角
    SetRotation(coordinate1, coordinate2);
    qDebug()<<this->coordinate();
    temp_timeline->start();//动画开始
}
void Bus::LuShu()
{
    tool.TestNoteTool("LuShu",0);
    this->LuShuStart();//开始动画
    tool.TestNoteTool("LuShu ",1);
}
void Bus::MoveNextIndex(const int index)//移动到下一个位置
{

    if (index < this->bus_path_coordinates().size()-1)
    {
        this->MoveNextPoint(this->bus_path_coordinates_.at(index),
                            this->bus_path_coordinates_.at(index+1));
    }else if(index==this->bus_path_coordinates().size()-1)//如果到达最后一个点
    {
        if(this->is_cricle_){//如果确定循环
              //console.log(f.i);
            this->line_index_=0;
            this->ChangePath();//更改路径
            this->LuShuStart();//再次运行；
//            //更改车辆iocn使得车辆翻转
//            if(this->is_return){
//               this->bus_iocn_->setSource(QUrl("qrc:/img/car_up1.png"));
//            }else {
//                this->bus_iocn_->setSource(QUrl("qrc:/img/car_up.png"));
//            }
            //更改信号变量
            this->is_return=!this->is_return;
        }
    }
}
double Bus::LinearInterpolation(const double init_pos,
                                const double target_pos,
                                const int current_count,
                                const int count)
{
    double b = init_pos;
    double c = target_pos - init_pos;
    int t = current_count;
    int d = count;
    double temp_result=(double)(c * t / d + b);
    //double temp_result=(double)(c/d);
    return temp_result;
}
void Bus::SetRotation(const QGeoCoordinate coordinate1,
                      const QGeoCoordinate coordinate2)
{
//    double deg = 0;
//    if(coordinate1.latitude()!= coordinate2.latitude()){
//           double tan = (coordinate1.longitude() - coordinate2.longitude())/(coordinate1.latitude() - coordinate2.latitude());
//           deg =qRadiansToDegrees(qAtan(tan));//注意坐标体系转换变号，负号反向
//                //degree  correction;
//           double atan  = qAtan(tan);
//           //deg = qRadiansToDegrees();
//           if(coordinate2.latitude()<coordinate1.latitude()){
//              deg = -deg + 90 + 90;

//           } else {
//              deg = -deg;
//           }
//             this->setRotation(deg);
//     }else {
//        double disy =coordinate2.longitude()-coordinate1.longitude() ;
//        double bias = 0;
//        if(disy > 0){
//           bias=-1;
//        }else{
//           bias = 1;
//        }
//        this->setRotation(-bias*90);

//    }
//     double temp_rotation=NULL;//转动角度;-180~180,
//    //计算转动方向
//    double dx=coordinate1.latitude() - coordinate2.latitude();
//    double dy=coordinate1.longitude() - coordinate2.longitude();
//    if(dx==0&&dy==0){
//        qDebug()<<"no move ";
//    }else
//    {
//        temp_rotation=-qRadiansToDegrees(qAtan2(dy,dx));//注意坐标体系转换变号，负号反向
//        //qDebug()<<temp_rotation;
//    }
//    if(temp_rotation!=NULL)
//    {
//        setRotation(temp_rotation);
//    }
        double temp_rotation=NULL;
        const double const_step=1;
        double dx=const_step,dy=const_step;//设置步长间隔
        //计算差值
        double diff_x=coordinate2.latitude()-coordinate1.latitude();
        double diff_y=coordinate2.longitude()-coordinate1.longitude();//注意地图坐标体系变化
        //计算步长和转动角度
        dx=(diff_x/qAbs(diff_x))*dx;
        if(diff_y==0&&
           diff_x==0){
            dx=0;
            dy=0;
            //ToDo 计算转动角度
        }else if(diff_x==0){
            dx=0;
        }else if(diff_y==0) {
            dy=0;
        }else {//x,y都不为0
            //计算斜率K
            dy=dx*(diff_y/diff_x);
        }

        //计算转动方向
        if(dx==0&&dy==0){
            qDebug()<<"no move ";
        }else{
            temp_rotation=-qRadiansToDegrees(qAtan2(diff_x,diff_y));//注意坐标体系转换变号，负号反
        }
        if(temp_rotation!=NULL)
        {
            setRotation(temp_rotation);
        }

}
void Bus::ChangePath()//转置队列
{
    int temp_size=this->bus_path_coordinates_.size();
    for(int i=0;i<temp_size/2;++i)
    {
        this->bus_path_coordinates_.swap(i,temp_size-i-1);
    }
}
void Bus::LuShuStart()
{
    auto me=this;
    int len = me->bus_path_coordinates_.size();
       //不是第一次点击开始,并且小车还没到达终
    if (me->line_index_!=0&& me->line_index_<len - 1) {
        //没按pause再按start不做处理
        if (!me->is_pause) {
               return;
        }else if(!me->is_stop){
            //按了pause按钮,并且再按start，直接移动到下一点
            //并且此过程中，没有按stop按钮
            //防止先stop，再pause，然后连续不停的start的异常
            me->MoveNextIndex(++me->line_index_);
        }
    }else {//第一次点击开始，或者点了stop之后点开始
           //重置状态
        this->MoveNextIndex(0);//移动到1
        this->is_pause = false;
        this->is_stop = false;
    }
}
void Bus::LuShuPause()
{
    this->is_pause=!this->is_pause;
    this->bus_time_line_list_.at(this->line_index_)->setPaused(this->is_pause);//停止动画
}
void Bus::LuShuStop()
{

    this->is_stop = true;
    this->bus_time_line_list_.at(this->line_index_)->stop();//停止动画
    this->line_index_= 0;//重置起点
    if(is_return)//是否在返程
    {
     this->ChangePath();
    }

}
