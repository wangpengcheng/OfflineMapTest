/**
 * @file TileCacheWorker.h
 * @brief CacheWorker 定义头文件
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2020-12-30 16:32:06
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
 *    <td> 2020-12-30 16:32:06 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 添加文档注释 </td>
 * </tr>
 * </table>
 */
#ifndef TILE_CACHE_WORKER_H
#define TILE_CACHE_WORKER_H

#include <QString>
#include <QThread>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <QMutexLocker>

class MapTask;
/**
 * @brief 主要是开启线程加载瓦片
 */
class CacheWorker : public QThread
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Cache Worker object
     */
    CacheWorker();
    /**
     * @brief Destroy the Cache Worker object
     */
    ~CacheWorker();
    /**
     * @brief 关闭线程
     */
    void quit();
    /**
     * @brief 将任务添加到等待队列中
     * @param  task             map任务
     * @return true             将任务添加到了任务队列中
     * @return false            添加任务队列失败
     */
    bool enqueueTask(MapTask *task);

protected:
    /**
     * @brief 重载的run函数，执行相关方法
     */
    void run();

private:
    QQueue<MapTask *> _taskQueue; ///< 任务队列
    QMutex _mutex;                ///< 线程互斥信号量
    QMutex _waitmutex;            ///< 等待信号量
    QWaitCondition _waitc;        ///< 等待条件
};

#endif
