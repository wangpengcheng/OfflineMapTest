#ifndef MAP_ENGINE_DATA_H
#define MAP_ENGINE_DATA_H

#include <QObject>
#include <QString>
#include <QHash>
#include <QDateTime>

#include "MapUrlEngine.h"

#ifndef UINT64_MAX
#define  UINT64_MAX 18446744073709551615
#endif

#ifndef M_PI
#define	M_PI		3.14159265358979323846	/* pi */
#endif

//-----------------------------------------------------------------------------
//任务相关接口
class MapTask : public QObject
{
    Q_OBJECT
public:

    enum TaskType {
        taskInit,//初始化
        taskFetchTile,//适配瓦片
    };

    MapTask(TaskType type)
        : _type(type)
    {}
    virtual ~MapTask()
    {}

    virtual TaskType    type            () { return _type; }
    //发生错误时，抛出错误信号
    void setError(QString errorString)
    {
        emit error(_type, errorString);
    }

signals:
    void error          (MapTask::TaskType type, QString errorString);//错误信号

private:
    TaskType    _type;
};

//-----------------------------------------------------------------------------
//瓦片匹配接口类
class FetchTileTask : public MapTask
{
    Q_OBJECT
public:
    FetchTileTask(const QString hash)
        : MapTask(MapTask::taskFetchTile)
        , _hash(hash)
    {}

    ~FetchTileTask()
    {
    }

    QString         hash() { return _hash; }


private:
    QString         _hash;
};


#endif
