/**
 * @file videosavethread.h
 * @brief 视频存储线程
 * @details 通过集成ffmpeg实现对于流的存储为h264编码和MP4格式,主要实现媒体流的存储
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2019-07-02 15:33:06
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
 *    <td> 2019-07-02 15:33:06 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 创建对应类 </td>
 * </tr>
 * <tr>
 *    <td> 2020-12-29 21:46:36 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 添加基本文档 </td>
 * </tr>
 * </table>
 */
#ifndef VIDEOSAVETHREAD_H
#define VIDEOSAVETHREAD_H


#include <QObject>
#include <QThread>

/**
 * @brief 视频存储线程
 * @details 通过集成ffmpeg实现对于流的存储为h264编码和MP4格式,主要实现媒体流的存储
 * @todo 讲存储的代码从VideoDecodeThread::run()中剥离出来 \n
 * - 主要实现接口：
 *  - 开始解码
 *  - 停止解码
 *  - 暂停解码
 *  - 设置存储路径
 *  - 支持本地存储和远端存储两种方式
 */
class VideoSaveThread : public QThread
{
    Q_OBJECT
public:
    explicit VideoSaveThread(QObject *parent = nullptr);

protected:
    /**
     * @brief 重写QThread；run函数
     * @todo 重写QThread；run函数
     */
    void run();
signals:

public slots:

private:
};

#endif // VIDEOSAVETHREAD_H
