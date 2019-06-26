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
    //~VideoDecodeThread();
    //基本存取函数
    inline QString net_stream_address(){return net_stream_address_;}
    inline void stream_type(unsigned int a){stream_type_=a;}
    inline unsigned stream_type(){return stream_type_;}
    inline void set_net_stream_address(QString new_address){net_stream_address_=new_address;}

    //-----视频存取函数 start-----
    inline void set_is_save(bool is_save){is_save_=is_save;}
    inline bool is_save(){return is_save_;}
    inline bool is_stop_now(){return is_stop_now_;}
    inline void set_is_stop_now(bool is_stop){is_stop_now_=is_stop;}
    inline bool is_save_stop(){return is_save_stop_;}
    inline QString video_save_type(){return video_save_type_;}
    inline void set_video_save_type(QString new_type){video_save_type_=new_type;}
    inline bool is_save_by_time(){return  is_save_by_time_;}
    inline void set_is_save_by_time(){is_save_by_time_=!is_save_by_time_;}
    inline unsigned long save_second_time(){return save_second_time_;}
    inline void set_save_second_time(unsigned long new_time){save_second_time_=new_time;}
    inline QString video_save_dir_name(){return video_save_dir_name_;}
    inline void set_video_save_dir_name(const QString new_dir_name){video_save_dir_name_=new_dir_name;}
    inline QString file_full_path(){return this->file_full_path_;}
    //----- 视频存取函数 end------
    //----- ffmpeg解码的中间函数变化
public slots:
    void StopDecode(){is_stop_now_=true;}//通过直接设置参数，跳出循环,方便内存的销毁和使用
    //void StopSave(){}
    void StartDecode();//开始解码
    void RestartDecode(); //重新开始解码
    void InsertVideoInformToSql(int record_id);//将生成的视频信息存储到数据库
    void StartSaveVideo(int record_id);//开始存储视频
    void StopSaveVideo();//如果正在存储就停止存储
    //信号函数
signals:
    void SendFrame(QImage);//信号函数，发送图片帧
protected:
    void run();//重写QThread；run函数
private ://私有成员变量
    QString net_stream_address_=nullptr;
    unsigned int stream_type_=0;//视频流方式，0是rtsp,1是mjpg
    bool is_stop_now_=false;//用来在while中控制视屏播放；当设置为true时，直接停止播放。线程结束，防止因为意外中断，内存释放失败
    //ffmpeg 解码变量
    bool is_free=false; //释放完成内存释放
    // 视频流存储相关变量
    bool is_save_=false;//是否将视频存储为mp4。
    bool is_save_stop_=false;//停止存储
    QString video_save_dir_name_="Videos";
    QString video_save_name_=nullptr;//设置视频存储的名字
    QString video_save_type_="flv";//设置默认存储的文件后缀名，默认为mp4
    bool is_save_by_time_=false;//是否按照固定时长来设置存储视频长度，默认按照播放时长来存储
    unsigned long save_second_time_=50;//设置默认的时间 以秒为单位
    QString file_full_path_;
    bool is_save_free=false; //视频存储释放变量，防止二次释放内存
    int video_save_times_=0;//记录存储视频次数信息
    bool is_resave_=false; //是否重新存储

};

#endif // VIDEODECODETHREAD_H
