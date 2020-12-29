/**
 * @file mainshowdialog.h
 * @brief 监控界面主要显示类 
 * @details 监控界面主要显示类  \n
 * QT Version    5.12.2
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2020-12-29 00:09:33
 * @copyright Copyright (c) 2020  IRLSCU
 * 
 * @par 修改日志:
 * <table>
 * <tr>
 *    <th> Commit date</th>
 *    <th> Version </th> 
 *    <th> Author </th>  
 *    <th> Description </th>
 * <tr>
 *    <td> 2020-12-29 00:09:33 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 添加注释文档 </td>
 * </tr>
 * </table>
 */
#ifndef MAINSHOWDIALOG_H
#define MAINSHOWDIALOG_H
#include "VideoPlayer/videoshowwidget.h"
#include "MainWindows/myreviewwidget.h"

#include <QDialog>
#include <QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QQuickWidget>
#include <QQuickView>
#include <QVBoxLayout>
#include <QSharedPointer>
#include <QComboBox>
#include <iostream>
#include <memory>
//地图插件私有地图类
#include <QtLocation/private/qdeclarativegeomap_p.h>
#include <QVideoWidget>

namespace Ui
{
    class MainShowDialog;
}
/**
 * @brief QUi的基本窗口类，主要是显示窗口
 * @bug MainShowDialog::on_show_tab_choose_currentChanged 从地图页与视频监控页切换时 \n
 * 存在显示的bug,视频显示的窗口布局会发生错乱 ，但是点击放大按钮刷新之后，布局恢复正常， \n
 * 疑似QML兼容 bug 暂时不清楚原因；
 */
class MainShowDialog : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new Main Show Dialog object
     * @param  parent           父类指针
     */
    explicit MainShowDialog(QWidget *parent = nullptr);
    ~MainShowDialog();
    //变量初始化
    void InitStackWidget();
    /**
     * @brief  获取qmlwidget对象，主要是地图qml窗口
     * @return QQuickWidget* 地图界面指针
     */
    inline QQuickWidget *map_page() { return map_page_; }
    /**
     * @brief  获取视频显示界面的QWidget*  指针
     * @return QWidget*  窗口指针
     */
    inline QWidget *video_page() { return video_page_; }
    /**
     * @brief  获取切换指针
     * @return QStackedWidget* 
     */
    inline QStackedWidget *stacked_widget() { return stacked_widget_; }
    /**
     * @brief 多视频显示窗口类，主要是布局模板
     * @return VideoShowWidget<StreamVideoWidget>* 
     */
    inline VideoShowWidget<StreamVideoWidget> *video_widget() { return video_widget_; }
    /**
     * @brief qml Map中的地图对象指针，通过Qml的object查找进行获取
     * @return std::shared_ptr<QDeclarativeGeoMap> 地图查找共享指针
     */
    inline std::shared_ptr<QDeclarativeGeoMap> show_map() { return show_map_; }
    /**
     * @brief 视频回放窗口指针，主要用来查看历史记录
     * @return MyReviewWidget* 数据回放历史指针
     */
    inline MyReviewWidget *review_widget() { return review_widget_; }
    /**
     * @brief 回放时的地图QML对象
     * @note 为了在演示和回访时，两者互不干扰，因此新建了一个回放对象；和实时监控独立
     * @return std::shared_ptr<QDeclarativeGeoMap> 
     */
    inline std::shared_ptr<QDeclarativeGeoMap> re_show_map() { return review_widget_->re_show_map(); }
private slots:
    /**
     * @brief  槽函数--根据模式按钮，来进行不同的页面切换
     * @param  arg1             制定的切换index
     * @bug MainShowDialog::on_show_tab_choose_currentChanged 从地图页与视频监控页切换时 \n
     * 存在显示的bug,视频显示的窗口布局会发生错乱 ，但是点击放大按钮刷新之后，布局恢复正常， \n
     * 疑似QML兼容 bug 暂时不清楚原因；
     */
    void on_show_tab_choose_currentChanged(int arg1);
    /**
     * @brief 打印顺序信息
     * @param index
     */
    void print_layout(int index);

private:
    Ui::MainShowDialog *ui;                                      ///< Ui数据指针类
    QStackedWidget *stacked_widget_ = nullptr;                   ///< 中间间隔类
    QQuickWidget *map_page_ = nullptr;                           ///< qml地图
    QWidget *video_page_ = nullptr;                              ///< 自定义视频展示页
    VideoShowWidget<StreamVideoWidget> *video_widget_ = nullptr; ///< 自定义视频展示widget
    QVBoxLayout *map_show_vbox_layout_ = nullptr;                ///< 地图水平布局
    QHBoxLayout *video_show_vbox_layout_ = nullptr;              ///< 视频水平布局
    std::shared_ptr<QDeclarativeGeoMap> show_map_ = nullptr;     ///< 地图指针方便获取地图
    QWidget *aggregative_show_page_ = nullptr;                   ///< 综合模式新的page;
    QGridLayout *aggregative_gridLayout_ = nullptr;              ///< 综合模式的布局，方便设置
    QQuickWidget *speed_show_chart_widget_ = nullptr;            ///< 仪表盘数据指针，/*ToDo 单独构造它的类，方便复用 */
    QHBoxLayout *video_review_layout_ = nullptr;                 ///< 设置视频回放布局
    MyReviewWidget *review_widget_ = nullptr;                    ///< 回放界面
};

#endif // MAINSHOWDIALOG_H
