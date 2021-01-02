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
static MapEngine *kMapEngine = nullptr; //声明全局的Map引擎
MapEngine *
getMapEngine()
{
    if (!kMapEngine)
        kMapEngine = new MapEngine();
    return kMapEngine;
}

//-----------------------------------------------------------------------------
void destroyMapEngine()
{
    if (kMapEngine)
    {
        delete kMapEngine;
        kMapEngine = nullptr;
    }
}

//-----------------------------------------------------------------------------
//MapEngine 构造函数的注册类
MapEngine::MapEngine()
    : _urlFactory(new UrlFactory())
{
    qRegisterMetaType<MapTask::TaskType>(); //将类型注册到QML
}

//-----------------------------------------------------------------------------
MapEngine::~MapEngine()
{
    _worker.quit(); //开始结束瓦片请求进程
    _worker.wait();
    if (_urlFactory)
    {
        delete _urlFactory;
        _urlFactory = nullptr;
    }
}

//-----------------------------------------------------------------------------
//向缓冲任务队列添加任务
void MapEngine::addTask(MapTask *task)
{
    _worker.enqueueTask(task);
}

//-----------------------------------------------------------------------------
//获取瓦片Has值，这里主要是为了和qml的hash值相对应

QString
MapEngine::getTileHash(UrlFactory::MapType type, int x, int y, int z)
{
    return QString().sprintf("%04d%08d%08d%03d", (int)type, x, y, z);
}

//-----------------------------------------------------------------------------
//从Hash值获取瓦片的类型

UrlFactory::MapType
MapEngine::hashToType(const QString &hash)
{
    QString type = hash.mid(0, 4);
    return (UrlFactory::MapType)type.toInt();
}

//-----------------------------------------------------------------------------
//根据x,y,z创建相关资料
FetchTileTask *
MapEngine::createFetchTileTask(UrlFactory::MapType type, int x, int y, int z)
{
    QString hash = getTileHash(type, x, y, z);
    FetchTileTask *task = new FetchTileTask(hash);
    return task;
}

//-----------------------------------------------------------------------------
//转换位置
int MapEngine::long2tileX(double lon, int z)
{
    return (int)(floor((lon + 180.0) / 360.0 * pow(2.0, z)));
}
//转化位置
//-----------------------------------------------------------------------------
int MapEngine::lat2tileY(double lat, int z)
{
    return (int)(floor((1.0 - log(tan(lat * M_PI / 180.0) + 1.0 / cos(lat * M_PI / 180.0)) / M_PI) / 2.0 * pow(2.0, z)));
}
