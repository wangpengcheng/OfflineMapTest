#ifndef VIDEODECODETHREAD_H
#define VIDEODECODETHREAD_H

#include <QWidget>
#include <QThread>
#include <QImage>

class VideoDecodeThread : public QThread
{
    Q_OBJECT
public:
    explicit VideoDecodeThread();
    VideoDecodeThread(QString url);
    ~VideoDecodeThread();
    //基本存取函数
    inline QString net_stream_address(){return net_stream_address_;}
    inline void set_net_stream_address(QString new_address){net_stream_address_=new_address;}
    void StartDecode();//开始解码
    //信号函数
signals:
    void SendFrame(QImage);//信号函数，发送图片帧
protected:
    void run();//重写QThread；run函数
private ://私有成员变量
    QString net_stream_address_=nullptr;
    //ffmpeg 解码变量


};

#endif // VIDEODECODETHREAD_H
