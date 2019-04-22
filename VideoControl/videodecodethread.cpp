#include "videodecodethread.h"
#include <QtDebug>
#if defined(__cplusplus) || defined (c_plusplus)
extern "C"
{
#endif

#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/pixfmt.h"
#include "libswscale/swscale.h"

#if defined(__cplusplus) || defined (c_plusplus)
}
#endif
#include <stdio.h>
#include<iostream>

VideoDecodeThread::VideoDecodeThread()
{

}
VideoDecodeThread::VideoDecodeThread(QString url)
{
    net_stream_address_=url;
}
VideoDecodeThread::~VideoDecodeThread()
{

}

void VideoDecodeThread::StartDecode()
{
    if(!this->isRunning()){
        this->start();//开始线程
    }else {
        qDebug()<<"this decode is already running";
    }
}
//线程运行状况
void VideoDecodeThread::run()
{
    qDebug()<<"thread start";
    AVFormatContext *pFormatCtx;
    AVCodecContext *pCodecCtx;
    AVCodec *pCodec;
    AVFrame *pFrame, *pFrameRGB;
    AVPacket *packet;
    uint8_t *out_buffer;

    static struct SwsContext *img_convert_ctx;
    int videoStream, i, numBytes;
    int ret, got_picture;
    //设定连接初始值
    char *url=NULL;

    avformat_network_init();   ///初始化FFmpeg网络模块
    av_register_all();         //初始化FFMPEG  调用了这个才能正常适用编码器和解码器
    //设置上下文
    //Allocate an AVFormatContext.
    pFormatCtx = avformat_alloc_context();
    //设置其他相关参数
    AVDictionary *avdic=NULL;
    char option_key[]="rtsp_transport";
    char option_value[]="tcp";
    av_dict_set(&avdic,option_key,option_value,0);
    char option_key2[]="max_delay";
    char option_value2[]="100";
    av_dict_set(&avdic,option_key2,option_value2,0);
    ///rtsp地址，可根据实际情况修改
    //char url[]="rtsp://admin:admin@192.168.1.18:554/h264/ch1/main/av_stream";
    if(net_stream_address_==nullptr){
       qDebug()<<"No file";
       //使用默认源设置
       net_stream_address_="http://ivi.bupt.edu.cn/hls/cctv1hd.m3u8";
    }
    QByteArray temp_url=net_stream_address_.toLocal8Bit();
    url=temp_url.data();
    std::cout<<url<<std::endl;
    qDebug()<<url;
    //char url[]="udp://@192.168.5.148/test:1234";
    //char url[]="udp://@:1234";
    if(url==NULL){
        qDebug()<<"url is empty";
        return;
    }
    if (avformat_open_input(&pFormatCtx, url, NULL, NULL) != 0) {
        printf("can't open the file. \n");
        return;
    }

    if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
        printf("Could't find stream infomation.\n");
        return;
    }

    videoStream = -1;

    //循环查找视频中包含的流信息，直到找到视频类型的流
    //便将其记录下来 保存到videoStream变量中
    //这里我们现在只处理视频流  音频流先不管他
    for (i = 0; i <pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStream = i;
        }
    }

    //如果videoStream为-1 说明没有找到视频流
    if (videoStream == -1) {
        printf("Didn't find a video stream.\n");
        return;
    }
    //查找解码器
    pCodecCtx = pFormatCtx->streams[videoStream]->codec;
    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    //设置解码器参数
    pCodecCtx->bit_rate =0;   //初始化为0
    pCodecCtx->time_base.num=1;  //下面两行：一秒钟25帧
    pCodecCtx->time_base.den=25;
    pCodecCtx->frame_number=1;  //每包一个视频帧

    if (pCodec == NULL) {
        printf("Codec not found.\n");
        return;
    }

    ///打开解码器
    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
        printf("Could not open codec.\n");
        return;
    }
    //分配解码帧内存
    pFrame = av_frame_alloc();
    //分配RGB颜色帧通道内存
    pFrameRGB = av_frame_alloc();

    //这里我们改成了 将解码后的YUV数据转换成RGB32
    img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height,
            pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height,
            AV_PIX_FMT_RGB32, SWS_BICUBIC, NULL, NULL, NULL);
    //获取图片内存大小
    numBytes = avpicture_get_size(AV_PIX_FMT_RGB32, pCodecCtx->width,pCodecCtx->height);
    //为图片分配内存
    out_buffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));
    //将图片转化为新帧
    avpicture_fill((AVPicture *) pFrameRGB, out_buffer, AV_PIX_FMT_RGB32,
            pCodecCtx->width, pCodecCtx->height);
    //获取图片面积大小
    int y_size = pCodecCtx->width * pCodecCtx->height;
    //添加包
    packet = (AVPacket*)malloc(sizeof(AVPacket)); //分配一个packet
    av_new_packet(packet, y_size); //分配packet的数据
    //持续解包
    while (1)
    {
        if (av_read_frame(pFormatCtx, packet) < 0)
        {
            break; //这里认为视频读取完了
        }

        if (packet->stream_index == videoStream) {
            ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture,packet);
            if (ret < 0) {
                printf("decode error.\n");
                return;
            }

            if (got_picture) {
                sws_scale(img_convert_ctx,
                        (uint8_t const * const *) pFrame->data,
                        pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data,
                        pFrameRGB->linesize);
                //把这个RGB数据 用QImage加载
                QImage tmpImg((uchar *)out_buffer,pCodecCtx->width,pCodecCtx->height,QImage::Format_RGB32);
                QImage image = tmpImg.copy(); //把图像复制一份 传递给界面显示
                emit SendFrame(image);  //发送信号图片
            }
        }
        //释放内存资源
        av_free_packet(packet); //释放资源,否则内存会一直上升
        //msleep(0.02); //停一停  不然放的太快了
    }
    //释放内存
    av_free(out_buffer);
    av_free(pFrameRGB);
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);
    qDebug()<<"thread end";
}
