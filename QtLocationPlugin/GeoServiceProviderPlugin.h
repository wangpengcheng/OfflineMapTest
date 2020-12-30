/**
 * @file GeoServiceProviderPlugin.h
 * @brief 地体瓦片服务类工厂类 定义头文件
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2020-12-30 16:44:13
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
 *    <td> 2020-12-30 16:44:13 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 添加文档注释 </td>
 * </tr>
 * </table>
 */
#ifndef GEOSERVICEPROVIDER_H
#define GEOSERVICEPROVIDER_H

#include <QtCore/QObject>
#include <QtLocation/QGeoServiceProviderFactory>
#include <QtPlugin>
/**
 * @brief 地体瓦片服务类工厂类，为了兼容QtLocation插件而写，仅仅作为适配层，无太大意义
 */
class GeoServiceProviderFactory : public QObject, public QGeoServiceProviderFactory
{
    Q_OBJECT
    Q_INTERFACES(QGeoServiceProviderFactory)
    Q_PLUGIN_METADATA(IID "org.qt-project.qt.geoservice.serviceproviderfactory/5.0" FILE "maps_plugin.json")

public:
     /**
     * @brief Create a new Geo Tiled Mapping Manager Engine object
     * @param  parameters       QML的启动参数
     * @param  error            错误
     * @param  errorString      错误信息
     * @return QGeoMappingManagerEngine*  地图引擎指针
     */
    QGeoMappingManagerEngine *createMappingManagerEngine(const QVariantMap &parameters, QGeoServiceProvider::Error *error, QString *errorString) const;
    /**
     * @brief Create a Routing Manager Engine object
     * @param  parameters       QML的启动参数
     * @param  error            错误
     * @param  errorString      错误信息
     * @return QGeoRoutingManagerEngine*  路径规划和导航引擎，此处没有作用
     */
    QGeoRoutingManagerEngine *createRoutingManagerEngine(const QVariantMap &parameters, QGeoServiceProvider::Error *error, QString *errorString) const;
    /**
     * @brief Create a Place Manager Engine object
     * @param  parameters       QML的启动参数
     * @param  error            错误
     * @param  errorString      错误信息
     * @return QPlaceManagerEngine* 障碍物管理引擎，此处没有作用
     */
    QPlaceManagerEngine *createPlaceManagerEngine(const QVariantMap &parameters, QGeoServiceProvider::Error *error, QString *errorString) const;
};

#endif
