/**
 * @file bus.h
 * @brief bus类主要头文件
 * @details 实现Bus类方法，在地图上显示公交bus，并且提供网络请求接口和自动动画接口
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2020-12-25 18:53:59
 * @copyright Copyright (c) 2020  IRLSCU
 * @par 修改日志:
 * <table>
 * <tr>
 *    <th> Commit date</th>
 *    <th> Version </th>
 *    <th> Author </th>
 *    <th> Description </th>
 * <tr>
 *    <td> 2018-12-10 周一  17:06:21 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td>实现Bus类方法，在地图上显示公交bus，并且提供网络请求接口和自动动画接口</td>
 * </tr>
 * <tr>
 *    <td> 2019-3-17 21:23:00 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td>修复 bug QDeclarativeGeoMapQuickItem没有虚析构函数在使用销毁时容易产生内存泄漏,将其转变为成员变量</td>
 * </tr>
 * </table>
 */

#ifndef BUS_H
#define BUS_H

#include <QString>
#include <QQuickItem>
#include <QtLocation/private/qdeclarativegeomapquickitem_p.h>
#include <QtQuick/private/qquickimage_p.h>
#include <QTimeLine>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>

#include "src/tool.h"

/**
 * @brief Bus公交UI抽象
 * @details bus 类的主要设计思路和数据类型： \n
 * 基本信息数据定义： \n
 * 1.公交车ID 2.公交车名称  3.所属线路编号 4.附加基本信息 5.公交驾驶员信息 \n
 * 功能实现成员变量： \n
 * 1.指向地图 2.储存线路 3.公交车图标 4.信息关键点（停靠关键点） 5.小车转动角度,6.时间定时器 \n
 * 实现重要功能： \n
 * 请求网络得出车辆位置，并在地图中显示位置 \n
 * 
 * @todo 代码解耦 \n
 * bus对应功能代码过重，应该将其拆解为LuShu类和位置更新类,以及基础信息类、UI函数类四个类，避免耦合 \n
 *
 */
class Bus : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Bus object
     * @param  parent           My Param doc
     */
    explicit Bus(QObject *parent = nullptr);
    /**
     * @brief Destroy the Bus object
     */
    ~Bus();
    /**
     * @brief Bus 其构造
     * @param new_coordinate
     */
    Bus(const QGeoCoordinate new_coordinate);
    /**
     * @brief Construct a new Bus object
     * @param  new_coordinate   初始化位置坐标
     * @param  new_path         初始化的路径path
     * @param  iocn_path        ioc图片qrc位置
     */
    Bus(const QGeoCoordinate new_coordinate,
        QList<QGeoCoordinate> new_path,
        const QUrl iocn_path);

    /**
     * @brief bus_id bus对应编号，方便快速查找
     * @return 当前bus对应编号
     */
    inline QString bus_id() { return bus_id_; }
    /**
     * @brief Set the bus id object
     * @param  input_bus_id     bus id
     */
    inline void set_bus_id(const QString input_bus_id) { bus_id_ = input_bus_id; }
    /**
     * @brief  获取当前车辆的名称
     * @return QString  车辆名称QString 字符串
     */
    inline QString bus_name() { return bus_name_; }
    /**
     * @brief Set the bus name object
     * @param  input_name      输入名称
     */
    inline void set_bus_name(const QString input_name) { bus_name_ = input_name; }
    /**
     * @brief  获取公交线路编号
     * @return QString 
     */
    inline QString bus_line_number() { return bus_line_number_; }
    /**
     * @brief Set the bus line number object
     * @param  input_bus_number 新的公交线路编号
     */
    inline void set_bus_line_number(const QString input_bus_number) { bus_line_number_ = input_bus_number; }
    /**
     * @brief  额外的描述信息
     * @return QString 描述信息字符串
     */
    inline QString bus_information() { return bus_information_; }
    /**
     * @brief Set the bus information object
     * @param  input_bus_information bus的额外描述信息
     */
    inline void set_bus_information(const QString input_bus_information) { bus_information_ = input_bus_information; }
    /**
     * @brief  驾驶员信息
     * @return QString 
     */
    inline QString bus_diver() { return bus_diver_; }
    /**
     * @brief Set the bus diver object 
     * @param  input_bus_diver  新的驾驶员信息
     */
    inline void set_bus_diver(const QString input_bus_diver) { bus_diver_ = input_bus_diver; }
    /**
     * @brief  bus对应的地图抽象图标类，主要是用于绘图和相关坐标操作,属于地图插件中的必要绘图类
     * @return QDeclarativeGeoMapQuickItem* 
     */
    inline QDeclarativeGeoMapQuickItem *bus_quick_item() { return this->bus_quick_item_; }
    /**
     * @brief Set the bus quick item object
     * @param  quick_item       车辆图标类
     */
    inline void set_bus_quick_item(QDeclarativeGeoMapQuickItem *quick_item) { this->bus_quick_item_ = quick_item; }
    /**
     * @brief 车辆运行是否已经停止
     * @return true  已经停止
     * @return false 没有停止
     */
    inline bool is_stop() { return is_stop_; }
    /**
     * @brief 是否处于循环线路中
     * @return true     处于循环线路中
     * @return false    没有处于循环线路中
     */
    inline bool is_cricle() { return is_cricle_; }
    /**
     * @brief Set the is cricle object
     * @param  isCricle         车辆行驶是否循环
     */
    inline void set_is_cricle(const bool isCricle) { is_cricle_ = isCricle; }
    /**
     * @brief  车辆行驶路径关键点，主要用于路书操作
     * @return QList<QGeoCoordinate> 
     */
    inline QList<QGeoCoordinate> bus_path_coordinates() { return bus_path_coordinates_; }
    /**
     * @brief Set the bus path coordinates object
     * @param  new_path         新的行驶路径
     */
    inline void set_bus_path_coordinates(QList<QGeoCoordinate> new_path) { bus_path_coordinates_ = new_path; }
    /**
     * @brief  车辆图标图片类指针，用于获取车辆绘图使用的图片数据指针
     * @return QQuickImage* 图片数据指针
     */
    inline QQuickImage *bus_iocn() { return bus_iocn_; }
    /**
     * @brief Set the bus iocn object
     * @param  iocn_image       My Param doc
     */
    inline void set_bus_iocn(QQuickImage *iocn_image) { bus_iocn_ = iocn_image; }
    /**
     * @brief Set the bus iocn 图标图片，所在路径，一般是qrc路径
     * @param  iocn_source_url  qrc图片路径
     */
    void set_bus_iocn(const QUrl iocn_source_url);
    /**
     * @brief 设置图片缩放尺寸，方便控制iocn 图标大小
     * @param  Scale            相对原图的缩放比例
     */
    void SetBusIocnScale(double Scale);
    /**
     * @brief bus所属的map对象指针，用于进行map的相关操作
     * @param  qMap             QQuickMap的数据指针
     */
    void SetMap(QDeclarativeGeoMap *qMap); //更改Bus的所属map

    /* 更新函数 start */

    /**
     * @brief 变量初始化和重置函数，主要用于初始化各种参数
     */
    void Init();
    /**
     * @brief 图片等更新函数，主要用于实现地图上各种图片设施的更新
     */
    void Updata();
    /**
     * @brief 动画中刷新车辆图标，更新车辆在地图中显示的位置
     */
    void UpdataPosition();
    /* 更新函数 end */

    /* 路书相关函数  start */
    /**
     * @brief GetPixelDistance 获取地图中两个像素点距离
     * @param coordinate1   像素点相对坐标1
     * @param coordinate2   像素点相对坐标2
     * @return 两个点的距离
     */
    double GetPixelDistance(const QGeoCoordinate coordinate1,
                            const QGeoCoordinate coordinate2);
    /**
     * @brief 移动到bus_path_coordinates_中所指定的下一个关键点
     * @param  index            下一个关键点的指定序号
     */
    void MoveNextIndex(const int index);
    /**
     * @brief  为了让车辆在两个点之间的移动，更加平滑，需要进行多点模拟和插值，这里是线性插值函数
     * @details 线性插值主要是对init_pos～target_pos两个值进行插值，获取current_count 对应的数据计算公式为: \n
     * current_count = init_pos+(target_pos-init_pos)/count*current_count
     * @param  init_pos         path 队列点中的起始坐标，
     * @param  target_pos       path 队列中的
     * @param  current_count    当前移动的帧数
     * @param  count            总过帧数
     * @return double           对应current_count 线性插值值
     */
    double LinearInterpolation(const double init_pos,
                               const double target_pos,
                               const int current_count,
                               const int count);
    //设置车辆的偏转

    /**
     * @brief 设置车辆图标偏转
     * @details 为了让车辆在运行过程中，可以根据行驶路线进行动态的转向变化 设置的车辆转向函数 \n 
     * 主要是根据起始点和目标点的坐标差值，计算转向的角度，
     * @param  coordinate1      起始坐标点
     * @param  coordinate2      终止坐标点
     */
    void SetRotation(const QGeoCoordinate coordinate1,
                     const QGeoCoordinate coordinate2);
    /**
     * @brief 路径转置函数，主要用于路书中
     * @details 当自动路书中，车辆到达路径尽头时，车辆路径进行翻转，最终实现回程的效果 
     */
    void ChangePath();
    /* ------ 路书常用控制函数 ------ */
    /**
     * @brief 封装路书开始启动类，主要含有日志信息，常使用在测试代码中
     */
    void LuShu();
    /**
     * @brief 路书开始
     */
    void LuShuStart();
    /**
     * @brief 路书暂停
     */
    void LuShuPause();
    /**
     * @brief 路书停止
     */
    void LuShuStop();
    /**
     * @brief 初始化socket通信
     * @details 实时位置显示模式中使用，此模式中主要位置坐标更新，由socket TCP通信完成 \n
     * 因此需要进行位置更新的socket初始化操作 \n
     * @todo \n 
     * 1. 增加车辆远程socket地址通信配置界面，可以直接在操作界面中更改对应的远程地址 \n
     * 2. 添加配置文件载入和写入函数和界面，实现车辆的可配置化 \n
     */
    void InitSocket(); //初始化socket通信
    /* 路书相关函数 end  */

    //----- 位置存储到数据库关键代码 start------
    /**
     * @brief is_save_gps 是否正在存储GPS数据
     * @return false/true 正在/不在存储
     *
     */
    inline bool is_save_gps() { return is_save_gps_; }
    /**
     * @brief 是否存储GPS坐标 
     * @param  is_save         是否存储
     */
    inline void set_is_save_gps(bool is_save) { is_save_gps_ = is_save; }
    /**
     * @brief record_id 查看当前的记录Id
     * @return  数据库中的记录ID
     */
    inline int record_id() { return record_id_; }
    /**
     * @brief set_record_id 设置数据库记录Id
     * @param new_record_id 新的记录Id
     */
    inline void set_record_id(int new_record_id) { record_id_ = new_record_id; }
    /**
     * @brief 将新的位置坐标存储到数据库中
     * @param coordinate 坐标数据点
     * @param record_id  对应的历史记录编号
     */
    void SaveCoordinateToSql(const QGeoCoordinate coordinate, int record_id);
    //----- 位置存储到数据库关键代码  end ------

    /**
     * @brief set_ip_address 设置记录服务器对应的ip地址
     * @param address IP地址的字符串形式
     */
    inline void set_ip_address(QString address) { ip_address_ = address; }
    /**
     * @brief 获取对应的ip地址
     * @return 返回ip地址字符串
     */
    inline QString ip_address() { return ip_address_; }
    /**
     * @brief set_port 设置网络请求对应的端口
     * @param i         网络请求端口号
     */
    inline void set_port(unsigned int i) { port_ = i; }
    /**
     * @brief port 端口号查询请求函数
     * @return 对应的端口号
     */
    inline unsigned port() { return port_; }

    //相关槽函数
public slots:
    /*http 通信 start */
    /**
     * @brief  槽函数--车辆坐标定位模拟更新函数
     * @details 当模式处于远程接受网络位置信息时，调用函数 \n
     * 请求后端并，更新位置,现有的请求脚本是php的模拟脚本函数 \n
     *  主要使用的协议是HTTP协议 \n
     * @note 此接口仅仅在测试中使用
     */
    void UpdataCoordinatesByNet();
    /**
     * @brief  槽函数--Http请求回复后的网络位置更新响应函数
     * @param  reply            响应网络消息
     */
    void GetReplyFinished(QNetworkReply *reply);
    /*http 通信 end */

    /*socket 通信 start*/
    /**
     * @brief 槽函数--socket通信更新位置函数，直接使用socket进行位置更新
     */
    void UpdateCoordinatesBySocket();
    /**
     * @brief 槽函数--当有消息过来时，进行数据的读取
     */
    void SocketReadData();
    /**
     * @brief 槽函数--socket关闭时的连接处理函数
     */
    void SocketDisconnected();
    /*socket 通信 end*/

    /*LuShu槽函数 start*/
    /**
     * @brief  LuShu的相关槽函数，主要是移动到指定位置
     * @param  dx               x方向上的增量
     * @param  dy               y方向上的增量
     */
    void Move(const double dx,
              const double dy);
    /**
     * @brief  移动到下一个坐标点
     * @param  coordinate1      原来的坐标点
     * @param  coordinate2      新的坐标点
     */
    void MoveNextPoint(const QGeoCoordinate coordinate1,
                       const QGeoCoordinate coordinate2);
    /**
     * @brief 设置新的坐标位置带偏转的
     * @details 会根据当前位置和目标位置设置偏转
     * @param  new_coordinate   新坐标参数
     */
    void SetCoordinate(const QGeoCoordinate new_coordinate);
    /**
     * @brief 使用WPS84坐标体系，来实现位置更新
     * @details 和 @link Bus::SetCoordinate 功能相同 \n 
     * 增加了WPS84的坐标体系的转换
     * @param  new_coordinate   My Param doc
     */
    void SetCoordinateFromWPS84(const QGeoCoordinate new_coordinate); //从标准坐标更新位置信息
    /*LuShu槽函数 end*/

    /*存储gps的槽函数 start*/
    /**
     * @brief  gps存储槽函数，主要是存储当前的GPS信息
     * @param  record_id      当前记录对应的主键，方便查找
     */
    void StartSaveGPS(int record_id);
    /**
     * @brief 停止存储GPS
     */
    void StopSaveGPS();
    /*存储gps的槽函数 end*/

private:
    /*基本信息 start*/
    QString bus_id_;          ///< bus 编号
    QString bus_name_;        ///< bus 名称
    QString bus_line_number_; ///< 对应公交线路编号
    QString bus_information_; ///< 额外的附加信息
    QString bus_diver_;       ///< 对应的驾驶员信息
    /*基本信息 end*/

    /*重要信息 start*/
    QList<QGeoCoordinate> bus_path_coordinates_;            ///< 线路关键点列表
    QQuickImage *bus_iocn_ = nullptr;                       ///< 公交车图标iocn指针
    QDeclarativeGeoMapQuickItem *bus_quick_item_ = nullptr; ///< 所属地图指针
    /*重要信息 end*/
    /*位置更新信息 start*/
    QTimeLine *bus_time_line_ = nullptr; ///< 位置更新动画时间线
    QTimer *bus_timer_ = nullptr;        ///< 位置更新时间指针
    /*位置更新信息 end*/
    /*路书动画 start*/
    QList<QTimeLine *> bus_time_line_list_; ///< 路书时间计时器列表，主要用来实现动画平滑化
    int line_index_ = 0;                    ///< 当前点索引初始化为0
    double bus_speed_ = 5;                  ///< 公交车速度(km/s)
    bool is_cricle_ = true;                 ///< 动画路书是否循环
    bool is_pause = false;                  ///< 是否暂停
    bool is_stop_ = false;                  ///< 是否停止，不停止;是否停止，当为true时，车辆已经停止
    bool is_return = false;                 ///< 是否正在返程
    /*路书动画 end*/
    QTcpSocket *socket_ = nullptr;         ///< socket通信成员变量
    QString ip_address_ = "112.74.188.50"; ///< 设置ip地址，默认IP地址 "112.74.188.50"
    unsigned int port_ = 20721;            ///< 设置端口号，默认端口号 为 20721
    bool is_save_gps_ = false;             ///< 存储坐标相关信息
    int record_id_ = NULL;                 ///< 存储时的记忆编号
};

#endif // BUS_H
