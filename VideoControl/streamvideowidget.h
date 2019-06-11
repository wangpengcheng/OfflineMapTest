#ifndef STREAMVIDEOWIDGET_H
#define STREAMVIDEOWIDGET_H
/****************************************************************************
** @projectName   OfflineMapTest
** QT Version    5.11.3
** This file is part of the OfflineMapTest project.
** @file          streamvideowidget.h
** @brief         StreamVideoWidget类头文件；主要是接收网络流
** @details       接收Videodecodethrea的Image信号槽函数
** @author        wangpengcheng
** @QQ            673018396
** @email         wangpengcheng2018@gmail.com
** @address       https://github.com/wangpengcheng/OfflineMapTest
** @date          2019-04-22 周一  15:58:52
** @example
**
** 示例代码
**
*****************************************************************************/
#include <QWidget>
#include <QMainWindow>
#include <QImage>
#include <QPaintEvent>
#include <QWidget>
#include <QtDebug>
#include <QtConcurrent/qtconcurrentrun.h>
#include <QSharedPointer>
#include <QPaintEvent>
#include <QPainter>
#include "videodecodethread.h"

class StreamVideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StreamVideoWidget(QWidget *parent=nullptr);
    StreamVideoWidget(QSharedPointer<VideoDecodeThread> new_decode);//直接用解码线程初始化
    void set_decode_thread(QSharedPointer<VideoDecodeThread> new_decode);
    inline  QSharedPointer<VideoDecodeThread> decode_thread(){return decode_thread_;}
    inline bool is_play(){return is_play_;}
    //~StreamVideoWidget();
    void Init();//初始化函数
    void VideoPlay();//播放视频
    void VideoPause();//暂停视频
protected:
    void paintEvent(QPaintEvent *event);
    QImage display_image;//记录当前显示的图像
private slots:
    void slot_get_frame(QImage show_img);
private :
    QSharedPointer<VideoDecodeThread> decode_thread_=nullptr;
    bool is_play_=false;//记录状态是否有画面播放
};

#endif // STREAMVIDEOWIDGET_H
