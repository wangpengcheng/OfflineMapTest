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
*/
class Bus: public QDeclarativeGeoMapQuickItem
{
     Q_OBJECT
public:
    Bus();
    ~Bus();
    Bus(const QGeoCoordinate new_coordinate);
    Bus(const QGeoCoordinate new_coordinate,
        QList<QGeoCoordinate> new_path);
    Bus(const QGeoCoordinate new_coordinate,
        QList<QGeoCoordinate> new_path,
        const QUrl iocn_path);
     /*基本信息存取 start*/
    QString bus_id();
    void set_bus_id(const QString input_bus_id);
    QString bus_name();
    void set_bus_name(const QString input_name);
    QString bus_line_number();
    void set_bus_line_number(const QString input_bus_number);
    QString bus_information();
    void set_bus_information(const QString input_bus_information);
    QString bus_diver();
    void set_bus_diver(const QString input_bus_diver);
    /*基本信息存取 end*/
    /*重要信息存取 start*/
    QList<QGeoCoordinate> bus_path_coordinates();
    void set_bus_path_coordinates(QList<QGeoCoordinate> new_path);
    QQuickImage *bus_iocn();
    void set_bus_iocn(QQuickImage *iocn_image);
    void set_bus_iocn(const QUrl iocn_source_url);
    /*重要信息存取 end*/
    void Init();//变量初始化
    void Updata();//更新数据
    void UpdataPosition();//更新车辆位置
    /*其它函数*/
    double GetPixelDistance(const QGeoCoordinate coordinate1,
                            const QGeoCoordinate coordinate2);//获取像素点上两点距离
    void LuShu();
    void MoveNextIndex(const int index);//移动到下一个关键点
    double LinearInterpolation(const int init_pos, //起始点
                               const int target_pos,//终结点
                               const int current_count,//当前帧数
                               const int count);//总帧数
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
    QQuickImage *bus_iocn_;//公交车图标iocn指针
    /*重要信息 end*/
    /*位置更新信息 start*/
    QTimeLine *bus_time_line_;
    QTimer *bus_timer_;
    /*位置更新信息 end*/
    /*路书动画 start*/
    QList<QTimeLine *> bus_time_line_list_;
    /*路书动画 end*/
    int line_index_=0;//当前点索引初始化为0
    double bus_speed_=0;//公交车速度
    //相关槽函数
public slots:
    void UpdataCoordinatesByNet();
    void GetReplyFinished(QNetworkReply *reply);
    void Move(const double dx,
              const double dy);
    void MoveNextPoint(const QGeoCoordinate coordinate1,
                       const QGeoCoordinate coordinate2);
};

#endif // BUS_H
