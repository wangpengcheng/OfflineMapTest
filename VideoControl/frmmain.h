#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QDialog>

class QMenu;
class QLabel;
class QModelIndex;

namespace Ui
{
    class frmMain;
}

class frmMain : public QDialog
{
    Q_OBJECT

public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void change_style();            //切换样式

    void screen_full();             //全屏模式
    void screen_normal();           //普通模式

    void delete_video_one();        //删除当前视频
    void delete_video_all();        //删除所有视频
    void snapshot_video_one();      //截图当前视频
    void snapshot_video_all();      //截图所有视频

    void show_video_1();            //切换到1画面
    void show_video_4();            //切换到4画面
    void show_video_9();            //切换到9画面
    void show_video_16();           //切换到16画面

    void on_btnMenu_Close_clicked();//关闭按钮
    void on_btnMenu_Min_clicked();//最小化按钮
    void on_treeMain_doubleClicked(const QModelIndex &index);

    void on_labStart_linkActivated(const QString &link);

    void on_labConfig_linkActivated(const QString &link);

private:
    Ui::frmMain *ui;    

    QMenu *menuStyle;               //样式菜单
    QMenu *menu;                    //鼠标右键菜单对象
    QLabel *tempLab;                //临时播放视频的标签
    bool video_max;                 //通道是否处于最大化

    QList<QLabel *> VideoLab;       //通道显示视频lab载体
    QList<QLayout *> VideoLay;      //通道视频所在lab的layout

    void InitStyle();               //初始化无边框窗体
    void InitForm();                //初始化窗体数据
    void InitVideo();               //初始化视频布局载体数据
    void LoadVideo();               //加载配置数据
    void LoadNVRIPC();              //加载NVR及IPC数据    

    void removelayout();            //移除所有布局
    void change_video_1(int index); //改变1画面布局
    void change_video_4(int index); //改变4画面布局
    void change_video_9(int index); //改变9画面布局
    void change_video_16(int index);//改变16画面布局

    QString GetNVRID(QString NVRIP);//获取NVR编号

    void ChangeVideoLayout();       //改变通道布局    

    //对应改变通道rtsp地址
    void ChangeRtspAddr(int ch, QString rtspAddr);

    //获取摄像机主码流子码流地址
    void GetRtspAddr(QString NVRID, QString IPCIP,
                     QString &IPCRtspAddrMain, QString &IPCRtspAddrSub);

};

#endif // FRMMAIN_H
