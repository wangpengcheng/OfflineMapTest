#ifndef MAP_ENGINE_H
#define MAP_ENGINE_H

#include <QString>

#include "MapUrlEngine.h"
#include "MapEngineData.h"
#include "TileCacheWorker.h"

//-----------------------------------------------------------------------------
//基础瓦片设置类
class TileSet
{
public:
    TileSet()
    {
        clear();
    }
    //重构操作符
    TileSet& operator += (TileSet& other)
    {
        tileX0      += other.tileX0;
        tileX1      += other.tileX1;
        tileY0      += other.tileY0;
        tileY1      += other.tileY1;
        tileCount   += other.tileCount;
        tileSize    += other.tileSize;
        return *this;
    }
    void clear()
    {
        tileX0      = 0;
        tileX1      = 0;
        tileY0      = 0;
        tileY1      = 0;
        tileCount   = 0;
        tileSize    = 0;
    }

    int         tileX0;                 //
    int         tileX1;                 //
    int         tileY0;                 //
    int         tileY1;                 //
    quint64     tileCount;              //瓦片数量
    quint64     tileSize;               //瓦片大小
};

//-----------------------------------------------------------------------------
//地图引擎
class MapEngine : public QObject
{
    Q_OBJECT
public:
    MapEngine                ();
    ~MapEngine               ();

    void                        addTask             (MapTask *task);                                //添加任务队列
    FetchTileTask*           createFetchTileTask (UrlFactory::MapType type, int x, int y, int z);   //获取瓦片的Hash值
    UrlFactory::MapType         hashToType          (const QString& hash);                          //获取地图类型
    UrlFactory*                 urlFactory          () { return _urlFactory; }                      //获取地图url参数类

    //-- Tile Math
    static int                  long2tileX          (double lon, int z);                            //将经度转换到相对坐标
    static int                  lat2tileY           (double lat, int z);                            //将纬度转换到相对坐标
    static QString              getTileHash         (UrlFactory::MapType type, int x, int y, int z);//获取瓦片hash值


private:
    CacheWorker          _worker;                   //缓冲线程
    UrlFactory*             _urlFactory;            //Http请求Url类
};

extern MapEngine*    getMapEngine();                //声明全局函数，返回地图引擎的静态变量
extern void             destroyMapEngine();         //声明引擎销毁全局函数

#endif
