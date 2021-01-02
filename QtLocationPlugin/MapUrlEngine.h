/**
 * @file MapUrlEngine.h
 * @brief UrlFactory 关键类头文件
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2020-12-30 16:26:20
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
 *    <td> 2020-12-30 16:26:20 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 添加文档注释 </td>
 * </tr>
 * </table>
 */
#ifndef MAP_URL_ENGINE_H
#define MAP_URL_ENGINE_H

#include <QString>
#include <QPoint>
#include <QByteArray>
#include <QNetworkProxy>
#include <QNetworkReply>
#include <QMutex>

#define MAX_MAP_ZOOM (20.0)
/**
 * @brief Url工厂类，使用工厂模式，根据地图类型；来进行图片操作
 */
class UrlFactory : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief 地图类型枚举，根据不同的地图，加载不同的瓦片数据
     */
    enum MapType
    {
        Invalid,        ///< 不存在
        GaodeStreet,    ///< 接景
        GaodeSatellite, ///< 街景瓦片
    };
    /**
     * @brief Construct a new Url Factory object
     */
    UrlFactory();
    /**
     * @brief Destroy the Url Factory object
     */
    ~UrlFactory();
    /**
     * @brief 获取瓦片对应的远程地址，根据类型、坐标和缩放等级查找对应瓦片的地址链接，生成HTTP请求头部
     * @param  type             地图类型
     * @param  x                x
     * @param  y                y
     * @param  zoom             缩放等级
     * @return QNetworkRequest  最终的头部请求
     */
    QNetworkRequest getTileURL(MapType type, int x, int y, int zoom);
    /**
     * @brief  查询图片格式
     * @param  type             地图格式
     * @param  image            图片引用
     * @return QString          图片格式
     */
    QString getImageFormat(MapType type, const QByteArray &image);

private slots:

private:
    /**
     * @brief  获取对应的远程地址，根据类型、坐标和缩放等级查找对应瓦片的地址链接
     * @param  type             地图类型
     * @param  x                x
     * @param  y                y
     * @param  zoom             缩放等级
     * @return QString          链接地址
     */
    QString _getURL(MapType type, int x, int y, int zoom);

private:
    int _timeout;          ///< 最长等待时间
    QByteArray _userAgent; ///< 请求用户信息，用于加载需要校验的数据
};

#endif
