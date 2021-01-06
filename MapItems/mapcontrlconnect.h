/**
 * @file mapcontrlconnect.h
 * @brief MapControlConnect 控制类头文件
 * @details  主要功能是连接和同步，两个地图之间的操作；主要运用是智能指针 \n
 * QT Version    5.12.2
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2019-03-31 22:12:19
 * @copyright Copyright (c) 2020  IRLSCU
 * 
 * @par 修改日志:
 * <table>
 * <tr>
 *    <th> Commit date</th>
 *    <th> Version </th> 
 *    <th> Author </th>  
 *    <th> Description </th>
 * </tr>
 * <tr>
 *    <td> 2019-03-31 22:12:19 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 完成类的基本功能 </td>
 * </tr>
 * <tr>
 *    <td> 2020-12-29 00:27:24 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 完善文档 </td>
 * </tr>
 * </table>
 * 
 * @example mapcontrlconnect.h 
 * 请到测试类中查看详细使用示例
 * @code{.cpp}
 * MapContrlConnect map_connect(qMap,control_map);
 * @endcode
 */
#ifndef MAPCONTRLCONNECT_H
#define MAPCONTRLCONNECT_H
#include <QObject>
#include <QtLocation/private/qdeclarativegeomap_p.h>
#include <iostream>
#include <memory>
/**
 * @brief 因为采用的双屏模式进行操作，大屏显示；小屏控制 \n
 * 此类用于连接类，讲两个QML Map的动作进行同步
 */
class MapContrlConnect : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Map Contrl Connect object
     */
    explicit MapContrlConnect();
    /**
     * @brief Construct a new Map Contrl Connect object
     * @param  show_map         My Param doc
     * @param  control_map      My Param doc
     */
    MapContrlConnect(std::shared_ptr<QDeclarativeGeoMap> show_map,
                     std::shared_ptr<QDeclarativeGeoMap> control_map);
    /**
     * @brief Destroy the Map Contrl Connect object
     */
    ~MapContrlConnect();
    /**
     * @brief  初始化函数；主要是连接信号和槽工具
     */
    void Init();
public slots:
    /**
     * @brief 槽函数--主要是同步缩放等级
     * @param  zoomLevel        指定的缩放等级
     */
    void change_show_zoom(qreal zoomLevel);
    /**
     * @brief  显示中心函数
     * @param  center           指定地图中心点坐标
     */
    void change_show_center(const QGeoCoordinate &center);

private:
    std::shared_ptr<QDeclarativeGeoMap> show_map_ptr_ = nullptr;    ///< 显示地图指针
    std::shared_ptr<QDeclarativeGeoMap> control_map_ptr_ = nullptr; ///< 控制地图指针
};

#endif // MAPCONTRLCONNECT_H
