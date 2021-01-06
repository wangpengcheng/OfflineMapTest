/**
 * @file GeoTiledMappingManagerEngine.h
 * @brief GeoTiledMappingManagerEngine 定义头部文件
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2020-12-30 16:37:26
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
 *    <td> 2020-12-30 16:37:26 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 添加文档内容 </td>
 * </tr>
 * </table>
 */
#ifndef GEOTILEDMAPPINGMANAGERENGINE_H
#define GEOTILEDMAPPINGMANAGERENGINE_H

#include <QtLocation/QGeoServiceProvider>
#if QT_VERSION >= 0x050500
#include <QtLocation/private/qgeotiledmap_p.h>
#endif
#include <QtLocation/private/qgeotiledmappingmanagerengine_p.h>

#if QT_VERSION >= 0x050500

class GeoTiledMap : public QGeoTiledMap
{
    Q_OBJECT
public:
    GeoTiledMap(QGeoTiledMappingManagerEngine *engine, QObject *parent = 0);
};
#endif

class GeoTileFetcher;
/**
 * @brief Qt 地图插件扩展类
 */
class GeoTiledMappingManagerEngine : public QGeoTiledMappingManagerEngine
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Geo Tiled Mapping Manager Engine object
     * @param  parameters       QML的启动参数
     * @param  error            错误
     * @param  errorString      错误信息
     */
    GeoTiledMappingManagerEngine(const QVariantMap &parameters, QGeoServiceProvider::Error *error, QString *errorString);
    /**
     * @brief Destroy the Geo Tiled Mapping Manager Engine object
     */
    ~GeoTiledMappingManagerEngine();
#if QT_VERSION < 0x050500
    /**
     * @brief 创建QGeoMapData函数，用来创建自定义地图
     * @return QGeoMapData* 
     */
    QGeoMapData *createMapData();
#else
    QGeoMap *createMap();
#endif
};

#endif
