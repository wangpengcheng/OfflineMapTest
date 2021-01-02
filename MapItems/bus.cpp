#include "bus.h"
#include <QtMath>
#include <algorithm>
Bus::Bus(QObject *parent) : QObject(parent)
{
    Init();
    Updata();
}
Bus::~Bus()
{
    DELETE_QOBJECT(bus_iocn_);
    DELETE_QOBJECT(bus_time_line_);
    DELETE_QOBJECT(bus_timer_);
    DELETE_QOBJECT(socket_);
}

Bus::Bus(const QGeoCoordinate new_coordinate)
{
    Init();
    Updata();
    if (new_coordinate.isValid())
    {
        this->bus_quick_item_->setCoordinate(new_coordinate);
    }
    else
    {
        qDebug() << "this input coordinate is empty ";
    }
}
Bus::Bus(const QGeoCoordinate new_coordinate,
         QList<QGeoCoordinate> new_path,
         const QUrl iocn_path)
{
    Init();
    Updata();
    if (new_coordinate.isValid() && !new_path.isEmpty() && !iocn_path.isEmpty())
    {
        this->bus_quick_item_->setCoordinate(new_coordinate);
        set_bus_path_coordinates(new_path);
        set_bus_iocn(iocn_path);
    }
    else
    {
        qDebug() << "input object is empty ,please check again";
    }
}

void Bus::set_bus_iocn(const QUrl iocn_source_url)
{
    bus_iocn_->setSource(iocn_source_url);
}
void Bus::SetBusIocnScale(double Scale)
{
    bus_iocn_->setSize(QSize(this->bus_iocn_->width() * Scale,
                             this->bus_iocn_->height() * Scale));
}
void Bus::Init()
{
    bus_id_ = "";          //公交站编号
    bus_name_ = "";        //公交站名称
    bus_line_number_ = ""; //公交线路编号
    bus_information_ = ""; //公交信息
    bus_diver_ = "";       //公交驾驶人员信息
    bus_time_line_ = nullptr;
    bus_timer_ = nullptr;
    bus_quick_item_ = new QDeclarativeGeoMapQuickItem();
#ifdef JANGAN                                                     //判断是否为江安
    QGeoCoordinate InitCoordinate(30.5567330000, 103.9997920000); //江安
#else
    QGeoCoordinate InitCoordinate(30.631091622, 104.081949595); //望江
#endif
    this->bus_quick_item_->setCoordinate(InitCoordinate); //设置默认位置

    bus_iocn_ = nullptr; //防止内存分配失败
    bus_iocn_ = new QQuickImage();
    bus_iocn_->setSource(QUrl("qrc:/img/car_up.png"));
    this->bus_quick_item_->setRotation(90); //设置图片旋转90度
    //bus_station_iocn_->setSize(QSize(50,50));//设置默认大小
    InitSocket();
}
void Bus::InitSocket()
{
    socket_ = new QTcpSocket();
    QObject::connect(socket_, &QTcpSocket::readyRead, this, &Bus::SocketReadData);
    QObject::connect(socket_, &QTcpSocket::disconnected, this, &Bus::SocketDisconnected);
    //连接信号槽
    qDebug() << "GPS address is" << ip_address_ << ":" << port_ << ";" << endl;
}
void Bus::Updata()
{
    this->bus_quick_item_->setSourceItem(bus_iocn_); //将图片添加到Item
    this->bus_quick_item_->setAnchorPoint(QPointF(bus_iocn_->width() * 0.5,
                                                  bus_iocn_->height() * 0.5)); //设置偏移
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
    bus_timer_ = new QTimer(this);
    connect(bus_timer_, SIGNAL(timeout()), this, SLOT(UpdataCoordinatesByNet()));
    bus_timer_->start(5000); //设置更新间隔为5s
}

//通过网络Socket通信指直接跟新位置
void Bus::UpdateCoordinatesBySocket()
{
    //没有初始化成功再次初始化
    if (socket_ == nullptr)
    {
        InitSocket();
    }
    //取消已有的连接
    socket_->abort();
    //连接服务器
    socket_->connectToHost(ip_address_, port_);
    if (!socket_->waitForConnected(30000))
    {
        qDebug() << "Connection failed!";
        return;
    }
    qDebug() << "Connect successfully!";
}
void Bus::SocketReadData()
{
    QByteArray buffer;
    //读取缓冲区数据
    buffer = socket_->readLine();
    //qDebug()<<buffer;
    QString cout_string;
    cout_string.prepend(buffer);
    QString temp_string_1 = cout_string.split("\n")[0];
    qDebug() << temp_string_1.simplified();
    QStringList string_list = temp_string_1.simplified().split(" ");
    QString latitude = string_list[2];     //纬度
    QString longitudinal = string_list[3]; //经度
    QGeoCoordinate crrut_coordinate = QGeoCoordinate(latitude.toDouble(), longitudinal.toDouble());
    //注意坐标转换
    this->bus_quick_item_->setCoordinate(Tool::WPS84ToGCJ02FromCoord(crrut_coordinate));
    if (is_save_gps_ &&
        record_id_ != NULL)
    {
        SaveCoordinateToSql(crrut_coordinate, record_id_);
    }
}
void Bus::SocketDisconnected()
{
    qDebug() << "Disconnected!";
}
//通过后台ajax更新位置请求
void Bus::UpdataCoordinatesByNet()
{
    //设置网络请求
    QNetworkAccessManager *manage = new QNetworkAccessManager(this);
    QNetworkRequest network_request;
    //注意这里的请求是模拟的请求数据
    network_request.setUrl(QUrl(QString("http://118.24.113.233/location_point_simulation.php")));
    /*建立connect，ReplyFinished为自定义槽函数,*/
    connect(manage, SIGNAL(finished(QNetworkReply *)), this, SLOT(GetReplyFinished(QNetworkReply *)));

    /*发送get网络请求*/
    manage->get(network_request);
}
void Bus::GetReplyFinished(QNetworkReply *reply)
{
    QJsonObject data = QJsonDocument::fromJson(reply->readAll()).object();
    double x = data.value(QString("bus_position")).toObject().value("x").toDouble();
    double y = data.value(QString("bus_position")).toObject().value("y").toDouble();
    bus_quick_item_->setCoordinate(QGeoCoordinate(x, y));
    // MoveNextPoint(this->coordinate(),QGeoCoordinate(x,y));
    qDebug() << this->bus_quick_item_->coordinate();
}
/*网络位置请求 end*/
//计算像素点差距
double Bus::GetPixelDistance(const QGeoCoordinate coordinate1,
                             const QGeoCoordinate coordinate2)
{
    QPointF point1, point2;
    auto parent_map = this->bus_quick_item_->quickMap();
    point1 = parent_map->fromCoordinate(coordinate1);
    point2 = parent_map->fromCoordinate(coordinate2);
    double result = qSqrt(qPow((point1.x() - point2.x()), 2) + qPow((point1.y() - point2.y()), 2));
    qDebug() << "this distance is " << result;
    return result;
}
void Bus::Move(const double dx,
               const double dy)
{
    QGeoCoordinate old_point, new_point;
    double temp_rotation = NULL;                     //转动角度;-180~180,
    old_point = this->bus_quick_item_->coordinate(); //获取中心点
    double x, y;
    x = old_point.latitude() + dx;
    y = old_point.longitude() + dy;
    // 获取新的位置
    new_point = QGeoCoordinate(x, y);
    this->bus_quick_item_->setCoordinate(new_point);
    //计算转动方向
    if (dx == 0 && dy == 0)
    {
        qDebug() << "no move ";
    }
    else
    {
        temp_rotation = -qRadiansToDegrees(qAtan2(dx, dy)); //注意坐标体系转换变号，负号反向
        //qDebug()<<temp_rotation;
    }
    if (temp_rotation != NULL)
    {
        this->bus_quick_item_->setRotation(temp_rotation);
    }
}
void Bus::MoveNextPoint(const QGeoCoordinate coordinate1,
                        const QGeoCoordinate coordinate2)
{
    if (!coordinate1.isValid() || !coordinate2.isValid())
    {
        qDebug() << "input is valisd";
        return;
    }
    else if (coordinate1 == coordinate2)
    {
        qDebug() << "the same point ";
        return;
    }
    //更改地图起点坐标
    //this->setCoordinate(coordinate1);
    //步长，米/秒
    int timer = 10;
    double step = this->bus_speed_ / (1000 / timer); //根据速度计算每步步长:每步多少米
    //根据速度计算时间
    if (bus_speed_ == 0)
    {
        bus_speed_ = 10;
    }
    //计算所需时间
    int total_time = qFloor(1000 * (Tool::GetDistance(coordinate1, coordinate2) / bus_speed_));
    //总的步长
    int count = qFloor(Tool::GetDistance(coordinate1, coordinate2) / step);
    //如果小于1直接移动到下一点
    if (count < 1)
    {
        this->MoveNextIndex(++this->line_index_); //直接移动到下一个
        return;
    }
    //设置动画时钟
    QTimeLine *temp_timeline = new QTimeLine(total_time, this);
    temp_timeline->setFrameRange(0, count);
    //设置时间变化曲线
    temp_timeline->setCurveShape(QTimeLine::LinearCurve);
    //将计时器添加到队列中
    this->bus_time_line_list_.append(temp_timeline);
    //绑定运动事件
    connect(temp_timeline, &QTimeLine::frameChanged, this, [=](int value) {
        //计算步长
        double pixe_point_x = LinearInterpolation(coordinate1.latitude(), coordinate2.latitude(), value, count);
        double pixe_point_y = LinearInterpolation(coordinate1.longitude(), coordinate2.longitude(), value, count);
        QGeoCoordinate temp_result(pixe_point_x, pixe_point_y); //输出坐标值
        this->bus_quick_item_->setCoordinate(temp_result);      //设置临时坐标
        //this->SaveCoordinateToSql(temp_result,5);
        if (is_save_gps_ &&
            record_id_ != NULL)
        {
            SaveCoordinateToSql(temp_result, record_id_);
        }
    });
    //绑定结束事件
    connect(temp_timeline, &QTimeLine::finished, this, [=]() {
        MoveNextIndex(++this->line_index_); //移动到下一个点
    });
    //计算转向角
    SetRotation(coordinate1, coordinate2);
    temp_timeline->start(); //动画开始
}
void Bus::LuShu()
{
    Tool::TestNoteTool("LuShu", 0);
    this->LuShuStart(); //开始动画
    Tool::TestNoteTool("LuShu ", 1);
}
void Bus::SetMap(QDeclarativeGeoMap *qMap)
{
    if (qMap != nullptr)
    {
        qMap->addMapItem(bus_quick_item_);
    }
    else
    {
        qDebug() << "this Map point is empty!";
    }
}
void Bus::MoveNextIndex(const int index) //移动到下一个位置
{
    if (index < this->bus_path_coordinates_.size() - 1 && index >= 0)
    {
        QGeoCoordinate frist_point = bus_path_coordinates_.at(index);
        QGeoCoordinate last_point = bus_path_coordinates_.at(index + 1);
        MoveNextPoint(frist_point, last_point);
    }
    else if (index == bus_path_coordinates().size() - 1) //如果到达最后一个点
    {
        if (is_cricle_)
        {   //如果确定循环
            //console.log(f.i);
            line_index_ = 0;
            ChangePath();           //更改路径
            LuShuStart();           //再次运行；
            is_return = !is_return; //更改信号变量
        }
        is_stop_ = true; //确定已经停止。
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
    double temp_result = (double)(c * t / d + b);
    //double temp_result=(double)(c/d);
    return temp_result;
}
void Bus::SetRotation(const QGeoCoordinate coordinate1,
                      const QGeoCoordinate coordinate2)
{
    double temp_rotation = NULL;
    const double const_step = 1;
    double dx = const_step, dy = const_step; //设置步长间隔
    //计算差值
    double diff_x = coordinate2.latitude() - coordinate1.latitude();
    double diff_y = coordinate2.longitude() - coordinate1.longitude(); //注意地图坐标体系变化
    //计算步长和转动角度
    dx = (diff_x / qAbs(diff_x)) * dx;
    if (diff_y == 0 &&
        diff_x == 0)
    {
        dx = 0;
        dy = 0;
        //ToDo 计算转动角度
    }
    else if (diff_x == 0)
    {
        dx = 0;
    }
    else if (diff_y == 0)
    {
        dy = 0;
    }
    else
    { //x,y都不为0
        //计算斜率K
        dy = dx * (diff_y / diff_x);
    }

    //计算转动方向
    if (dx == 0 && dy == 0)
    {
        qDebug() << "no move ";
    }
    else
    {
        temp_rotation = -qRadiansToDegrees(qAtan2(diff_x, diff_y)); //注意坐标体系转换变号，负号反
    }
    if (temp_rotation != NULL)
    {
        this->bus_quick_item_->setRotation(temp_rotation);
    }
}
void Bus::ChangePath() //转置队列
{
    int temp_size = this->bus_path_coordinates_.size();
    for (int i = 0; i < temp_size / 2; ++i)
    {
        this->bus_path_coordinates_.swap(i, temp_size - i - 1);
    }
}
void Bus::LuShuStart()
{
    int len = this->bus_path_coordinates_.size();
    //不是第一次点击开始,并且小车还没到达终
    if ((this->line_index_ != 0) &&
        (this->line_index_ < len - 1))
    {
        //没按pause再按start不做处理
        if (!this->is_pause)
        {
            return;
        }
        else if (!this->is_stop_)
        {
            //按了pause按钮,并且再按start，直接移动到下一点
            //并且此过程中，没有按stop按钮
            //防止先stop，再pause，然后连续不停的start的异常
            this->MoveNextIndex(++this->line_index_);
        }
    }
    else
    {                           //第一次点击开始，或者点了stop之后点开始
                                //重置状态
        this->MoveNextIndex(0); //移动到1
        this->is_pause = false;
        this->is_stop_ = false;
    }
}
void Bus::LuShuPause()
{
    this->is_pause = !this->is_pause;
    this->bus_time_line_list_.at(this->line_index_)->setPaused(this->is_pause); //停止动画
}
void Bus::LuShuStop()
{

    this->is_stop_ = true;
    this->bus_time_line_list_.at(this->line_index_)->stop(); //停止动画
    this->line_index_ = 0;                                   //重置起点
    if (is_return)                                           //是否在返程
    {
        this->ChangePath();
    }
}
/*
 * input coordinate ,record id
 *
*/
void Bus::SaveCoordinateToSql(const QGeoCoordinate coordinate, int record_id)
{
    //设置网络请求
    QNetworkAccessManager *save_manage = new QNetworkAccessManager(this);
    QNetworkRequest network_request;
    network_request.setUrl(QUrl(QString("http://localhost/re_save_gps.php")));

    network_request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    connect(save_manage, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply) {
        // 获取http状态码
        QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
#ifdef MyTest
        if (statusCode.isValid())
        {
            qDebug() << "status code=" << statusCode.toInt();
        }
        QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
        if (reason.isValid())
        {
            qDebug() << "reason=" << reason.toString();
        }
#endif
        QNetworkReply::NetworkError err = reply->error();
        if (err != QNetworkReply::NoError)
        {
            qDebug() << "Failed: " << reply->errorString();
        }
        else
        {
            // 获取返回内容
            QJsonObject data = QJsonDocument::fromJson(reply->readAll()).object();
        }
    });

    //准备发送的数据
    //获取当前时间
    QString currt_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    QJsonObject send_data;
    send_data.insert("latitude", coordinate.latitude());
    send_data.insert("longitude", coordinate.longitude());
    send_data.insert("record_id", record_id);
    send_data.insert("gps_time", currt_time); //存储时间
    //将Json转化为数据流
    QByteArray send_data_array = QJsonDocument(send_data).toJson();
    /*发送get网络请求*/
    save_manage->post(network_request, send_data_array);
}
void Bus::SetCoordinate(const QGeoCoordinate new_coordinate)
{
    if (new_coordinate.isValid())
    {
        //设置旋转
        if (bus_quick_item_->coordinate().isValid())
        {
            this->SetRotation(bus_quick_item_->coordinate(), new_coordinate);
        }
        //更新坐标位置
        bus_quick_item_->setCoordinate(new_coordinate);
    }
}
void Bus::SetCoordinateFromWPS84(const QGeoCoordinate new_coordinate)
{
    SetCoordinate(Tool::WPS84ToGCJ02FromCoord(new_coordinate));
}

void Bus::StartSaveGPS(int record_id)
{
    //更改record id;
    Tool::TestNoteTool("StartSaveGPS", 0);
    record_id_ = record_id;
    is_save_gps_ = true;
}
void Bus::StopSaveGPS()
{
    is_save_gps_ = false;
    Tool::TestNoteTool("StopSaveGPS", 1);
}
