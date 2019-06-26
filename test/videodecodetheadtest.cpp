#include "videodecodetheadtest.h"
#include "VideoControl/streamvideowidget.h"
#include "VideoControl/videodecodethread.h"
#include "src/tool.h"

VideoDecodeTheadTest::VideoDecodeTheadTest()
{
    if(test_show_label_==nullptr){
        test_show_label_=new StreamVideoWidget();
    }
    if(test_videocodethead_==nullptr)
    {

        test_videocodethead_=QSharedPointer<VideoDecodeThread>(new VideoDecodeThread());
    }
}
VideoDecodeTheadTest::~VideoDecodeTheadTest()
{
    DELETE_OBJECT(test_show_label_);
}

//主要的测试函数

void VideoDecodeTheadTest::MainTest()
{
    Tool::TestNoteTool("VideoDecodeTheadTest MainTest",0);
    QString net_address1="http://192.168.12.1:8080/?action=stream";
    //QString net_address2="rtsp://10.6.154.66:8554/test2";
    test_videocodethead_->set_net_stream_address(net_address1);
    test_videocodethead_->set_is_save(true);
    test_videocodethead_->set_is_save_by_time();//开启按照播放时长存储
    qDebug()<<test_videocodethead_->is_save_by_time();
    test_show_label_->set_decode_thread(test_videocodethead_);
    test_show_label_->resize(800,810);
    test_show_label_->show();
    Tool::TestNoteTool("VideoDecodeTheadTest MainTest",1);

}
