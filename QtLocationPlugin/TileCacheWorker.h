#ifndef TILE_CACHE_WORKER_H
#define TILE_CACHE_WORKER_H

#include <QString>
#include <QThread>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <QMutexLocker>

class MapTask;

class CacheWorker : public QThread
{
    Q_OBJECT
public:
    CacheWorker  ();
    ~CacheWorker ();

    void    quit            ();
    bool    enqueueTask     (MapTask* task);

protected:
    void    run             ();


private:
    QQueue<MapTask*>     _taskQueue;
    QMutex                  _mutex;
    QMutex                  _waitmutex;
    QWaitCondition          _waitc;


};

#endif
