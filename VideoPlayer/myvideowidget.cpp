#include "myvideowidget.h"
#include "MapItems/tool.h"
MyVideoWidget::MyVideoWidget(QWidget *parent) : QWidget(parent)
{   // test
    //play_file_path_=QUrl::fromLocalFile(QString("C:/Users/lin/Videos/out/chedaoxian.mp4"));
    Init();
    //play_list_->addMedia(play_file_path_);
}
MyVideoWidget::MyVideoWidget(QUrl video_file_path)
{
    play_file_path_ = video_file_path;
    Init();
    play_list_->addMedia(play_file_path_);
}
MyVideoWidget::~MyVideoWidget()
{
    DELETE_QOBJECT(media_player_);
    DELETE_QOBJECT(play_list_);
    DELETE_QOBJECT(video_widget_);
}

void MyVideoWidget::Init()
{
    //初始化相关参数
    video_widget_ = new QVideoWidget(this);
    media_player_ = new QMediaPlayer(this);
    play_list_ = new QMediaPlaylist(this);
    video_layout_ = new QVBoxLayout(this);
    if (play_list_ != nullptr &&
        media_player_ != nullptr &&
        video_widget_ != nullptr)
    {
        play_list_->setCurrentIndex(1); //设置循环播放的初始序列
        play_list_->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        //设置开始绑定
        media_player_->setPlaylist(play_list_);
        media_player_->setVideoOutput(video_widget_);
        video_layout_->addWidget(video_widget_);
        video_layout_->setMargin(1);
        this->setLayout(video_layout_);
    }
    else
    {
        qDebug() << "Init MyVideoWidget file!!!!!";
    }
}
void MyVideoWidget::VideoPlay()
{
    media_player_->play();
}
void MyVideoWidget::VideoPause()
{
    media_player_->pause();
}
void MyVideoWidget::VideoStop()
{
    media_player_->stop();
}
