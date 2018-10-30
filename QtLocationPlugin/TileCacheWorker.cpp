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
void
CacheWorker::quit()
{
    _mutex.lock();
    while(_taskQueue.count()) {
        MapTask* task = _taskQueue.dequeue();
        delete task;
    }
    _mutex.unlock();
    if(this->isRunning()) {
        _waitc.wakeAll();
    }
}

//-----------------------------------------------------------------------------
bool
CacheWorker::enqueueTask(MapTask* task)
{
    //-- If not initialized, the only allowed task is Init
    if( task->type() != MapTask::taskInit) {
        task->setError("Database Not Initialized");
        task->deleteLater();
        return false;
    }
    if(!_taskQueue.contains(task))
    {
        _mutex.lock();
        _taskQueue.enqueue(task);
        _mutex.unlock();
        if(this->isRunning()) {
            _waitc.wakeAll();
        } else {
            this->start(QThread::NormalPriority);
        }
        return true;
    }
    //-- Should never happen
    return false;
}

//-----------------------------------------------------------------------------
void
CacheWorker::run()
{
    return;
}
