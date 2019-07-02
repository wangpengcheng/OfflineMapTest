#ifndef QTAVVIDEOWIDGET_H
#define QTAVVIDEOWIDGET_H

#include <QSharedDataPointer>
#include <QSharedPointer>
#include <QWidget>
#include <QHBoxLayout>
#include <QtAV/QtAV.h>
#include "QtAVWidgets/QtAVWidgets.h"
/****************************************************************************
** @projectName   OfflineMapTest
** QT Version    5.11.1-5.12.3
** This file is part of the OfflineMapTest project.
** @file          qtavvideowidget.h
** @brief         qtavvideowidget 类的头文件
** @details       主要实现播放类的封装成widget
** @author        wangpengcheng
** @QQ            673018396
** @email         wangpengcheng2018@gmail.com
** @address       https://github.com/wangpengcheng/OfflineMapTest
** @date          2019-06-27 周四  10:50:46
** @example
**
** 示例代码
**
*****************************************************************************/
class QtAVVideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QtAVVideoWidget(QWidget *parent = nullptr);
    QtAVVideoWidget(QSharedPointer<QtAV::AVPlayer> new_player,QString new_vid="gl");
    QtAVVideoWidget(const QtAVVideoWidget &);
    //基本的存取函数
    inline QSharedPointer<QtAV::AVPlayer> av_player(){return av_player_;}
    //inline void set_av_player(QSharedPointer<QtAV::AVPlayer*> new_player){av_player_=new_player;}
    inline QtAV::VideoRenderer* video_render(){return video_render_;}
    //inline void set_video_render(QtAV::VideoRenderer* new_render){video_render_=new_render;}
    inline bool is_play(){return is_play_;}
    void ChangeVideoRender(QtAV::VideoRenderer* new_render);        //更改渲染器函数
    void ChangeAVPlayer(QSharedPointer<QtAV::AVPlayer> new_player); //更改播放器函数

    ~QtAVVideoWidget();
    void Init();                                                    //初始化函数
    void VideoPlay();                                               //播放视频
    void VideoPause();                                              //暂停视频
signals:

public slots:

private:
    QSharedPointer<QtAV::AVPlayer> av_player_;              //指向播放器的指针
    QtAV::VideoRenderer* video_render_=nullptr;             //渲染器
    QHBoxLayout* video_layer_out_=nullptr;                  //视频显示布局
    QString vid="wg";                                       //显示的渲染方式,默认使用wg渲染；注意如果要与OpenGL或者QML一起使用，必须选择wg模式。
    bool is_play_=false;                                    //记录是否正在播放状态
};

#endif // QTAVVIDEOWIDGET_H
