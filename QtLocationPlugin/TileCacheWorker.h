#ifndef TILE_CACHE_WORKER_H
#define TILE_CACHE_WORKER_H

#include <QString>
#include <QThread>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <QMutexLocker>

class MapTask;
//主要是开启线程加载瓦片
class CacheWorker : public QThread
{
    Q_OBJECT
public:
    CacheWorker  ();
    ~CacheWorker ();

    void    quit            ();                         //关闭线程
    bool    enqueueTask     (MapTask* task);            //是否队列正在等待中

protected:
    void    run             ();


private:
    QQueue<MapTask*>     _taskQueue;                    //任务队列
    QMutex                  _mutex;                     //线程互斥信号量
    QMutex                  _waitmutex;                 //等待信号量
    QWaitCondition          _waitc;                     //等待条件


};

#endif
