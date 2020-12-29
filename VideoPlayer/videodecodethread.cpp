#include "videodecodethread.h"
#include <QtDebug>
#include <QTime>
#include <iostream>
#include <MapItems/tool.h>
#if defined(__cplusplus) || defined (c_plusplus)
extern "C"
{
#endif
#include <stdio.h>
#include <stdlib.h>
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/pixfmt.h"
#include "libavutil/mathematics.h"
#include "libavutil/time.h"
#include "libswscale/swscale.h"

#if defined(__cplusplus) || defined (c_plusplus)
}
#endif
#include <stdio.h>
#include<iostream>

VideoDecodeThread::VideoDecodeThread(QObject *parent):QThread(parent)
{

}
VideoDecodeThread::VideoDecodeThread(QString url)
{
    net_stream_address_=url;
}
//VideoDecodeThread::~VideoDecodeThread()
//{
//    StopDecode();
//}

void VideoDecodeThread::StartDecode()
{
    if(!this->isRunning()){
        //重置现在跳出
        is_stop_now_=false;
        this->start();//开始线程
    }else {
        qDebug()<<"this decode is already running";
    }
}
//强制重新启动线程
void VideoDecodeThread::RestartDecode()
{
    //如果线程正在运行
    if(this->isRunning()){
        qDebug()<<"Is Stopping Thread : "<<QString::number(quintptr(this->currentThreadId()));
        //跳出解码
        StopDecode();
        //等待线程结束
        this->wait();
        qDebug()<<"Is Stopped Thread : "<<QString::number(quintptr(this->currentThreadId()));
    }
    StartDecode();//重新开始线程
}
/*
 * 2019-4-5 16:45:23
 * 不要问我为什么写这么烂
 * 老板要求三天搞定，我只有直接copy过来了
 * 能跑就行了，要啥自行车
 * 至于修改，估计这个项目，没有下一次修改的机会了
 *
 * 2019-6-11 17:26:53
 * 因为服务器没有搭建好，老板要求本地存储视频，估计之后代码会被弃用
 * 所以又回来改这块的代码了。。。。
 * 需求还很多，只有先实现功能了
 * 重构是不可能重构的，这辈子都不可能重构的
 * 但愿不会再有打开这个的机会
 *
 * 2019-6-26 9:48:54
 * 我又回来了，真香......
 * 添加一个随时自启动的选择存储功能
 *
*/
//线程运行,这里在进行解码的同时，将包复制，生成对应的视频流文件
void VideoDecodeThread::run()
{
    qDebug()<<"thread start";
    //------输入解码显示 变量 start------
    AVFormatContext *pFormatCtx;
    AVCodecContext *pCodecCtx;
    AVCodec *pCodec;
    AVFrame *pFrame, *pFrameRGB;
    AVPacket *packet;
    uint8_t *out_buffer;

    struct SwsContext *img_convert_ctx;
    int videoStream, i, numBytes;
    int ret, got_picture;
    //设定连接初始值
    char *url=NULL;

    avformat_network_init();   //初始化FFmpeg网络模块
    av_register_all();         //初始化FFMPEG  调用了这个才能正常适用编码器和解码器
    //初始化格式转换
    pFormatCtx = avformat_alloc_context();
    //设置其他相关参数
    AVDictionary *avdic=NULL;
    //选项关键字
    char option_key[]="rtsp_transport";
    char option_value[]="tcp";
    av_dict_set(&avdic,option_key,option_value,0);
    char option_key2[]="max_delay";
    char option_value2[]="100";//设置时间间隔
    av_dict_set(&avdic,option_key2,option_value2,0);
    //------输入解码显示 变量 end-------
    //rtsp地址，可根据实际情况修改
    //char url[]="rtsp://admin:admin@192.168.1.18:554/h264/ch1/main/av_stream";
    if(net_stream_address_==nullptr){
       qDebug()<<"No file";
       //使用默认源设置
       //net_stream_address_="http://ivi.bupt.edu.cn/hls/cctv1hd.m3u8";
       return;
    }
    QByteArray temp_url=net_stream_address_.toLocal8Bit();
    //获取字符
    url=temp_url.data();
    qDebug()<<url;
    //char url[]="udp://@192.168.5.148/test:1234";
    //char url[]="udp://@:1234";
    if(url==NULL){
        qDebug()<<"url is empty";
        return;
    }
    //打开输入流
    if (avformat_open_input(&pFormatCtx, url, NULL, NULL) != 0) {
        printf("can't open the file. \n");
        return;
    }
    //查找流文件信息
    if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
        printf("Could't find stream infomation.\n");
        return;
    }

    videoStream = -1;

    //循环查找视频中包含的流信息，直到找到视频类型的流
    //便将其记录下来 保存到videoStream变量中
    //这里我们现在只处理视频流  音频流先不管他
    //nb_streams代表有几路流，一般是2路；即音频和视频
    for (i = 0; i <pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStream = i;//记录视频流编号
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
    pCodecCtx->bit_rate =0;   //字节率初始化为0
    pCodecCtx->time_base.num=1;  //下面两行：一秒钟25帧
    pCodecCtx->time_base.den=25;
    pCodecCtx->frame_number=1;  //每包一个视频帧

    if (pCodec == NULL) {
        printf("Codec not found.\n");
        return;
    }

    //打开解码器
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
    //------ 根据输入流决定存储参数 start------
    //因为需要动态决定是否存储视频，因此所有变量必须在循环开始前准备好。
    // if(is_save_){

init_save://goto 语句帮助重复存储
    //------视频存储 模块 start------

        AVOutputFormat* out_stream_format=NULL;
        AVFormatContext* out_stream_format_context=NULL;
        AVCodecContext* out_stream_codec_context=NULL;
        AVCodec*  out_stream_codec=NULL;
        AVStream *out_stream=NULL,*in_stream=NULL;
        char* save_file_name=NULL;
        int out_ret;
        unsigned long long frame_index=0;
        int I_received = 0;
        unsigned long long frames_count = 30*save_second_time_;
        QDateTime current_date_time =QDateTime::currentDateTime();
        //文件命名使用时间+当前线程的内存地址前6位作为真实的地址
        video_save_name_=current_date_time.toString("yyyy-MM-dd-hh-mm-ss-zzz-")+QString::number(quintptr(this->currentThreadId())).mid(0,5);
        qDebug()<<video_save_name_;
        file_full_path_=Tool::CreatFile(video_save_dir_name_,video_save_name_,video_save_type_);
        QByteArray temp_path_byte=file_full_path_.toLocal8Bit();
        save_file_name=temp_path_byte.data();

    //------视频存储 模块 end------

        //创建输入流
        out_stream=pFormatCtx->streams[videoStream];
        //打开输出流
        avformat_alloc_output_context2(&out_stream_format_context,NULL,NULL,save_file_name);
        if(!out_stream_format_context)
        {
            qDebug()<<"Could not create output context \n";
            out_ret=AVERROR_UNKNOWN;
            avformat_free_context(out_stream_format_context);
        }else {
            out_stream_format=out_stream_format_context->oformat;
            //根据输入创建输出流
            out_stream=avformat_new_stream(out_stream_format_context,pFormatCtx->streams[videoStream]->codec->codec);
            if(!out_stream)
            {
                qDebug()<<"Failed allocating output stream.\n";
                out_ret = AVERROR_UNKNOWN;
                avformat_free_context(out_stream_format_context);


            }else {
                //将输入流的编码信息复制到输出流
                out_ret=avcodec_copy_context(out_stream->codec,pFormatCtx->streams[videoStream]->codec);
                if(out_ret<0){
                    qDebug()<<"Failed to copy context from input to output stream codec context\n";
                    avformat_free_context(out_stream_format_context);
                }else {
                    out_stream->codec->codec_tag = 0;
                    if(out_stream_format_context->oformat->flags& AVFMT_GLOBALHEADER){
                         out_stream->codec->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
                    }
                    //Dump format--------------------
                   av_dump_format(out_stream_format_context,0,save_file_name,1);
                   qDebug()<<out_stream_format->flags;
                   //打开输出文件
                       if(!(out_stream_format->flags & AVFMT_NOFILE))
                       {
                           ret = avio_open(&out_stream_format_context->pb,save_file_name,AVIO_FLAG_WRITE);
                           if(ret<0)
                           {
                               printf("Could not open output URL '%s'",save_file_name);
                               if(out_stream_format_context&&!(out_stream_format->flags & AVFMT_NOFILE))
                               {
                                   avio_close(out_stream_format_context->pb);
                               }
                               avformat_free_context(out_stream_format_context);
                           }else{
                               //写文件头到输出文件
                               out_ret=avformat_write_header(out_stream_format_context,NULL);
                               if(out_ret<0){
                                   printf("Error occured when opening output URL\n");
                                   if(out_stream_format_context&&!(out_stream_format->flags & AVFMT_NOFILE))
                                   {
                                       avio_close(out_stream_format_context->pb);
                                   }
                                   avformat_free_context(out_stream_format_context);
                               }
                           }
                       }
                }
            }
        }
    //}

    //------ 根据输入流决定存储参数 end  ------


    //持续解包
    while (1)
    {
        if(is_stop_now_){//针对整个线程的
            qDebug()<<"jump out while ,stop get pack";
            break;
        }
        //读取pack包
        if (av_read_frame(pFormatCtx, packet) < 0)
        {
            break; //这里认为视频读取完了
        }

        if (packet->stream_index == videoStream) {
            //将获取的帧解码出来
            ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture,packet);
            if (ret < 0) {
                printf("decode error.\n");
                return;
            }

            if (got_picture) {
                //转换图片格式
                sws_scale(img_convert_ctx,
                        (uint8_t const * const *) pFrame->data,
                        pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data,
                        pFrameRGB->linesize);
                //把这个RGB数据 用QImage加载
                QImage tmpImg((uchar *)out_buffer,pCodecCtx->width,pCodecCtx->height,QImage::Format_RGB32);
                QImage image = tmpImg.copy(); //把图像复制一份 传递给界面显示
                emit SendFrame(image);  //发送信号图片
            }
            //------ 循环读取和写入帧 start ------
            if(is_save_){//判断是否需要存入
                //如果是再次存储
                if(is_resave_){//注意这里一定要先停止在重新存储
                    //重置 重复存储选项
                    is_resave_=false;
                    goto init_save;

                }
                in_stream=pFormatCtx->streams[packet->stream_index];
                out_stream=out_stream_format_context->streams[packet->stream_index];
                //copy packet
                //转换 PTS/DTS 时序
                packet->pts = av_rescale_q_rnd(packet->pts,in_stream->time_base,out_stream->time_base,(enum AVRounding)(AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
                packet->dts = av_rescale_q_rnd(packet->dts, in_stream->time_base, out_stream->time_base, (enum AVRounding)(AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
                packet->duration=av_rescale_q(packet->duration,in_stream->time_base,out_stream->time_base);
                packet->pos=-1;
                //此while循环中并非所有packet都是视频帧，当收到视频帧时记录一下，仅此而已
                if(packet->stream_index==videoStream)
                {
                    if ((packet->flags & AV_PKT_FLAG_KEY) && (I_received == 0)){
                        I_received = 1;
                    }
                    if (I_received == 0){
                        continue;
                    }
                    qDebug()<<"Receive "<<frame_index<<" video frames from input URL\n";
                    frame_index++;
                } else {
                    continue;
                }
                //这里可以根据自己需要设置，是否存储定长的视频，一般设置为false
                if(is_save_by_time_){//正常情况下一班都不开启
                    if (frame_index == frames_count){
                        is_save_=false;//设置接下来的帧都不储存
                        //直接写入文件
                        av_write_trailer(out_stream_format_context);
                        qDebug()<<"video saved";
                        continue;
                    }
                }

                //将包数据写入到文件。
                out_ret = av_interleaved_write_frame(out_stream_format_context,packet);
                if(ret < 0)
                {
                    /**
                     * 当网络有问题时，容易出现到达包的先后不一致，pts时序混乱会导致
                     * av_interleaved_write_frame函数报 -22 错误。暂时先丢弃这些迟来的帧吧
                     * 若所大部分包都没有pts时序，那就要看情况自己补上时序（比如较前一帧时序+1）再写入。
                     */
                    if(ret==-22){
                        continue;
                    }else{
                        qDebug()<<"Error muxing packet.error code"<<out_ret;
                        break;
                    }
                }
                if(is_save_stop_)
                {
                    av_write_trailer(out_stream_format_context);
                    qDebug()<<"video saved";
                    is_save_=false;//设置接下来的帧都不储存
                        //释放写相关内存
                        if(out_stream_format_context && !(out_stream_format->flags & AVFMT_NOFILE)){
                                avio_close(out_stream_format_context->pb);
                            avformat_free_context(out_stream_format_context);
                            if(out_ret<0 && out_ret != AVERROR_EOF)
                            {
                                qDebug()<<"Free Error occured";
                            }
                        }else{
                            qDebug()<<"save file delected";
                        }

                }
                //使用完之后重置is_save_stop;
                is_save_stop_=false;
            }

            //------ 循环读取和写入帧 end ------

        }
        //释放内存资源
        av_free_packet(packet); //释放资源,否则内存会一直上升
        //msleep(0.02); //停一停  不然放的太快了
    }
free_code://释放跳转语句
    //释放内存
    av_free(out_buffer);
    av_free(pFrameRGB);
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);
    av_dict_free(&avdic);
free_save://free_save 跳转语句
    //写文件尾部
    av_write_trailer(out_stream_format_context);
    //释放写相关内存
        //释放写相关内存
        if(out_stream_format_context && !(out_stream_format->flags & AVFMT_NOFILE)){
                avio_close(out_stream_format_context->pb);
            avformat_free_context(out_stream_format_context);
            if(out_ret<0 && out_ret != AVERROR_EOF)
            {
                qDebug()<<"Free Error occured";
            }
         }


    qDebug()<<"------ thread end ------";
}
//将当前视频存储到数据库中。
void VideoDecodeThread::InsertVideoInformToSql(int record_id)
{
    if(record_id!=NULL&&
       !file_full_path_.isEmpty()&&
            !video_save_name_.isEmpty()){
    Tool::TestNoteTool("InsertVideoInformToSql",0);
    QJsonObject temp_data;
    QDateTime current_date_time =QDateTime::currentDateTime();
    //文件命名使用时间+当前线程的内存地址前6位作为真实的地址
    QString video_time=current_date_time.toString("yyyy-MM-dd hh:mm:ss:zzz");
    temp_data.insert("record_id",record_id);
    temp_data.insert("video_path",file_full_path_);
    temp_data.insert("video_name",video_save_name_);
    temp_data.insert("start_time",video_time);
    QString request_url="http://localhost/re_save_video.php";
    QJsonObject test=Tool::NetWorkGet(request_url,temp_data);
    qDebug()<<test.size();
    qDebug()<<test.isEmpty();
    QJsonArray result_array=test.value("result").toArray();
    qDebug()<<result_array.at(0);
    qDebug()<<result_array.size();
    }else{
        qDebug()<<"input is empty()";
    }
    Tool::TestNoteTool("InsertVideoInformToSql",1);
}
void VideoDecodeThread::StartSaveVideo(int record_id)
{
    //如果线程正在运行

    if(this->isRunning()){
        //判断是否为第一次存储
        if(video_save_times_>0){
//            //清除相关数据
//            file_full_path_.clear();
//            video_save_name_.clear();
            //设置信号量
            is_resave_=true;
        }
        is_save_=true;//设置开始存储
        //连续等待，直到文件名字不为空即开始解码
        while (1) {
            if((!file_full_path_.isEmpty()))
            {
                InsertVideoInformToSql(record_id);
                break;
            }
        }
        qDebug()<<"------ start save video with recod_id "<<record_id<<"------";
        ++video_save_times_;//存储次数+1
        qDebug()<<"This Save time is: "<<video_save_times_;
    } else {
        qDebug()<<"------ Thread : "<<this->thread()->currentThreadId()<<"is not Running Or Saving,Please  Start it ------";
    }

}
void VideoDecodeThread::StopSaveVideo()
{
    if(this->isRunning()){
        if(!is_save_stop_){
            is_save_stop_=true;
        }
        //is_save_=false;//设置是否存储为假
        qDebug()<<"------ Thread : "<<this->thread()->currentThreadId()<<"stoped ------";
    } else {
        qDebug()<<"------ Thread : "<<this->thread()->currentThreadId()<<"is not Running ,Please  Start it ------";
    }
}
