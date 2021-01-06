/**
 * @file busline.h
 * @brief Busline class to draw the busline in this map;inhert  QDeclarativeGeoMapItemGroup
 * @details 主要包含线路关键点和，线路上的站点关键点  \n
 * QT Version    5.12.2
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2018-12-04 22:18:30
 * @copyright Copyright (c) 2020  IRLSCU
 * 
 * @par 修改日志:
 * <table>
 * <tr>
 *    <th> Commit date</th>
 *    <th> Version </th> 
 *    <th> Author </th>  
 *    <th> Description </th>
 * <tr>
 *    <td> 2018-12-04 22:18:30 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 完成基本内容 </td>
 * </tr>
 * <tr>
 *    <td> 2020-12-28 23:15:42 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td>添加文档</td>
 * </tr>
 * </table>
 */
#ifndef BUSLINE_H
#define BUSLINE_H

#include <QtLocation/private/qdeclarativegeomapitemgroup_p.h>
#include <QtLocation/private/qdeclarativepolylinemapitem_p.h>
#include <QQuickItem>
#include <QGeoPath>
#include "MapItems/tool.h"
class BusStation;
/**
 * @brief 公交线路抽象类，主要包含线路关键点和站点关键点
 */
class BusLine : public QDeclarativeGeoMapItemGroup
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Bus Line object
     */
    explicit BusLine();
    /**
     * @brief Construct a new Bus Line object
     * @param  line_coordinates  线路坐标点列表，主要是各种转折关键单
     * @param  station_coordinatesMy 站点坐标点，各个停靠站点
     */
    explicit BusLine(QList<QGeoCoordinate> line_coordinates,
                     QList<QGeoCoordinate> station_coordinates);
    /**
     * @brief Destroy the Bus Line object
     */
    ~BusLine();
    /**
     * @brief 获取线路关键点列表
     * @return QList<QGeoCoordinate> 
     */
    inline QList<QGeoCoordinate> line_coordinate_list() { return line_coordinate_list_; }
    /**
     * @brief Set the bus polyline path object
     * @param  new_path         关键路径折线点
     */
    inline void set_bus_polyline_path(QList<QGeoCoordinate> new_path)
    {
        line_coordinate_list_.clear();
        line_coordinate_list_ = new_path;
    }
    /**
     * @brief  设置公交站点列表
     * @return QList<BusStation *> 
     */
    inline QList<BusStation *> bus_station_list() { return bus_station_list_; } //获取站点队列
    /**
     * @brief 通过一系列的公交站点坐标，提交公交站点类
     * @param  station_coordinates 站点经纬度坐标点
     */
    void set_bus_stations_fromcoordinate(const QList<QGeoCoordinate> station_coordinates); //坐标列表更改站点
    /**
     * @brief 直接拷贝设置站点
     * @param  stations         BusStation 站点坐标类
     */
    void set_bus_station_list(QList<BusStation *> stations);
    /* 基本信息变量存取-start */
    inline QString bus_line_id() { return bus_line_id_; }
    inline void set_bus_line_id(const QString line_id) { bus_line_id_ = line_id; }
    inline QString bus_line_name() { return bus_line_name_; }
    inline void set_bus_line_name(const QString line_name) { bus_line_name_ = line_name; }
    inline QString bus_line_information() { return bus_line_information_; }
    inline void set_bus_line_information(const QString line_information) { bus_line_information_ = line_information; }
    QDeclarativePolylineMapItem *bus_poly_line() { return bus_poly_line_; }
    /* 基本信息变量存取-end */
    /**
     * @brief 更新基本数据函数，主要用于，图像刷新
     */
    void Updata();
    /**
     * @brief  初始化数据函数
     */
    void Init();

private:                                                   ///< 设置私有变量
    QList<QGeoCoordinate> line_coordinate_list_;           ///< 线路坐标列表
    QDeclarativePolylineMapItem *bus_poly_line_ = nullptr; ///< 设置线段
    QList<BusStation *> bus_station_list_;                 ///< 公交站点列表
    QString bus_line_id_;                                  ///< 线路编号
    QString bus_line_name_;                                ///< 线路名称
    QString bus_line_information_;                         ///< 线路详细信息
};

#endif // BUSLINE_H
