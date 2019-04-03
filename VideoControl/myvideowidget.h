#ifndef MYVIDEOWIDGET_H
#define MYVIDEOWIDGET_H

/****************************************************************************
** @projectName   OfflineMapTest
** QT Version    5.11.3
** This file is part of the OfflineMapTest project.
** @file          myvideowidget.h
** @brief         MyVideoWidget类的头文件
** @details       将Qt播放列表重新封装一次，便于后期的使用和布局，将其封装为类似HTML video的易于使用的类
** @author        wangpengcheng
** @QQ            673018396
** @email         wangpengcheng2018@gmail.com
** @address       https://github.com/wangpengcheng/OfflineMapTest
** @date          2019-04-03 周三  19:09:57
** @example
**
**    QString video_path=QString("C:/Users/lin/Videos/Captures/minieyeone.mp4");
**    MyVideoWidget test(QUrl::fromLocalFile(video_path));
**    test.resize(400,300);
**    test.show();
**    test.VideoPlay();
**
*****************************************************************************/
#include <QVideoWidget>
#include <QtMultimediaWidgets>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QWidget>
#include <QVBoxLayout>
#include <QVideoEncoderSettingsControl>
class MyVideoWidget: public QVideoWidget
{
    Q_OBJECT
public:
    MyVideoWidget(QUrl video_file_path);
    ~MyVideoWidget();
    //基本存取函数
    inline QMediaPlayer* media_player(){return media_player_;}
    inline void set_media_player(QMediaPlayer* media_player){media_player_=media_player;}
    inline QVideoWidget* video_widget(){return video_widget_;}
    inline void set_video_widget(QVideoWidget* video_widget){ video_widget_=video_widget;}
    inline QMediaPlaylist* play_list(){return play_list_;}
    inline void set_play_list(QMediaPlaylist* play_list){play_list_=play_list;}
    void VideoPlay();//播放函数
    void VideoPause();//暂停
    void VideoStop();//播放停止
private:
    QMediaPlayer* media_player_=nullptr;
    QVideoWidget* video_widget_=nullptr;
    QMediaPlaylist* play_list_=nullptr;
    QVBoxLayout* video_layout_ = nullptr;

};

#endif // MYVIDEOWIDGET_H
