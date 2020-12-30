#include "MapEngine.h"

#include <QVariant>
#include <QDebug>
#include <QFile>

#include "time.h"

//-----------------------------------------------------------------------------
CacheWorker::CacheWorker()
{
}

//-----------------------------------------------------------------------------
CacheWorker::~CacheWorker()
{
}

//-----------------------------------------------------------------------------
void CacheWorker::quit()
{
    //线程加锁
    _mutex.lock();
    //清空任务队列
    while (_taskQueue.count())
    {
        MapTask *task = _taskQueue.dequeue();
        delete task;
    }
    //解锁
    _mutex.unlock();
    //如果线程正在运行，则将其唤醒
    if (this->isRunning())
    {
        _waitc.wakeAll();
    }
}

//-----------------------------------------------------------------------------
//检查任务是否在队列中，不在则加入

bool CacheWorker::enqueueTask(MapTask *task)
{
    //-- If not initialized, the only allowed task is Init
    if (task->type() != MapTask::taskInit)
    {
        task->setError("Database Not Initialized"); //发射错误信息
        task->deleteLater();
        return false;
    }
    if (!_taskQueue.contains(task))
    {
        _mutex.lock();
        _taskQueue.enqueue(task);
        _mutex.unlock();
        if (this->isRunning())
        {
            _waitc.wakeAll();
        }
        else
        {
            this->start(QThread::NormalPriority);
        }
        return true;
    }
    //-- Should never happen
    return false;
}

//-----------------------------------------------------------------------------
void CacheWorker::run()
{
    return;
}
