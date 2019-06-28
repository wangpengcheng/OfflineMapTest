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

//---------- template realize start ---------

template < class T>
VideoShowWidget<T>::VideoShowWidget(QWidget *parent):VideoShowWidgetBase(parent),
    ui(new Ui::VideoShowWidget)
{
    ui->setupUi(this);
    initForm();
    initMenu();
    //show_video_all();
    change_video_4(0);
    //QTimer::singleShot(1000, this, SLOT(play_video_all()));
}

template < class T>
VideoShowWidget<T>::~VideoShowWidget()
{
    delete ui;
    DELETE_QOBJECT(videoMenu);
}
template < class T>
bool VideoShowWidget<T>::eventFilter(QObject *watched, QEvent *event)
{
    //监听全局事件
    if (event->type() == QEvent::MouseButtonDblClick) {
            //MyVideoWidget *widget = qobject_cast<MyVideoWidget *>(watched);//获取双击对象
            T *widget = qobject_cast<T *>(watched);
            if (!videoMax) {//如果没有处于最大模式则，将其设置为最大模式
                hide_video_all();
                ui->gridLayout->addWidget(widget, 0, 0,1,1);
                widget->setVisible(true);
                videoMax = true;
                qDebug()<<"DblClick";
            } else {//否则显示所有
                videoMax = false;
                show_video_all();
            }
        } else if (event->type() == QEvent::MouseButtonPress) {
            if (qApp->mouseButtons() == Qt::RightButton) {//如果点击右键显示按钮
                videoMenu->exec(QCursor::pos());
            }
        }

        return QWidget::eventFilter(watched, event);
}
template < class T>
void VideoShowWidget<T>::initForm()
{
    //设置QSS样式
//    QStringList qss;
//    qss.append("QFrame{border:2px solid #000000;}");
//    qss.append("MyVideoWidget{font:75 25px;color:#F0F0F0;border:2px solid #AAAAAA;background:#000000;}");
//    qss.append("MyVideoWidget:focus{border:2px solid #00BB9E;background:#555555;}");
//    ui->frame->setStyleSheet(qss.join(""));
    videoMax=false;
    videoCount=12;//设置视频总数
    //ui->gridLayout->setSpacing(5);//设置间距
    //ui->gridLayout->setMargin(5);//设置边距
    video_type_="1_12";
    //QString video_path=QString("C:/Users/lin/Videos/Captures/2.mp4");
    //初始化并添加视频
    for (int i = 0; i < videoCount; ++i) {
          //MyVideoWidget *widget = new MyVideoWidget(video_path);
          T *widget = new T();
          widget->setObjectName(QString("video%1").arg(i + 1));
          widget->installEventFilter(this);
          widget->setFocusPolicy(Qt::StrongFocus);
          //二选一可以选择显示文字,也可以选择显示背景图片
          //widget->setText(QString("通道 %1").arg(i + 1));
          //widget->setPixmap(QPixmap(":/bg_novideo.png"));
          widgets.append(widget);
      }
    //设置边距
    ui->gridLayout->setMargin(1);
    ui->gridLayout->setSpacing(1);
}

//初始化右侧按键
template < class T>
void VideoShowWidget<T>::initMenu()
{
    videoMenu = new QMenu(this);
    videoMenu->setStyleSheet(QStringLiteral("font: 10pt \"微软雅黑\";"));
    videoMenu->addAction(QStringLiteral("截图当前视频"), this, SLOT(snapshot_video_one()));
    videoMenu->addAction(QStringLiteral("截图所有视频"), this, SLOT(snapshot_video_all()));
    videoMenu->addSeparator();

    QMenu *menu1 = videoMenu->addMenu(QStringLiteral("切换到1画面"));
    menu1->addAction(QStringLiteral("通道1"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("通道2"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("通道3"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("通道4"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("通道5"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("通道6"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("通道7"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("通道8"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("通道9"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("通道10"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("通道11"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("通道12"), this, SLOT(show_video_1()));

    QMenu *menu4 = videoMenu->addMenu(QStringLiteral("切换到4画面"));
    menu4->addAction(QStringLiteral("通道1-通道4"), this, SLOT(show_video_4()));
    menu4->addAction(QStringLiteral("通道5-通道8"), this, SLOT(show_video_4()));
    menu4->addAction(QStringLiteral("通道9-通道12"), this, SLOT(show_video_4()));

    QMenu *menu6 = videoMenu->addMenu(QStringLiteral("切换到6画面"));
    menu6->addAction(QStringLiteral("通道1-通道6"), this, SLOT(show_video_6()));
    menu6->addAction(QStringLiteral("通道7-通道12"), this, SLOT(show_video_6()));
    QMenu *menu7=videoMenu->addMenu(QStringLiteral("切换到7画面"));
    menu7->addAction(QStringLiteral("通道1-通道7"), this, SLOT(show_video_7()));
    menu7->addAction(QStringLiteral("通道6-通道12"), this, SLOT(show_video_7()));

    videoMenu->addAction(QStringLiteral("切换到12画面"), this, SLOT(show_video_12()));

}
template <class T>
void VideoShowWidget<T>::snapshot_video_one()
{

}
template <class T>
void VideoShowWidget<T>::snapshot_video_all()
{

}

//显示所有视频
template <class T>
void VideoShowWidget<T>::show_video_all()
{
    if (video_type_ == "1_4") {
            change_video_4(0);
        } else if (video_type_ == "5_8") {
            change_video_4(4);
        } else if (video_type_ == "9_12") {
            change_video_4(8);
        } else if (video_type_ == "1_6") {
            change_video_6(0);
        } else if (video_type_ == "7_12") {
            change_video_6(6);
        } else if(video_type_ == "1_7"){
            change_video_7(0);
        } else if (video_type_=="6_12") {
            change_video_7(5);
        } else if (video_type_ == "1_12") {
            change_video_12(0);
        }
}
//显示1画面
template <class T>
void VideoShowWidget<T>::show_video_1()
{
    videoMax = false;
    QString videoType;
    int index = 0;
    QAction *action = qobject_cast<QAction *>(sender());
    QString name = action->text();
    if (name == QStringLiteral("通道1")) {
        index = 0;
        videoType = "0_0";
    } else if (name == QStringLiteral("通道2")) {
        index = 1;
        videoType = "0_1";
    } else if (name == QStringLiteral("通道3")) {
        index = 2;
        videoType = "0_2";
    } else if (name == QStringLiteral("通道4")) {
        index = 3;
        videoType = "0_3";
    } else if (name == QStringLiteral("通道5")) {
        index = 4;
        videoType = "0_4";
    } else if (name == QStringLiteral("通道6")) {
        index = 5;
        videoType = "0_5";
    } else if (name == QStringLiteral("通道7")) {
        index = 6;
        videoType = "0_6";
    } else if (name == QStringLiteral("通道8")) {
        index = 7;
        videoType = "0_7";
    } else if (name == QStringLiteral("通道9")) {
        index = 8;
        videoType = "0_8";
    } else if (name == QStringLiteral("通道10")) {
        index = 9;
        videoType = "0_9";
    } else if (name == QStringLiteral("通道11")) {
        index = 10;
        videoType = "0_10";
    } else if (name == QStringLiteral("通道12")) {
        index = 11;
        videoType = "0_11";
    }
    if (this->video_type_ != videoType) {
        this->video_type_ = videoType;
        change_video_1(index);
    }else {
        qDebug()<<"It is already in this model,need no change ";
    }
}
//显示4画面
template <class T>
void VideoShowWidget<T>::show_video_4()
{
    videoMax = false;
    QString videoType;
    int index = 0;

    QAction *action = qobject_cast<QAction *>(sender());
    QString name = action->text();
    qDebug()<<name;
    if (name == QStringLiteral("通道1-通道4")) {
        index = 0;
        videoType = "1_4";
    } else if (name == QStringLiteral("通道5-通道8")) {
        index = 4;
        videoType = "5_8";
    } else if (name == QStringLiteral("通道9-通道12")) {
        index = 8;
        videoType = "9_12";
    }
    if (this->video_type_ != videoType) {
        this->video_type_ = videoType;
        change_video_4(index);
    }else {
        qDebug()<<"It is already in this model,need no change ";
    }
}
//显示6视频
template <class T>
void VideoShowWidget<T>::show_video_6()
{
    videoMax = false;
    QString videoType;
    int index = 0;

    QAction *action = (QAction *)sender();
    QString name = action->text();

    if (name == QStringLiteral("通道1-通道6")) {
        index = 0;
        videoType = "1_6";
    } else if (name == QStringLiteral("通道7-通道12")) {
        index = 6;
        videoType = "7_12";
    }
    if (this->video_type_ != videoType) {
        this->video_type_ = videoType;
        change_video_6(index);
    }
    qDebug()<<"video_type is :"<<video_type_;
}
//显示7个视频
template <class T>
void VideoShowWidget<T>::show_video_7()
{
    videoMax = false;
    QString videoType;
    int index = 0;

    QAction *action = ( QAction *)sender();
    QString name = action->text();

    if (name == QStringLiteral("通道1-通道7")) {
        index = 0;
        videoType = "1_7";
    } else if (name == QStringLiteral("通道6-通道12")) {
        index = 5;
        videoType = "6_12";
    }
    if (this->video_type_ != videoType) {
        this->video_type_ = videoType;
        //更改分布
        change_video_7(index);
    }
    qDebug()<<"video_type is :"<<video_type_;
}
//显示12视频
template <class T>
void VideoShowWidget<T>::show_video_12()
{
    videoMax = false;
    QString videoType;
    int index = 0;
    videoType = "1_12";

    if (this->video_type_ != videoType) {
        this->video_type_ = videoType;
        change_video_12(index);
    }
}
//隐藏所有
template <class T>
void VideoShowWidget<T>::hide_video_all()
{
    for (int i = 0; i < videoCount; ++i) {
        ui->gridLayout->removeWidget(widgets.at(i));
        widgets.at(i)->setVisible(false);
       // widgets.at(i)->VideoPause();
    }
    qDebug()<<"Hidden All Video";
}
//更改视频函数
//输入视频起始编号，根据行列决定分布
template <class T>
void VideoShowWidget<T>::change_video(int index, int v_row,int v_col)
{
    int count = 0;
    int row = 0;
    int column = 0;
    //videoMax = false;
    for (int i = index; i < videoCount; ++i) {
            ui->gridLayout->addWidget(widgets.at(i), row, column);
            widgets.at(i)->setVisible(true);
            //widgets.at(i)->VideoPlay();//播放视频
            count++;
            column++;
            //到达行界限就开始下一行
            if (column == v_col) {
                row++;
                column = 0;
            }

        if (count == (v_row * v_col)) {
            break;
        }
    }
    emit play_changed(0);
}
//更改显示函数
template <class T>
void VideoShowWidget<T>::change_video_1(int index)
{
    if(index>=0&&index<12)
    {
        hide_video_all();
        videoMax=true;
        ui->gridLayout->addWidget(widgets.at(index),0,0);
        widgets.at(index)->setVisible(true);
    }else {
        qDebug()<<"Please give right input!!!";
    }
    qDebug()<<"col:"<<ui->gridLayout->columnCount();
    qDebug()<<"row:"<<ui->gridLayout->rowCount();
    emit play_changed(0);
}
template <class T>
void VideoShowWidget<T>::change_video_4(int index)
{
    hide_video_all();
    //change_video(index,2,2);//2行2列
    if(index==0){
        ui->gridLayout->addWidget(widgets.at(0),0,0,1,1);
        ui->gridLayout->addWidget(widgets.at(1),0,1,1,1);
        ui->gridLayout->addWidget(widgets.at(2),1,0,1,1);
        ui->gridLayout->addWidget(widgets.at(3),1,1,1,1);
        for (int i = 0; i < 4; ++i) {
            widgets.at(i)->setVisible(true);
        }
    }else if (index==4) {
        ui->gridLayout->addWidget(widgets.at(4),0,0,1,1);
        ui->gridLayout->addWidget(widgets.at(5),0,1,1,1);
        ui->gridLayout->addWidget(widgets.at(6),1,0,1,1);
        ui->gridLayout->addWidget(widgets.at(7),1,1,1,1);
        for (int i = 4; i < 8; ++i) {
            widgets.at(i)->setVisible(true);
        }
    }else if (index==8) {
        ui->gridLayout->addWidget(widgets.at(8),0,0,1,1);
        ui->gridLayout->addWidget(widgets.at(9),0,1,1,1);
        ui->gridLayout->addWidget(widgets.at(10),1,0,1,1);
        ui->gridLayout->addWidget(widgets.at(11),1,1,1,1);
        for (int i = 8; i < 12; ++i) {
            widgets.at(i)->setVisible(true);
        }
    }else {
        qDebug()<<"input error";
    }
    qDebug()<<"col:"<<ui->gridLayout->columnCount();
    qDebug()<<"row:"<<ui->gridLayout->rowCount();
    emit play_changed(0);
}
template <class T>
void VideoShowWidget<T>::change_video_6(int index)
{
    hide_video_all();
    if (index == 0) {
        ui->gridLayout->addWidget(widgets.at(0), 0, 0, 1, 2);
        ui->gridLayout->addWidget(widgets.at(1), 0, 2, 1, 2);
        ui->gridLayout->addWidget(widgets.at(2), 1, 0, 1, 2);
        ui->gridLayout->addWidget(widgets.at(3), 1, 2, 1, 2);
        ui->gridLayout->addWidget(widgets.at(4), 2, 0, 1, 2);
        ui->gridLayout->addWidget(widgets.at(5), 2, 2, 1, 2);

        for (int i = 0; i < 6; ++i) {
            widgets.at(i)->setVisible(true);
        }
    } else if (index == 6) {
        ui->gridLayout->addWidget(widgets.at(6), 0, 0, 1, 2);
        ui->gridLayout->addWidget(widgets.at(7), 0, 2, 1, 2);
        ui->gridLayout->addWidget(widgets.at(8), 1, 0, 1, 2);
        ui->gridLayout->addWidget(widgets.at(9), 1, 2, 1, 2);
        ui->gridLayout->addWidget(widgets.at(10), 2, 0, 1, 2);
        ui->gridLayout->addWidget(widgets.at(11), 2, 2, 1, 2);

        for (int i = 6; i < 12; ++i) {
            widgets.at(i)->setVisible(true);
        }
    }
    //编号11之后的东西--已经注释掉了
//    else if (index == 10) {
//        ui->gridLayout->addWidget(widgets.at(10), 0, 0, 1, 2);
//        ui->gridLayout->addWidget(widgets.at(11), 0, 2, 1, 2);
//        ui->gridLayout->addWidget(widgets.at(12), 1, 0, 1, 2);
//        ui->gridLayout->addWidget(widgets.at(13), 1, 2, 1, 2);
//        ui->gridLayout->addWidget(widgets.at(14), 2, 0, 1, 2);
//        ui->gridLayout->addWidget(widgets.at(15), 2, 2, 1, 2);

//        for (int i = 10; i < 16; ++i) {
//            widgets.at(i)->setVisible(true);
//        }
//    }
    qDebug()<<"col:"<<ui->gridLayout->columnCount();
    qDebug()<<"row:"<<ui->gridLayout->rowCount();
    emit play_changed(0);
}
//显示7视频
template <class T>
void VideoShowWidget<T>::change_video_7(int index)
{
    hide_video_all();
    if(index==0){
        //设置布局
        ui->gridLayout->addWidget(widgets.at(0),0,0,2,3);
        ui->gridLayout->addWidget(widgets.at(1),0,3,1,1);
        ui->gridLayout->addWidget(widgets.at(2),1,3,1,1);
        ui->gridLayout->addWidget(widgets.at(3),2,3,1,1);
        ui->gridLayout->addWidget(widgets.at(4),2,0,1,1);
        ui->gridLayout->addWidget(widgets.at(5),2,1,1,1);
        ui->gridLayout->addWidget(widgets.at(6),2,2,1,1);
        for (int i = 0; i < 7; ++i) {
            widgets.at(i)->setVisible(true);
        }
    }else if(index==5){
        ui->gridLayout->addWidget(widgets.at(5),0,0,2,3);
        ui->gridLayout->addWidget(widgets.at(6),0,3,1,1);
        ui->gridLayout->addWidget(widgets.at(7),1,3,1,1);
        ui->gridLayout->addWidget(widgets.at(8),2,3,1,1);
        ui->gridLayout->addWidget(widgets.at(9),2,0,1,1);
        ui->gridLayout->addWidget(widgets.at(10),2,1,1,1);
        ui->gridLayout->addWidget(widgets.at(11),2,2,1,1);
        for(int i=5;i<12;++i){
            widgets.at(i)->setVisible(true);
        }
    }
    qDebug()<<"col:"<<ui->gridLayout->columnCount();
    qDebug()<<"row:"<<ui->gridLayout->rowCount();
    emit play_changed(0);
}
template <class T>
void VideoShowWidget<T>::change_video_12(int index)
{
    hide_video_all();
    change_video(index,3,4);//三行四列
    qDebug()<<"col:"<<ui->gridLayout->columnCount();
    qDebug()<<"row:"<<ui->gridLayout->rowCount();
    emit play_changed(0);
}

//---------- template realize end ---------

#endif // VIDEOSHOWWIDGET_H
