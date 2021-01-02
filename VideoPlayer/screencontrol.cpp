#include "screencontrol.h"

ScreenControl::ScreenControl()
{
    Init(); //初始化内存分配
}
ScreenControl::ScreenControl(QDesktopWidget *desktop)
{
    m_desktop = desktop;
    m_screen_count = desktop->screenCount();
    if (m_screen_count == 1)
    {
        SetScreenSize(desktop->size().width(), desktop->size().height());
    }
    Init();
}

int ScreenControl::screen_count()
{
    return this->m_screen_count;
}

QDesktopWidget *ScreenControl::desktop()
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
    return video_playlist_list_;
}
int ScreenControl::screen_height()
{
    return screen_height_;
}
int ScreenControl::screen_width()
{
    return screen_width_;
}
int ScreenControl::widget_height()
{
    return widget_height_;
}
int ScreenControl::widget_width()
{
    return widget_width_;
}
void ScreenControl::SetScreenSize(const int width, const int height)
{
    screen_width_ = width;
    screen_height_ = height;
}
void ScreenControl::SetWindowScreen(QWidget *widget, const int screen_number)
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
void ScreenControl::Init()
{
    qDebug() << "start Init";
    qDebug() << "Clean list";
    //清除队列列表
    video_player_list_.clear();
    video_widget_list_.clear();
    video_playlist_list_.clear();
    //初始化内存分配
    for (int i = 0; i < virtual_screen_count_; i++)
    {
        QVideoWidget *temp_video_widget = new QVideoWidget();
        QMediaPlayer *temp_player = new QMediaPlayer();
        QMediaPlaylist *temp_playlist = new QMediaPlaylist();

        QString video_path = QString("C:/Users/lin/Videos/Captures/2.mp4");
        //temp_playlist->addMedia(QUrl("file:///C:/Users/lin/Videos/Captures/2.mp4"));
        temp_playlist->addMedia(QUrl::fromLocalFile(video_path));
        // playlist->addMedia(QUrl::fromLocalFile(video_path));
        temp_playlist->setCurrentIndex(1); //设置播放间隔
        temp_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        temp_player->setPlaylist(temp_playlist);
        temp_player->setVideoOutput(temp_video_widget);
        //将数据加入列表
        video_player_list_.append(temp_player);
        video_widget_list_.append(temp_video_widget);
        video_playlist_list_.append(temp_playlist);
    }
}
//设置屏幕模式
void ScreenControl::SetModel(const int x,
                             const int y)
{
    //计算窗口宽高
    widget_width_ = screen_width_ / y;   //计算窗口宽度
    widget_height_ = screen_height_ / x; //计算窗口高度
    if (show_widget_count_ == 0)         //初始化show_widget_count_
    {
        show_widget_count_ = virtual_screen_count_;
    }
    //双重循环遍历三项列表
    if (x * y < show_widget_count_) //如果小于视频正在播放数目就将剩下的隐藏
    {
        for (int a = x * y; a < show_widget_count_ && a < video_widget_list_.size(); ++a)
        {
            qDebug() << video_widget_list_.size();
            video_widget_list_.at(a)->hide();
        }
    }
    else if (x * y > video_widget_list_.size())
    {
        qDebug() << "this number of model is over widget size,please,check again !!!!";
    }
    for (int i = 0; i < x; ++i) //行
    {
        for (int j = 0; j < y; ++j) //列
        {
            //设置中间变量指针
            QVideoWidget *temp_widget = video_widget_list_.at(i * y + j);
            //重设屏幕宽和高
            temp_widget->resize(widget_width_, widget_height_);
            //计算坐标
            QRect temp(widget_width_ * j, widget_height_ * i, widget_width_, widget_height_);
            //更改位置
            temp_widget->setGeometry(temp); //设置窗口坐标
            // delete temp_widget;
        }
    }
    //更新显示窗口数量
    show_widget_count_ = x * y;
    //播放视频
    VideoPlay();
}

/*
 * 视频控制模块
*/
//视频列表均播放
void ScreenControl::VideoPlay()
{
    for (int i = 0; i < video_player_list_.size() && i < show_widget_count_; ++i)
    {
        if (video_widget_list_.at(i)->isHidden())
        {
            video_widget_list_.at(i)->show();
        }
        video_player_list_.at(i)->play();
    }
}
//视频列表均暂停
void ScreenControl::VideoPause()
{
    for (int i = 0; i < show_widget_count_ && i < video_player_list_.size(); ++i)
    {
        video_player_list_.at(i)->pause();
    }
}
