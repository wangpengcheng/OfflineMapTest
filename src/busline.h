#ifndef BUSLINE_H
#define BUSLINE_H
/****************************************************************************
** @projectName   OfflineMapTest
** QT Version    5.11.1
** This file is part of the OfflineMapTest project.
** @file          busline.h
** @brief         BusLine class
** @details       Busline class to draw the busline in this map;inhert  QDeclarativeGeoMapItemGroup
** @author        wangpengcheng
** @QQ            673018396
** @email         wangpengcheng2018@gmail.com
** @address       https://github.com/wangpengcheng/OfflineMapTest
** @date          2018-12-04 周二  22:18:30
** @example
**
** 示例代码
**
*****************************************************************************/
#include <QtLocation/private/qdeclarativegeomapitemgroup_p.h>
#include <QtLocation/private/qdeclarativepolylinemapitem_p.h>
#include <QQuickItem>
#include <QGeoPath>
#include "src/tool.h"
class BusStation;
class BusLine : public QDeclarativeGeoMapItemGroup
{
    Q_OBJECT
public:
    BusLine();//空构造函数
    BusLine(QList<QGeoCoordinate> line_coordinates,
            QList<QGeoCoordinate> station_coordinates);//线路坐标和站点坐标构造函数
    ~BusLine();//析构函数
    inline QList<QGeoCoordinate> line_coordinate_list(){return line_coordinate_list_;}
   // QGeoPath bus_polyline_path();//获取线段关键路径
    inline void set_bus_polyline_path(QList<QGeoCoordinate> new_path){line_coordinate_list_.clear();line_coordinate_list_=new_path;}//更改路径坐标点
    inline QList<BusStation *> bus_station_list(){return bus_station_list_;}//获取站点队列
    void set_bus_stations_fromcoordinate(const QList<QGeoCoordinate> station_coordinates);//坐标列表更改站点
    void set_bus_station_list(QList<BusStation *> stations);//直接拷贝设置站点
    /*基本信息变量存取-start*/
    inline QString bus_line_id(){return bus_line_id_;}
    inline void set_bus_line_id(const QString line_id){bus_line_id_=line_id;}
    inline QString bus_line_name(){return bus_line_name_;}
    inline void set_bus_line_name(const QString line_name){bus_line_name_=line_name;}
    inline QString bus_line_information(){return bus_line_information_;}
    inline void set_bus_line_information(const QString line_information){ bus_line_information_=line_information;}
    QDeclarativePolylineMapItem *bus_poly_line(){return bus_poly_line_;}
     /*基本信息变量存取-end*/

    void Updata();              //更新数据
    void Init();                //初始化数据
private: //设置私有变量
     QList<QGeoCoordinate> line_coordinate_list_;//线路坐标列表
    // QGeoPath bus_polyline_path_;
     QDeclarativePolylineMapItem *bus_poly_line_=nullptr;//设置线段
     QList<BusStation *> bus_station_list_;//公交站点列表
     QString bus_line_id_;//线路编号
     QString bus_line_name_;//线路名称
     QString bus_line_information_;//线路详细信息
     Tool tool;


signals:

public slots:
};

#endif // BUSLINE_H
