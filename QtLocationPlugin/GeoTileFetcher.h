/**
 * @file GeoTileFetcher.h
 * @brief GeoTileFetcher 定义头文件
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2020-12-30 16:33:51
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
 *    <td> 2020-12-30 16:33:51 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 添加文档信息 </td>
 * </tr>
 * </table>
 */
#ifndef GEOTILEFETCHER_H
#define GEOTILEFETCHER_H

#include <QtLocation/private/qgeotilefetcher_p.h>
#include "MapUrlEngine.h"

class QGeoTiledMappingManagerEngine;
class QNetworkAccessManager;
/**
 * @brief Geo瓦片类，主要是为了适配QtLocation
 */
class GeoTileFetcher : public QGeoTileFetcher
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Geo Tile Fetcher object
     * @param  parent         父指针
     */
    explicit GeoTileFetcher(QGeoTiledMappingManagerEngine *parent = 0);
    ~GeoTileFetcher();

private:
    /**
     * @brief Get the Tile Image object
     * @param  spec             QGeo瓦片
     * @return QGeoTiledMapReply* 瓦片请求网络响应
     */
    QGeoTiledMapReply *getTileImage(const QGeoTileSpec &spec);

private:
    QNetworkAccessManager *_networkManager; ///< 瓦片请求网络响应指针
};

#endif
