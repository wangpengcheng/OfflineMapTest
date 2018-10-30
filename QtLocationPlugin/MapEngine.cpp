#include <math.h>
#include <QSettings>
#include <QStandardPaths>
#include <QDir>
#include <stdio.h>

#include "MapEngine.h"

#include <QDebug>

Q_DECLARE_METATYPE(MapTask::TaskType)

//-----------------------------------------------------------------------------
// Singleton
static MapEngine* kMapEngine = NULL;
MapEngine*
getMapEngine()
{
    if(!kMapEngine)
        kMapEngine = new MapEngine();
    return kMapEngine;
}

//-----------------------------------------------------------------------------
void
destroyMapEngine()
{
    if(kMapEngine) {
        delete kMapEngine;
        kMapEngine = NULL;
    }
}

//-----------------------------------------------------------------------------
MapEngine::MapEngine()
    : _urlFactory(new UrlFactory())
{
    qRegisterMetaType<MapTask::TaskType>();
}

//-----------------------------------------------------------------------------
MapEngine::~MapEngine()
{
    _worker.quit();
    _worker.wait();
    if(_urlFactory)
        delete _urlFactory;
}


//-----------------------------------------------------------------------------
void
MapEngine::addTask(MapTask* task)
{
    _worker.enqueueTask(task);
}



//-----------------------------------------------------------------------------
QString
MapEngine::getTileHash(UrlFactory::MapType type, int x, int y, int z)
{
    return QString().sprintf("%04d%08d%08d%03d", (int)type, x, y, z);
}

//-----------------------------------------------------------------------------
UrlFactory::MapType
MapEngine::hashToType(const QString& hash)
{
    QString type = hash.mid(0,4);
    return (UrlFactory::MapType)type.toInt();
}

//-----------------------------------------------------------------------------
FetchTileTask*
MapEngine::createFetchTileTask(UrlFactory::MapType type, int x, int y, int z)
{
    QString hash = getTileHash(type, x, y, z);
    FetchTileTask* task = new FetchTileTask(hash);
    return task;
}


//-----------------------------------------------------------------------------
int
MapEngine::long2tileX(double lon, int z)
{
    return (int)(floor((lon + 180.0) / 360.0 * pow(2.0, z)));
}

//-----------------------------------------------------------------------------
int
MapEngine::lat2tileY(double lat, int z)
{
    return (int)(floor((1.0 - log( tan(lat * M_PI/180.0) + 1.0 / cos(lat * M_PI/180.0)) / M_PI) / 2.0 * pow(2.0, z)));
}


