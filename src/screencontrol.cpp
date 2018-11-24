#include "screencontrol.h"



ScreenControl::ScreenControl()
{

}
ScreenControl::ScreenControl(QDesktopWidget *desktop)
{
    m_desktop=desktop;
    m_screen_count=desktop->screenCount();
}

int ScreenControl::screen_count()
{
    return this->m_screen_count;
}

QDesktopWidget* ScreenControl::desktop()
{
    return this->m_desktop;
}
int ScreenControl::virtual_screen_count()
{
    return virtual_screen_count_;
}
QList<QVideoWidget *> ScreenControl::video_widget_list()
{
    return video_widget_list_;
}
QList<QMediaPlayer *> ScreenControl::video_player_list()
{
    return video_player_list_;
}
QList<QMediaPlaylist *> ScreenControl::video_playlist_list()
{
   return  video_playlist_list_;
}
int ScreenControl::screen_height()
{
    return screen_height_;
}
int ScreenControl::screen_width()
{
    return screen_width_;
}
void ScreenControl::SetWindowScreen(QWidget *widget,const int screen_number)
{
   // QRect temp=m_desktop->screenGeometry(screen_number);
    widget->setGeometry(this->desktop()->screenGeometry(screen_number));
}
void ScreenControl::Update()
{
    //ToDo
    /*
     * 更新窗口和视频在内的所有信息
    */

}
void ScreenControl::init()
{
    //初始化内存分配
    for(int i=0;i<virtual_screen_count_;i++)
    {
        QVideoWidget *temp_video_widget = new QVideoWidget();
        QMediaPlayer *temp_player=new QMediaPlayer();
        QMediaPlaylist *temp_playlist=new QMediaPlaylist();

            QString video_path=QString("C:/Users/lin/Videos/Captures/1.mp4");
           // temp_playlist->addMedia(QUrl("file:///C:/Users/lin/Videos/Captures/2.mp4"));
            temp_playlist->addMedia(QUrl::fromLocalFile(video_path));
           // playlist->addMedia(QUrl::fromLocalFile(video_path));
            temp_playlist->setCurrentIndex(1);//设置播放间隔
            temp_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
            temp_player->setPlaylist(temp_playlist);
            temp_player->setVideoOutput(temp_video_widget);
            temp_video_widget->resize(screen_width_,screen_height_);
            temp_video_widget->setGeometry(QRect(screen_width_*(i%4),20+screen_width_*(i/4),screen_width_,screen_width_));
            temp_video_widget->show();
            temp_player->play();
        video_widget_list_.append(temp_video_widget);
    }
}
void ScreenControl::SetModel(int x,int y)//设置屏幕模式
{
    //计算窗口宽高
    widget_width_=screen_width_/y;//计算窗口宽度
    widget_height_=screen_width_/x;//计算窗口高度
    //双重循环遍历三项列表
    for(int i=0;i<x;++i)//行
    {
        for(int j=0;j<y;++j)//列
        {
            video_widget_list_.at(i*y+j)->resize(widget_width_,widget_height_);//重设屏幕宽和高
            QRect temp(widget_width_*j,widget_height_*i,widget_width_, widget_height_);//计算坐标
            video_widget_list_.at(i*y+j)->setGeometry(temp);//设置坐标
        }
    }
}

