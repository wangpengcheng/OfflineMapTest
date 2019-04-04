#include "myvideowidget.h"

MyVideoWidget::MyVideoWidget(QUrl video_file_path)
{
    //初始化相关参数
    video_widget_=new QVideoWidget();
    media_player_=new QMediaPlayer();
    play_list_=new QMediaPlaylist();
    video_layout_=new QVBoxLayout();
    if(play_list_!=nullptr&&
       media_player_!=nullptr&&
       video_widget_!=nullptr){
        play_list_->addMedia(video_file_path);
        play_list_->setCurrentIndex(1);//设置循环播放的初始序列
        play_list_->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        //设置开始绑定
        media_player_->setPlaylist(play_list_);
        media_player_->setVideoOutput(video_widget_);
        video_widget_->setParent(this);
        //video_widget_->resize(this->width(),this->height());
        //video_widget_->resize();
        video_layout_->addWidget(video_widget_);
        video_layout_->setMargin(2);
        this->setLayout(video_layout_);

    }else {
        qDebug()<<"Init MyVideoWidget file!!!!!";
    }

}
MyVideoWidget::~MyVideoWidget()
{
    if(media_player_!=nullptr)
    {
        delete []  media_player_;
        media_player_=nullptr;
    }
    if(play_list_!=nullptr)
    {
        delete [] play_list_;
        play_list_=nullptr;
    }
    if(video_widget_!=nullptr)
    {
        delete [] video_widget_;
        video_widget_=nullptr;
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

