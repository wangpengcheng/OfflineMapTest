#ifndef BUS_H
#define BUS_H
/****************************************************************************
** @projectName   OfflineMapTest
** QT Version    5.11.1
** This file is part of the OfflineMapTest project.
** @file          bus.cpp
** @brief         Bus class
** @details       实现Bus类方法，在地图上显示公交bus，并且提供网络请求接口和自动动画接口
** @author        wangpengcheng
** @QQ            673018396
** @email         wangpengcheng2018@gmail.com
** @address       https://github.com/wangpengcheng/OfflineMapTest
** @date          2018-12-10 周一  17:06:21
** @example
**
** 示例代码
**
*****************************************************************************/
#ifndef QSTRING_H
#include <QString>
#endif
#ifndef QQUICKITEM_H
#include <QQuickItem>
#endif
#ifndef  QDECLARATIVEGEOMAPQUICKITEM_H
#include <QtLocation/private/qdeclarativegeomapquickitem_p.h>
#endif
#ifndef  QQUICKIMAGE_P_H
#include <QtQuick/private/qquickimage_p.h>
#endif
#ifndef QTIMELINE_H
#include <QTimeLine>
#endif
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#ifndef TOOL_H
#include "src/tool.h"
#endif
/*
 * bus 类的主要设计思路和数据类型：
 * 基本信息数据定义：
 * 1.公交车ID 2.公交车名称  3.所属线路编号 4.附加基本信息;公交驾驶员信息
 * 功能实现成员变量：
 * 1.指向地图 2.储存线路 3.公交车图标 4.信息关键点（停靠关键点） 5.小车转动角度,6.时间定时器
 * 实现重要功能：
 * 请求网络得出车辆位置，并在地图中显示位置
 * 2019-3-17 21:23:00 发现bug  QDeclarativeGeoMapQuickItem 没有虚析构函数在使用销毁时容易产生内存泄漏,将其转变为成员变量修复
 *
*/
class Bus: public QObject
{
     Q_OBJECT
public:
    Bus(QObject *parent = nullptr);
    ~Bus();
    Bus(QList<QGeoCoordinate> new_path);
    Bus(const QGeoCoordinate new_coordinate);
    Bus(const QGeoCoordinate new_coordinate,
        QList<QGeoCoordinate> new_path);
    Bus(const QGeoCoordinate new_coordinate,
        QList<QGeoCoordinate> new_path,
        const QUrl iocn_path);

     /*基本信息存取 start*/
    inline QString bus_id(){return bus_id_;}
    inline void set_bus_id(const QString input_bus_id){bus_id_=input_bus_id;}
    inline QString bus_name(){return bus_name_;}
    inline void set_bus_name(const QString input_name){bus_name_=input_name;}
    inline QString bus_line_number(){return bus_line_number_; }
    inline void set_bus_line_number(const QString input_bus_number){bus_line_number_=input_bus_number;}
    inline QString bus_information(){return bus_information_;}
    inline void set_bus_information(const QString input_bus_information){bus_information_=input_bus_information;}
    inline QString bus_diver(){return bus_diver_;}
    inline void set_bus_diver(const QString input_bus_diver){bus_diver_=input_bus_diver;}
    inline QDeclarativeGeoMapQuickItem * bus_quick_item(){ return  this->bus_quick_item_;}
    inline void set_bus_quick_item(QDeclarativeGeoMapQuickItem *quick_item){this->bus_quick_item_=quick_item;}
    inline bool is_stop(){return is_stop_;}
    inline bool is_cricle(){return is_cricle_;}
    inline void set_is_cricle(const bool isCricle){is_cricle_=isCricle;}
    /*基本信息存取 end*/

    /*重要信息存取 start*/
    inline QList<QGeoCoordinate> bus_path_coordinates(){return bus_path_coordinates_;}
    inline void set_bus_path_coordinates(QList<QGeoCoordinate> new_path){bus_path_coordinates_=new_path;}
    inline QQuickImage *bus_iocn(){return bus_iocn_;}
    inline void set_bus_iocn(QQuickImage *iocn_image){bus_iocn_=iocn_image;}
    void set_bus_iocn(const QUrl iocn_source_url);
    void SetBusIocnScale(double Scale);//更改icon缩放
    void SetMap(QDeclarativeGeoMap *qMap);    //更改Bus的所属map
    /*重要信息存取 end*/
    /* 更新函数 start */
    void Init();//变量初始化
    void Updata();//更新数据
    void UpdataPosition();//动画更新车辆位置
    /* 更新函数 end */
    /*路书相关函数  start */
    double GetPixelDistance(const QGeoCoordinate coordinate1,
                            const QGeoCoordinate coordinate2);//获取像素点上两点距离
    void MoveNextIndex(const int index);//移动到下一个关键点
    double LinearInterpolation(const double init_pos, //起始点
                               const double target_pos,//终结点
                               const int current_count,//当前帧数
                               const int count);//总帧数
    //设置车辆的偏转
    void SetRotation(const QGeoCoordinate coordinate1,
                     const QGeoCoordinate coordinate2);
    void ChangePath();//转置路径坐标
    // ------ 路书常用控制函数 ------
    void LuShu();                       //路书开始函数
    void LuShuStart();                  //开始LuShu
    void LuShuPause();                  //暂停LuShu
    void LuShuStop();                   //停止路书
    void InitSocket();                  //初始化socket通信
    /* 路书相关函数 end  */

    //----- 位置存储到数据库关键代码 start------
    inline bool is_save_gps(){return is_save_gps_;}
    inline void set_is_save_gps(bool is_save){is_save_gps_=is_save;}
    inline int record_id(){return record_id_;}
    inline void set_record_id(int new_record_id){record_id_=new_record_id;}
    void SaveCoordinateToSql(const QGeoCoordinate coordinate,int record_id);//将新的位置坐标存储到数据库中
    //----- 位置存储到数据库关键代码  end ------

    //设置ip地址
    inline void set_ip_address(QString address){ip_address_=address;}
    inline QString ip_address(){return ip_address_;}
    inline void set_port(unsigned int i){port_=i;}
    inline unsigned port(){return port_;}

    //相关槽函数
public slots:
    /*http 通信 start */
    void UpdataCoordinatesByNet();
    void GetReplyFinished(QNetworkReply *reply);
    /*http 通信 end */

    /*socket 通信 start*/
    void UpdateCoordinatesBySocket();//根据位置更新
    void SocketReadData();//读取数据
    void SocketDisconnected();//断开连接
    /*socket 通信 end*/

    /*LuShu槽函数 start*/
    void Move(const double dx,
              const double dy);
    void MoveNextPoint(const QGeoCoordinate coordinate1,
                       const QGeoCoordinate coordinate2);
    void SetCoordinate(const QGeoCoordinate new_coordinate);//更新位置信息，带偏转的
    void SetCoordinateFromWPS84(const QGeoCoordinate new_coordinate); //从标准坐标更新位置信息
    /*LuShu槽函数 end*/

    /*存储gps的槽函数 start*/
    void StartSaveGPS(int record_id);
    void StopSaveGPS();
    /*存储gps的槽函数 end*/

private:
    /*基本信息 start*/
    QString bus_id_;
    QString bus_name_;
    QString bus_line_number_;
    QString bus_information_;
    QString bus_diver_;
    Tool tool;
    /*基本信息 end*/

    /*重要信息 start*/
    QList<QGeoCoordinate> bus_path_coordinates_;//线路关键点列表
    QQuickImage *bus_iocn_=nullptr;//公交车图标iocn指针
    QDeclarativeGeoMapQuickItem *bus_quick_item_=nullptr;
    /*重要信息 end*/
    /*位置更新信息 start*/
    QTimeLine *bus_time_line_=nullptr;
    QTimer *bus_timer_=nullptr;
    /*位置更新信息 end*/
    /*路书动画 start*/
    QList<QTimeLine *> bus_time_line_list_;
    int line_index_=0;//当前点索引初始化为0
    double bus_speed_=5;//公交车速度(km/s)
    bool is_cricle_=true;//是否循环
    bool is_pause = false;//是否
    bool is_stop_ = false;//不停止;是否停止，当为true时，车辆已经停止
    bool is_return=false;//是否在返程
    /*路书动画 end*/
    //socket通信成员
    QTcpSocket *socket_=nullptr;//socket通信成员变量
    QString ip_address_="112.74.188.50";//设置ip地址，默认IP地址 "112.74.188.50"
    unsigned int port_=20721;           //设置端口号，默认端口号 为 20721
    //存储坐标相关信息
    bool is_save_gps_=false;
    int record_id_=NULL;//存储时的记忆编号
};

#endif // BUS_H
