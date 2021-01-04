/**
 * @file frmmain.h
 * @brief frmMain 主界面实现类
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2020-12-30 00:41:28
 * @copyright Copyright (c) 2020  IRLSCU
 * 
 * @par 修改日志:
 * <table>
 * <tr>
 *    <th> Commit date</th>
 *    <th> Version </th> 
 *    <th> Author </th>  
 *    <th> Description </th>
 * </tr>
 * <tr>
 *    <td> 2020-12-30 00:41:28 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 添加文档 </td>
 * </tr>
 * </table>
 */
#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QDialog>
#include <iostream>
#include <memory>
#include <QtLocation/private/qdeclarativegeomap_p.h>
#include <QQuickWidget>
#include <QGridLayout>
#include <QQuickView>
#include <QSharedPointer>
#include <QMap>
class QMenu;
class QLabel;
class QModelIndex;
class MainShowDialog;
class MapContrlConnect;
class VideoDecodeThread;
class BusTest;
class BusLineTest;
class Player;
class Bus;
class ReviewWidget;
namespace Ui
{
    class frmMain;
}
/**
 * @brief 应用主要界面类，超级复杂
 * @todo 
 * - 代码重构，将其中的重复布局类使用 VideoShowWidget 模板类进行重构
 * - 代码业务过重，需要解耦，将数据库前后端访问的功能进行剥离
 */
class frmMain : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief frmMain 基础构造函数
     * @param parent 父指针
     */
    explicit frmMain(QWidget *parent = 0);
    /**
     * @brief 析构函数
     */
    ~frmMain();
    /**
     * @brief 返回控制地图
     * @return 控制地图指针
     */
    inline std::shared_ptr<QDeclarativeGeoMap> control_map() { return control_map_; }
    /**
     * @brief 回放控制类
     * @return 回放控制类指针
     */
    inline ReviewWidget *video_review_control() { return review_control_; }
    //------- 数据存储相关函数 start ------

    /**
     * @brief 是否存储数据，ture就会将数据添加到数据库中
     * @return true 存储
     * @return false 不存储
     */
    inline bool is_save_data() { return is_save_data_; }
    /**
     * @brief 是否存储数据，ture就会将数据添加到数据库中
     * @param  is_save          是否存储数据
     */
    inline void set_ia_save_data(bool is_save) { is_save_data_ = is_save; }
    /**
     * @brief  开始存储记录编号
     * @return int 记录编号
     */
    inline int save_record_id() { return save_record_id_; }
    /**
     * @brief 创建记录函数，返回mysql中的记录编号
     * @return int 当前记录编号
     */
    int CreateRecord();
    //------- 数据存储相关函数 end ------
    //数据记录的相关信号
public slots:
    /**
     * @brief 开始记录数据
     */
    void StartSaveData();
    /**
     * @brief 停止记录数据
     */
    void StopSaveData();
    /**
     * @brief 子树的右键槽
     * @param  point     位置信息
     */
    void showrightMenu(QPoint point);
    //------- 解码线程相关槽函数 start ------
    //    void decode_thead_stop(QString thread_key);//停止解码
    //    void decode_thead_start(QString thread_key);//开始解码
    //    void decode_thead_restart(QString thread_key);//重新开始解码
    //    void decode_thead_destory(QString thread_key);//销毁线程
    //------- 解码线程相关槽函数 end ------

    //记录的关键信号
signals:
    void signal_send_record_id(int record_id); //发送record_id的信号
    void signal_send_stop();                   //发送停止信号
    void signal_change_video_1(int index);     //改变1画面布局
    void signal_change_video_4(int index);     //改变4画面布局
    void signal_change_video_6(int index);     //改变6画面布局
    void signal_change_video_7(int index);     //改变7画面布局
    void signal_change_video_12(int index);    //改变12画面布局
protected:
    /**
     * @brief  对象事件适配器，主要用来进行复杂的逻辑操作
     * @param  obj              操作对象
     * @param  event            发生事件
     * @return true             处理成功
     * @return false            处理失败
     */
    bool eventFilter(QObject *obj, QEvent *event);
    /**
     * @brief  监听键盘事件
     * @param  event   获取键盘事件        
     */
    void keyPressEvent(QKeyEvent *event);
private slots:
    /**
     * @brief 切换样式
     */
    void change_style();
    /**
     * @brief 全屏模式
     */
    void screen_full();
    /**
     * @brief 普通模式
     */
    void screen_normal();
    /**
     * @brief 截图当前视频
     * @todo 实现该功能
     */
    void snapshot_video_one();
    /**
     * @brief 截图所有视频
     * @todo 实现该功能
     */
    void snapshot_video_all();
    /**
     * @brief 切换到1画面
     */
    void show_video_1();
    /**
     * @brief 切换到4画面
     */
    void show_video_4();
    /**
     * @brief 切换到6画面
     */
    void show_video_6();
    /**
     * @brief 切换到7画面
     */
    void show_video_7();
    /**
     * @brief 切换到16画面
     */
    void show_video_12();
    /**
     * @brief 关闭按钮
     */
    void on_btnMenu_Close_clicked();
    /**
     * @brief 最小化按钮
     */
    void on_btnMenu_Min_clicked();
    /**
     * @brief 回放树节点点击节点响应
     * @param  index           节点索引
     */
    void on_treeMain_doubleClicked(const QModelIndex &index);
    /**
     * @brief 开始轮询按钮。无操作
     * @param  link             地址连接
     */
    void on_labStart_linkActivated(const QString &link);
    /**
     * @brief 开始配置按钮，无实际操作
     * @param  link             地址连接
     */
    void on_labConfig_linkActivated(const QString &link);
    /**
     * @brief  控制界面。标签切换页槽函数
     * @param  index    当前切换标签索引
     */
    void on_tab_choose_currentChanged(int index);

    void on_pushButton_clicked();
    /**
     * @brief 记录数据按钮，响应函数
     */
    void on_save_data_button_clicked();
    /**
     * @brief  回放连接更改函数，主要用于修改已经建立连接的解码视频和显示界面
     * @param  av_player_index  播放器编号
     * @param  show_widget_index 显示界面编号
     */
    void review_player_connect_changed(const int av_player_index, const int show_widget_index);
    /**
     * @brief  回放标签，更改事件；主要用于修改标题。
     * @param  label_id         当前label的id编号
     */
    void re_label_changed(QString label_id);

private:
    Ui::frmMain *ui; ///< ui对象指针
    /*视频控制模块变量 start*/
    QMenu *menuStyle = nullptr;                                    ///< 样式菜单
    QMenu *menu = nullptr;                                         ///< 鼠标右键菜单对象
    QMenu *thread_menu = nullptr;                                  ///< 线程管理的右键菜单
    QMenu *menu8 = nullptr;                                        ///< 视频控制临时按钮
    QLabel *tempLab;                                               ///< 临时播放视频的标签
    bool video_max_;                                               ///< 通道是否处于最大化
    QString video_type_;                                           ///< 当前video的type值
    int video_count_;                                              ///< 视频总数
    QList<QLabel *> video_labs_;                                   ///< 通道显示视频lab载体
    QMap<QString, QSharedPointer<VideoDecodeThread>> decode_list_; ///< 解码线程映射表

    QVBoxLayout *video_vbox_layout_ = nullptr; ///< 视频布局元素
    QWidget *video_control_widget_ = nullptr;  ///< 视频控制页面的widget
    /*视频控制模块变量 end*/

    /*地图控制模块变量 start*/
    QWidget *map_control_widget_ = nullptr;                     ///< 地图控制widget
    QQuickView *map_control_view_ = nullptr;                    ///< qml地图控制bug不得已而为之
    QVBoxLayout *map_vbox_layout_ = nullptr;                    ///< 地图分配指针
    std::shared_ptr<QDeclarativeGeoMap> control_map_ = nullptr; ///< 控制地图显示
    BusTest *bus_test_ = nullptr;                               ///< bus测试对象，实现路书
    BusLineTest *bus_line_test_ = nullptr;                      ///< bus_line测试，实现路书
    /*地图控制模块变量 end*/

    /*综合显示模块变量 start*/
    QGridLayout *aggregative_gridLayout_ = nullptr; ///< 综合模式网格布局
    QQuickWidget *speed_chart_widget_ = nullptr;    ///< 数据显示模块
    /*综合显示模块变量 end*/
    //显示窗口
    MainShowDialog *show_dialog_ = nullptr;   ///< 主要显示窗口
    MapContrlConnect *map_connect_ = nullptr; ///< 主要地图连接类

    /* 回放控制 start */
    QVBoxLayout *video_review_layout_ = nullptr;     ///< 回放布局指针
    ReviewWidget *review_control_ = nullptr;         ///< 回放控制对象
    Bus *review_bus_ = nullptr;                      ///< 回放的车辆
    MapContrlConnect *review_map_connect_ = nullptr; ///< 回放地图控制链接
    /* 回放控制 end */
    //------ 存储数据相关变量 start -----
    bool is_save_data_ = false; ///< 是否需要存储数据
    int save_record_id_ = NULL; ///< 记录当前正在存储的记录编号
    //------ 存储数据相关变量 end -----

    /**
     * @brief 初始化无边框窗体
     */
    void InitStyle();
    /**
     * @brief 初始化窗体数据
     */
    void InitForm();
    /**
     * @brief 初始化右侧按钮
     */
    void InitMenu();
    /**
     * @brief 初始化视频布局载体数据
     */
    void InitVideo();
    /**
     * @brief 初始化TabWidget布局
     */
    void InitTabWidget();
    /**
     * @brief 初始化显示窗口
     */
    void InitShowDialog();
    /**
     * @brief 加载视频配置数据
     */
    void LoadVideo();
    /**
     * @brief 加载NVR及IPC数据
     */
    void LoadNVRIPC();
    /**
     * @brief 移除所有布局
     */
    void removelayout();
    /**
     * @brief 改变1画面布局
     * @param index 选中对应的index
     */
    void change_video_1(int index);
    /**
     * @brief  改变4画面布局 信号
     * @param  index            选中对应的index
     */
    void change_video_4(int index);
    /**
     * @brief  改变6画面布局 信号
     * @param  index            选中对应的index
     */
    void change_video_6(int index);
    /**
     * @brief  改变7画面布局 信号
     * @param  index            选中对应的index
     */
    void change_video_7(int index);
    /**
     * @brief  改变12画面布局 信号
     * @param  index            选中对应的index
     */
    void change_video_12();
signals:

public:
    /**
     * @brief change_video 更改布局函数
     * @param index
     * @param v_row
     * @param col
     */
    void change_video(int index, int v_row, int col);
    /**
     * @brief GetNVRID 获取NVR编号
     * @param NVRIP
     * @return 对应的编号名称
     */
    QString GetNVRID(QString NVRIP);
    /**
     * @brief 改变通道布局
     */
    void ChangeVideoLayout();
    /**
     * @brief 对应改变通道rtsp地址
     * @param 编号索引
     * @param rtsp地址
     */
    void ChangeRtspAddr(int ch,
                        QString rtspAddr);

    /**
     * @brief 获取摄像机主码流子码流地址
     * @param NVRID NVR编号
     * @param IPCIP IPC对应Ip
     * @param IPCRtspAddrMain 主码流地址
     * @param IPCRtspAddrSub  子码流地址
     */
    void GetRtspAddr(QString NVRID,
                     QString IPCIP,
                     QString &IPCRtspAddrMain,
                     QString &IPCRtspAddrSub);
};

#endif // FRMMAIN_H
