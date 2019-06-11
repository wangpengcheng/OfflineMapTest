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
    QString net_address="http://ivi.bupt.edu.cn/hls/cctv6hd.m3u8";
    test_videocodethead_->set_net_stream_address(net_address);
    test_videocodethead_->set_is_save();
    test_show_label_->set_decode_thread(test_videocodethead_);
    test_show_label_->resize(800,810);
    test_show_label_->show();
    Tool::TestNoteTool("VideoDecodeTheadTest MainTest",1);

}
