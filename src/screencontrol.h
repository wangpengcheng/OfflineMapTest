#ifndef SCREENCONTROL_H
#define SCREENCONTROL_H

/****************************************************************************
** @projectName   OfflineMapTest
** QT Version     5.11.1
** This file is part of the OfflineMapTest project.
** @file          screencontrol.h
** @brief         ScreenControl class to control the big screen
** @details       主要功能包括；屏幕数量统计；分辨率统计；
**                屏幕合并和拆分；
**                屏幕复制、指定屏幕窗口等功能
** @author        wangpengcheng
** @QQ            673018396
** @email         wangpengcheng2018@gmail.com
** @address       https://github.com/wangpengcheng/OfflineMapTest
** @date          2018-11-09 周五  18:18:07
** @example
**
** 详见test/screencontroltest.h 中的ScreenControlTest 类
** ------2018-12-4 更新；完善测试类，添加自动分屏模块；根据屏幕大小和窗口排列自动排列计算窗口大小------
** 使用方法：
** ScreenControl screen_control;
** screen_control.SetScreenSize(1920,1080);
** screen_control.SetModel(3,4);//3 行4列
**
**
** QT Version    5.11.1
*****************************************************************************/
/*
 * 2018-11-24 添加新模块功能
 * 思路：设置模式列表，不同模式对应不同的分辨率坐标和窗口大小
 * 一： 3*4 3行4列，每个窗口分辨率为1920*1080（长*宽） 共计12个坐标点，每个窗口dx=1920;dy=1080 num=12
 * 二： 3*2 3行2列，每个窗口分辨率为（1920*2）*1080 共计6个坐标点，每个窗口dx=1920*2;dy=1080 num=6
 * 三： 3*1 3行1列，每个窗口分辨率为（1920*3）*1080 共计3个坐标点，每个窗口dx=1920*3;dy=1080 num=3
 * 四： 1*4 1行4列，每个窗口分辨率为1920*（1080*3） 共计4个坐标点，每个窗口dx=1920;dy=1080*3 num=4
 * 五： 1*2 1行2列，每个窗口分辨率为（1920*2）*（1080*3）共计2个坐标点，每个窗口dx=1920*2;dy=1080*3 num=2
 * 六： 1*1 1行1列，每个窗口分辨率为（1920*4）*（1080*3）共计1个坐标点，每个串口dx=1920*4;dy=1080*3
*/
#ifndef QLIST_H
#include <QList>
#endif
#ifndef QDESKTOPWIDGET_H
#include <QDesktopWidget>
#endif
#ifndef  QVIDEOWIDGET_H
#include <QVideoWidget>
#endif
#ifndef QMEDIAPLAYER_H
#include <QMediaPlayer>
#endif
#ifndef QMEDIAPLAYLIST_H
#include <QMediaPlaylist>
#endif
#include <QDebug>
class ScreenControl
{
public:
    ScreenControl();
    ScreenControl(QDesktopWidget *desktop);
  //  ~ScreenControl();
    QDesktopWidget* desktop();
    int screen_count();
    int virtual_screen_count();
    QList<QVideoWidget *> video_widget_list();
    QList<QMediaPlayer *> video_player_list();
    QList<QMediaPlaylist *> video_playlist_list();
    int screen_width();
    int screen_height();
    void SetScreenSize(const int width,
                       const int height);//设置屏幕宽高
    int widget_width();
    int widget_height();
    void SetWindowScreen(QWidget * widget,
                         const int screen_number);//设置窗口所在屏幕
    QDesktopWidget* m_desktop;//desktop硬件
    QList<QMediaPlayer *> video_player_list_;//视屏播放器列表
    QList<QVideoWidget *> video_widget_list_;//视频窗口队列
    QList<QMediaPlaylist *> video_playlist_list_;//视频播放队列列表
    void VideoPlay();//视频播放函数
    void VideoPause();//视频暂停
    void SetModel(const int x,const int y);//设置屏幕模式
    void Init();//初始化函数
    void Update();//数据更新函数
private:
    int m_screen_count=0;//屏幕总数
    int virtual_screen_count_=12;//虚拟屏幕数
    int screen_width_=1920;//每块屏幕宽度
    int screen_height_=1080;//屏幕高度
    int widget_width_=0;//窗口宽度
    int widget_height_=0;//窗口宽度
    int show_widget_count_=0;

};

#endif // SCREENCONTROL_H
