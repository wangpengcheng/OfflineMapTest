/**
 * @file videoshowwidget.h
 * @brief 视频显示控制模板类，主要是公共布局函数的变化
 * @details 因为直播实时视频类和回放中的播放视频类在布局上存在相同的布局操作； \n
 *  代码冗余，因此将其公共部分使用模板方式进行抽象，VideoShowWidgetBase 为接口类 \n
 *  再通过 VideoShowWidget 定义模板类，定义布局切换时的相关槽函数 \n
 * QT Version 5.11.1-5.12.3
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2020-12-29 21:51:10
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
 *    <td> 2020-12-29 21:51:10 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td>内容</td>
 * </tr>
 * </table>
 */
#ifndef VIDEOSHOWWIDGET_H
#define VIDEOSHOWWIDGET_H

#include <QWidget>
#include <QMenu>
#include <QTimer>

//模板类
#include "videoshowwidget.h"
#include "ui_videoshowwidget.h"
#include "myvideowidget.h"
#include "MapItems/tool.h"
#include "streamvideowidget.h"

namespace Ui
{
    class VideoShowWidget;
}
/**
 * @brief 基础类，定义相关接口
 * @details 主要是定义信号函数和槽函数，主要定义了1、4、6、7、12共计5种布局模式
 */
class VideoShowWidgetBase : public QWidget
{
    Q_OBJECT
public:
    explicit VideoShowWidgetBase(QWidget *parent = nullptr) : QWidget(parent) {}
    //公共槽函数
public slots:
    /**
     * @brief 表单初始化接口
     */
    virtual void initForm() = 0;
    /**
     * @brief 右键复选框初始化接口
     */
    virtual void initMenu() = 0;
    /**
     * @brief 当前窗口截图
     * @todo 实现保存当前界面图片
     */
    virtual void snapshot_video_one() = 0;
    /**
     * @brief 所有窗口截图
     * @todo 实现保存所有窗口图片
     */
    virtual void snapshot_video_all() = 0;
    /**
     * @brief 显示所有画面界面
     */
    virtual void show_video_all() = 0;
    /**
     * @brief 显示1画面
     */
    virtual void show_video_1() = 0;
    /**
     * @brief 显示4画面
     */
    virtual void show_video_4() = 0;
    /**
     * @brief 显示6画面
     */
    virtual void show_video_6() = 0;
    /**
     * @brief 显示7画面
     */
    virtual void show_video_7() = 0;
    /**
     * @brief 显示12画面
     */
    virtual void show_video_12() = 0;
    /**
     * @brief 隐藏所有画面
     */
    virtual void hide_video_all() = 0;
    /**
     * @brief 窗口当前所在位置，将其放到目标行列中
     * @param  index            画面索引
     * @param  v_row            目标行
     * @param  col              目标列
     */
    virtual void change_video(int index, int v_row, int col) = 0;
    /**
     * @brief 1视频改变
     * @param  index            视频编号索引
     */
    virtual void change_video_1(int index) = 0;
    /**
     * @brief 4视频改变
     * @param  index            视频编号索引
     */
    virtual void change_video_4(int index) = 0;
    /**
     * @brief 6视频改变
     * @param  index            视频编号索引
     */
    virtual void change_video_6(int index) = 0;
    /**
     * @brief 7视频改变
     * @param  index            视频编号索引
     */
    virtual void change_video_7(int index) = 0;
    /**
     * @brief 12视频改变
     * @param  index            视频编号索引
     */
    virtual void change_video_12(int index) = 0;

signals:
    /**
     * @brief 播放状态更改函数
     * @param  index          对应的index
     */
    void play_changed(int index);
    /**
     * @brief  改变1画面布局 信号
     * @param  index            选中对应的index
     */
    void signal_change_video_1(int index);
    /**
     * @brief  改变4画面布局 信号
     * @param  index            选中对应的index
     */
    void signal_change_video_4(int index);
    /**
     * @brief  改变6画面布局 信号
     * @param  index            选中对应的index
     */
    void signal_change_video_6(int index);
    /**
     * @brief  改变7画面布局 信号
     * @param  index            选中对应的index
     */
    void signal_change_video_7(int index);
    /**
     * @brief  改变12画面布局 信号
     * @param  index            选中对应的index
     */
    void signal_change_video_12(int index);
};

//---------- template define start ---------
/**
 * @brief  模板实现类
 * @tparam T 对应的模板
 */
template <class T>
class VideoShowWidget : public VideoShowWidgetBase
{

public:
    /**
     * @brief 基础构造函数,默认为四画面格式
     * @param  parent           父数据指针
     */
    explicit VideoShowWidget(QWidget *parent = nullptr);
    ~VideoShowWidget();
    /**
     * @brief 获取鼠标右键时的选择框
     * @return QMenu* 选框指针
     */
    inline QMenu *VideoMenu() { return videoMenu; }
    /**
     * @brief 获取视频对应widget 列表
     * @return QList<T *> 视频指针列表
     */
    inline QList<T *> video_widgets() { return widgets; }
    /**
     * @brief  当前是否处于视频最大化模式
     * @return true  处于
     * @return false 不处于
     */
    inline bool is_videomax() { return videoMax; }
    /**
     * @brief 视频数量
     * @return int 数量
     */
    inline int video_count() { return videoCount; }

protected:
    /**
     * @brief 保护函数，设置键盘监听
     * @param  watched          监听对象
     * @param  event            监听事件
     * @return true             成功
     * @return false            失败
     */
    bool eventFilter(QObject *watched, QEvent *event);

public:
    /** 重载的槽函数列表，详见  VideoShowWidgetBase */
    void initForm();
    void initMenu();
    void snapshot_video_one();
    void snapshot_video_all();
    void show_video_all();
    void show_video_1();
    void show_video_4();
    void show_video_6();
    void show_video_7();
    void show_video_12();
    void hide_video_all();
    void change_video(int index, int v_row, int col);
    void change_video_1(int index);
    void change_video_4(int index);
    void change_video_6(int index);
    void change_video_7(int index);
    void change_video_12(int index);

private:
    Ui::VideoShowWidget *ui;    ///< qt ui中对应的UI类
    bool videoMax;              ///< 是否处于最大化模式
    int videoCount;             ///< 视频数量
    QString video_type_;        ///< 视频类型
    QMenu *videoMenu = nullptr; ///< 右键选项
    QList<T *> widgets;         ///< 播放窗口队列
};
//---------- template define end ---------

// 模板函数实现
#include "videoshowwidget.cpp"

#endif // VIDEOSHOWWIDGET_H
