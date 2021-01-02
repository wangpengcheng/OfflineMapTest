/**
 * @file MapEngine.h
 * @brief TileSet 定义头文件
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2020-12-30 16:05:24
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
 *    <td> 2020-12-30 16:05:24 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 添加文档注释 </td>
 * </tr>
 * </table>
 */
#ifndef MAP_ENGINE_H
#define MAP_ENGINE_H

#include <QString>

#include "MapUrlEngine.h"
#include "MapEngineData.h"
#include "TileCacheWorker.h"

//-----------------------------------------------------------------------------
/**
 * @brief 基础瓦片设置类,主要是重载地图瓦片的基础操作
 */
class TileSet
{
public:
    /**
     * @brief Construct a new Tile Set object
     */
    TileSet()
    {
        clear();
    }
    /**
     * @brief  重载+= 操作符号
     * @param  other           其它瓦片设置
     * @return TileSet&         当前瓦片
     */
    TileSet &operator+=(TileSet &other)
    {
        tileX0 += other.tileX0;
        tileX1 += other.tileX1;
        tileY0 += other.tileY0;
        tileY1 += other.tileY1;
        tileCount += other.tileCount;
        tileSize += other.tileSize;
        return *this;
    }
    /**
     * @brief 清除重置函数
     */
    void clear()
    {
        tileX0 = 0;
        tileX1 = 0;
        tileY0 = 0;
        tileY1 = 0;
        tileCount = 0;
        tileSize = 0;
    }

    int tileX0;        ///< x起点做标
    int tileX1;        ///< x终点坐标
    int tileY0;        ///< y起点坐标
    int tileY1;        ///< y终点坐标
    quint64 tileCount; ///< 瓦片数量
    quint64 tileSize;  ///< 瓦片大小
};

//-----------------------------------------------------------------------------
/**
 * @brief 地图引擎抽象类
 */
class MapEngine : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Map Engine object
     */
    MapEngine();
    /**
     * @brief Destroy the Map Engine object
     */
    ~MapEngine();
    /**
     * @brief 添加任务队列
     * @param  task            接收的任务
     */
    void addTask(MapTask *task);
    /**
     * @brief 获取瓦片的Hash值,方便记录和快速查找坐标对应的瓦片
     * @param  type             瓦片类型
     * @param  x                x坐标，一般为维度
     * @param  y                y坐标，一般为经度
     * @param  z                z坐标，一般为缩放层级
     * @return FetchTileTask*   加载的瓦片数据指针
     */
    FetchTileTask *createFetchTileTask(UrlFactory::MapType type, int x, int y, int z);
    /**
     * @brief 获取地图类型
     * @param  hash             瓦片对应Hash值
     * @return UrlFactory::MapType 地图类型
     */
    UrlFactory::MapType hashToType(const QString &hash);
    UrlFactory *urlFactory() { return _urlFactory; }                                   //获取地图url参数类

    //-- Tile Math
    static int long2tileX(double lon, int z);                                  //将经度转换到相对坐标
    static int lat2tileY(double lat, int z);                                   //将纬度转换到相对坐标
    static QString getTileHash(UrlFactory::MapType type, int x, int y, int z); //获取瓦片hash值

private:
    CacheWorker _worker;     ///< 缓冲线程
    UrlFactory *_urlFactory; ///< Http请求Url类
};
/**
 * @brief 声明全局函数，返回地图引擎的静态变量
 * @return MapEngine* 地图引擎的静态全局变量
 */
extern MapEngine *getMapEngine();
/**
 * @brief 声明引擎销毁全局函数
 */
extern void destroyMapEngine();

#endif
