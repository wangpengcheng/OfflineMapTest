#ifndef VIDEODECODETHREAD_H
#define VIDEODECODETHREAD_H

#include <QWidget>
#include <QThread>
#include <QImage>

class VideoDecodeThread : public QThread
{
    Q_OBJECT
public:
    explicit VideoDecodeThread(QObject *parent = nullptr);
    VideoDecodeThread(QString url);
    ~VideoDecodeThread();
    //基本存取函数
    inline QString net_stream_address(){return net_stream_address_;}
    inline void stream_type(unsigned int a){stream_type_=a;}
    inline unsigned stream_type(){return stream_type_;}
    inline void set_net_stream_address(QString new_address){net_stream_address_=new_address;}
    inline void set_is_save(){is_save_=!is_save_;}
    inline bool is_save(){return is_save_;}
    void StartDecode();//开始解码
    //信号函数
signals:
    void SendFrame(QImage);//信号函数，发送图片帧
protected:
    void run();//重写QThread；run函数
private ://私有成员变量
    QString net_stream_address_=nullptr;
    unsigned int stream_type_=0;//视频流方式，0是rtsp,1是mjpg
    //ffmpeg 解码变量

    bool is_save_=false;//是否将视频存储为flv。


};

#endif // VIDEODECODETHREAD_H
