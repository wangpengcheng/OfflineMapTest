#ifndef MAP_ENGINE_H
#define MAP_ENGINE_H

#include <QString>

#include "MapUrlEngine.h"
#include "MapEngineData.h"
#include "TileCacheWorker.h"

//-----------------------------------------------------------------------------
class TileSet
{
public:
    TileSet()
    {
        clear();
    }
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

    int         tileX0;
    int         tileX1;
    int         tileY0;
    int         tileY1;
    quint64     tileCount;
    quint64     tileSize;
};

//-----------------------------------------------------------------------------
class MapEngine : public QObject
{
    Q_OBJECT
public:
    MapEngine                ();
    ~MapEngine               ();

    void                        addTask             (MapTask *task);
    FetchTileTask*           createFetchTileTask (UrlFactory::MapType type, int x, int y, int z);
    UrlFactory::MapType         hashToType          (const QString& hash);
    UrlFactory*                 urlFactory          () { return _urlFactory; }

    //-- Tile Math
    static int                  long2tileX          (double lon, int z);
    static int                  lat2tileY           (double lat, int z);
    static QString              getTileHash         (UrlFactory::MapType type, int x, int y, int z);


private:
    CacheWorker          _worker;
    UrlFactory*             _urlFactory;
};

extern MapEngine*    getMapEngine();
extern void             destroyMapEngine();

#endif
