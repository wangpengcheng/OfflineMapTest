#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QDialog>
#include <iostream>
#include <memory>
#include <QtLocation/private/qdeclarativegeomap_p.h>
#include <QQuickWidget>
#include <QGridLayout>
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
    //返回控制地图
    inline std::shared_ptr<QDeclarativeGeoMap> control_map(){return control_map_;}

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
    void show_video_6();            //切换到6画面
    void show_video_7();            //切换到7画面
    void show_video_12();           //切换到16画面

    void on_btnMenu_Close_clicked();//关闭按钮
    void on_btnMenu_Min_clicked();//最小化按钮
    void on_treeMain_doubleClicked(const QModelIndex &index);

    void on_labStart_linkActivated(const QString &link);

    void on_labConfig_linkActivated(const QString &link);

    void on_tab_choose_currentChanged(int index);

private:
    Ui::frmMain *ui;    
    /*视频控制模块变量 start*/
    QMenu *menuStyle=nullptr;               //样式菜单
    QMenu *menu=nullptr;                    //鼠标右键菜单对象
    QLabel *tempLab;                //临时播放视频的标签
    bool video_max_;                //通道是否处于最大化
    QString video_type_;            //当前video的type值
    int video_count_;               //视频总数
    QList<QLabel *> video_labs_;    //通道显示视频lab载体
    QVBoxLayout* video_vbox_layout_=nullptr; //视频布局元素
    QWidget* video_control_widget_=nullptr; //视频控制页面的widget
    /*视频控制模块变量 end*/
    /*地图控制模块变量 start*/
    QQuickWidget* map_control_widget_=nullptr; //地图控制widget
    QVBoxLayout* map_vbox_layout_=nullptr; //地图分配指针
    std::shared_ptr<QDeclarativeGeoMap> control_map_=nullptr; //控制地图显示
    /*地图控制模块变量 end*/
    /*综合显示模块变量 start*/
    QGridLayout* aggregative_gridLayout_=nullptr; //综合模式网格布局
    QQuickWidget* speed_chart_widget_=nullptr; //数据显示模块
    /*综合显示模块变量 end*/
    /*数据显示窗口*/


    void InitStyle();               //初始化无边框窗体
    void InitForm();                //初始化窗体数据
    void InitMenu();                //初始化右侧按钮
    void InitVideo();               //初始化视频布局载体数据
    void InitTabWidget();           //初始化TabWidget布局
    void LoadVideo();               //加载配置数据
    void LoadNVRIPC();              //加载NVR及IPC数据    

    void removelayout();            //移除所有布局
    void change_video_1(int index); //改变1画面布局
    void change_video_4(int index); //改变4画面布局
    void change_video_6(int index); //改变6画面布局
    void change_video_7(int index); //改变7画面布局
    void change_video_12();         //改变12画面布局
    void change_video(int index, int v_row,int col); //更改布局
    QString GetNVRID(QString NVRIP);//获取NVR编号

    void ChangeVideoLayout();       //改变通道布局    

    //对应改变通道rtsp地址
    void ChangeRtspAddr(int ch, QString rtspAddr);

    //获取摄像机主码流子码流地址
    void GetRtspAddr(QString NVRID, QString IPCIP,
                     QString &IPCRtspAddrMain, QString &IPCRtspAddrSub);

};

#endif // FRMMAIN_H
