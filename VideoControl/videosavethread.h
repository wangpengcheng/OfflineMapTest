#ifndef VIDEOSAVETHREAD_H
#define VIDEOSAVETHREAD_H
/****************************************************************************
** @projectName   OfflineMapTest
** QT Version    5.11.1-5.12.3
** This file is part of the OfflineMapTest project.
** @file          videosavethread.h
** @brief         视频存储线程
** @details       通过集成ffmpeg实现对于流的存储为h264编码和MP4格式,主要实现媒体流的存储
** @author        wangpengcheng
** @QQ            673018396
** @email         wangpengcheng2018@gmail.com
** @address       https://github.com/wangpengcheng/OfflineMapTest
** @date          2019-07-02 周二  15:33:06
** @example
**
** 示例代码
**
*****************************************************************************/

/*ToDo: 实现存储
 * input: 网络流地址,保存文件地址
 * out：保存文件名称和路径
 * function ：开始解码，停止解码
 *           开始线程，暂停线程，销毁线程
*/
#include <QObject>
#include <QThread>

class VideoSaveThread : public QThread
{
    Q_OBJECT
public:
    explicit VideoSaveThread(QObject *parent = nullptr);

protected:
    void run();                                             //重写QThread；run函数
signals:

public slots:

private:
};

#endif // VIDEOSAVETHREAD_H
