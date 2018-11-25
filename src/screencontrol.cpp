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

            QString video_path=QString("D:/minieyeone.mp4");
            //temp_playlist->addMedia(QUrl("file:///C:/Users/lin/Videos/Captures/2.mp4"));
            temp_playlist->addMedia(QUrl::fromLocalFile(video_path));
           // playlist->addMedia(QUrl::fromLocalFile(video_path));
            temp_playlist->setCurrentIndex(1);//设置播放间隔
            temp_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
            temp_player->setPlaylist(temp_playlist);
            temp_player->setVideoOutput(temp_video_widget);
        //将数据加入列表
        video_widget_list_.append(temp_video_widget);
        video_player_list_.append(temp_player);
        video_playlist_list_.append(temp_playlist);
    }
    SetModel(1,2);//设置模式为3*4
    VideoPlay();//视频播放
  //  video_player_list_.at(0)->play();
}
//设置屏幕模式
void ScreenControl::SetModel(const int x,
                             const int y)
{
    //计算窗口宽高
    widget_width_=screen_width_/y;//计算窗口宽度
    widget_height_=screen_height_/x;//计算窗口高度
    //双重循环遍历三项列表
    if(x*y<video_widget_list_.size())//如果小于视频播放列表数目就将剩下的隐藏
    {
        for(int a=x*y;a<video_widget_list_.size();++a)
        {
            video_widget_list_.at(a)->hide();
        }

    }else if (x*y>video_widget_list_.size()) {
        qDebug()<<"this number of model is over widget size,please,check again !!!!";
    }
    for(int i=0;i<x;++i)//行
    {
        for(int j=0;j<y;++j)//列
        {
            //设置中间变量指针
            QVideoWidget *temp_widget =video_widget_list_.at(i*y+j);
            //播放器
            QMediaPlayer *temp_player =video_player_list_.at(i*y+j);
            //更改位置
            video_widget_list_.at(i*y+j)->resize(widget_width_,widget_height_);//重设屏幕宽和高
           // temp_player->play();
            QRect temp(widget_width_*j,widget_height_*i,widget_width_, widget_height_);//计算坐标
            video_widget_list_.at(i*y+j)->setGeometry(temp);//设置窗口坐标
            video_widget_list_.at(i*y+j)->show();
            //video_player_list_.at(i*y+j)->play();
        }

    }

}

/*
 * 视频控制模块
*/
//视频列表均播放
void ScreenControl::VideoPlay()
{
    //判断小于虚拟屏幕数量和列表数量
    for(int i=0;i<video_player_list_.size();++i)
    {
        //video_player_list_.at(i)->play();
        qDebug()<<video_player_list_.at(i)->playlist()->dynamicPropertyNames();
    }

}
//视频列表均暂停
void ScreenControl::VideoPause()
{
    for(int i=0;i<video_player_list_.size();++i)
    {
        video_player_list_.at(i)->pause();
    }
}
