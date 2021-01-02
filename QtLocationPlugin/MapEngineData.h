/**
 * @file MapEngineData.h
 * @brief MapEngine类中需要使用的基础数据的定义头文件
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2020-12-30 16:12:41
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
 *    <td> 2020-12-30 16:12:41 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 添加文档注释 </td>
 * </tr>
 * </table>
 */
#ifndef MAP_ENGINE_DATA_H
#define MAP_ENGINE_DATA_H

#include <QObject>
#include <QString>
#include <QHash>
#include <QDateTime>

#include "MapUrlEngine.h"

#ifndef UINT64_MAX
#define UINT64_MAX 18446744073709551615
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846 /* pi */
#endif

//-----------------------------------------------------------------------------
/**
 * @brief Map任务接口类，主要用来，执行瓦片初始化操作
 */
class MapTask : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Map操作需要的任务类型
     */
    enum TaskType
    {
        taskInit,      ///< 初始化--将图片加载到内存
        taskFetchTile, ///< 适配瓦片--从已加载的瓦片中查找
    };
    /**
     * @brief 构造函数
     * @param  type   基本类型
     */
    MapTask(TaskType type)
        : _type(type)
    {
    }
    /**
     * @brief Destroy the Map Task object
     */
    virtual ~MapTask()
    {
    }
    /**
     * @brief  获取类型
     * @return TaskType 
     */
    virtual TaskType type() { return _type; }
    /**
     * @brief 发生错误时，抛出错误信号
     * @param  errorString      错误描述
     */
    void setError(QString errorString)
    {
        emit error(_type, errorString);
    }

signals:
    /**
     * @brief 错误信号 
     * @param  type             类型
     * @param  errorString      提示信息
     */
    void error(MapTask::TaskType type, QString errorString);

private:
    TaskType _type; ///< 任务类型
};

//-----------------------------------------------------------------------------
//
/**
 * @brief 瓦片匹配任务类，主要用来进行瓦片查找
 */
class FetchTileTask : public MapTask
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Fetch Tile Task object
     * @param  hash             My Param doc
     */
    FetchTileTask(const QString hash)
        : MapTask(MapTask::taskFetchTile), _hash(hash)
    {
    }
    /**
     * @brief Destroy the Fetch Tile Task object
     */
    ~FetchTileTask()
    {
    }
    /**
     * @brief  瓦片hash值
     * @return QString 对应的索引字符串
     */
    QString hash() { return _hash; }

private:
    QString _hash; ///< 唯一的hash字符串
};

#endif
