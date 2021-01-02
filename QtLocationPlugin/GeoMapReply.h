/**
 * @file GeoMapReply.h
 * @brief GeoTiledMapReply类定义头文件
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2020-12-30 16:45:01
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
 *    <td> 2020-12-30 16:45:01 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 添加文档注释 </td>
 * </tr>
 * </table>
 */
#ifndef GEOMAPREPLY_H
#define GEOMAPREPLY_H

#include <QtNetwork/QNetworkReply>
#include <QtLocation/private/qgeotiledmapreply_p.h>

#include "MapEngineData.h"
/**
 * @brief 地图瓦片响应类
 */
class GeoTiledMapReply : public QGeoTiledMapReply
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Geo Tiled Map Reply object
     * @param  networkManager   网络请求管理
     * @param  request          请求管理
     * @param  spec             瓦片数据引用
     * @param  parent           parent
     */
    GeoTiledMapReply(QNetworkAccessManager *networkManager, const QNetworkRequest &request, const QGeoTileSpec &spec, QObject *parent = 0);
    /**
     * @brief Destroy the Geo Tiled Map Reply object
     */
    ~GeoTiledMapReply();
    /**
     * @brief 异常中断函数
     */
    void abort();

private slots:
    /**
     * @brief 回应销毁
     */
    void replyDestroyed();
    /**
     * @brief 网络请求完成响应
     */
    void networkReplyFinished();
    /**
     * @brief 网络请求错误响应
     * @param  error            错误信息
     */
    void networkReplyError(QNetworkReply::NetworkError error);
    /**
     * @brief 缓冲任务错误显示
     * @param  type             任务类型
     * @param  errorString      错误信息
     */
    void cacheError(MapTask::TaskType type, QString errorString);

private:
    QNetworkReply *_reply;                  ///< 请求返回函数
    QNetworkRequest _request;               ///< 请求函数
    QNetworkAccessManager *_networkManager; ///< 网络请求管理
    QByteArray _badMapBox;                  ///< 坏Map管理
    QByteArray _badTile;                    ///< 坏瓦片
};

#endif
