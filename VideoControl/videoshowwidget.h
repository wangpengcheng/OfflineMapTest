#ifndef VIDEOSHOWWIDGET_H
#define VIDEOSHOWWIDGET_H

#include <QWidget>
#include <QMenu>
#include <QTimer>

//模板类
#include "videoshowwidget.h"
#include "ui_videoshowwidget.h"
#include "myvideowidget.h"
#include "src/tool.h"
#include "streamvideowidget.h"

namespace Ui {
    class VideoShowWidget;
}
//为了使用模板提前定义信号和槽
class VideoShowWidgetBase: public QWidget{
     Q_OBJECT
public:
    explicit VideoShowWidgetBase(QWidget *parent = nullptr):QWidget(parent){}
    //公共槽函数
public slots:
    virtual void initForm()=0;
    virtual void initMenu()=0;
    //virtual void play_video_all()=0;
    virtual void snapshot_video_one()=0;
    virtual void snapshot_video_all()=0;

    virtual void show_video_all()=0;
    virtual void show_video_1()=0;
    virtual void show_video_4()=0;
    virtual void show_video_6()=0;
//    void show_video_8();
//    void show_video_9();
    virtual void show_video_7()=0;
    virtual void show_video_12()=0;
    virtual void hide_video_all()=0;
    virtual void change_video(int index, int v_row,int col)=0;
    virtual void change_video_1(int index)=0;//1视频改变
    virtual void change_video_4(int index)=0;
    virtual void change_video_6(int index)=0;
   // void change_video_8(int index);
  //  void change_video_9(int index);
    virtual void change_video_7(int index)=0;
    virtual void change_video_12(int index)=0;

signals:
    void play_changed(int index);
    void signal_change_video_1(int index); //改变1画面布局
    void signal_change_video_4(int index); //改变4画面布局
    void signal_change_video_6(int index); //改变6画面布局
    void signal_change_video_7(int index); //改变7画面布局
    void signal_change_video_12(int index);//改变12画面布局

};

//---------- template define start ---------
template <class T>
class VideoShowWidget : public VideoShowWidgetBase
{

public:
    explicit VideoShowWidget(QWidget *parent = nullptr);
    ~VideoShowWidget();
    //获取视频列表
    //inline QList<MyVideoWidget *> video_widgets(){return widgets;}
    //inline QList<StreamVideoWidget *> video_widgets(){return widgets;}
    inline QMenu* VideoMenu(){return videoMenu;}
    inline QList<T *> video_widgets(){return widgets;}
    inline bool is_videomax(){return videoMax;}
    inline int  video_count(){return videoCount;}
    //保护函数，设置键盘监听
protected:
    bool eventFilter(QObject *watched, QEvent *event);
    //公共槽函数
public:
    //public slots:
    void initForm();
    void initMenu();
//signals:
//void   play_changed(int index);
//public slots:
//    void play_video_all();
    void snapshot_video_one();
    void snapshot_video_all();

    void show_video_all();
    void show_video_1();
    void show_video_4();
    void show_video_6();
    void show_video_7();
    void show_video_12();
    void hide_video_all();
    void change_video(int index, int v_row,int col);
    void change_video_1(int index);
    void change_video_4(int index);
    void change_video_6(int index);
    void change_video_7(int index);
    void change_video_12(int index);
private:
    Ui::VideoShowWidget *ui;

    bool videoMax;
    int videoCount;
    QString video_type_;
    QMenu *videoMenu=nullptr;//右键选项
    //QList<MyVideoWidget *>widgets;//播放窗口队列
    //QList<StreamVideoWidget *>widgets;//播放窗口队列
    QList<T *>widgets;//播放窗口队列

};
//---------- template define end ---------

// 模板函数实现
#include "videoshowwidget.cpp"

#endif // VIDEOSHOWWIDGET_H
