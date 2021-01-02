/**
 * @file myreviewwidget.h
 * @brief 显示窗口回放的关键类 
 * @details 通过与回放控制类ReviewWidget相关联，可以灵活控制回放显示 \n
 * QT Version    5.11.1-5.12.3
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2020-12-29 01:18:50
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
 *    <td> 2019-06-29 周六  18:39:05 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 完成基本功能 </td>
 * </tr>
 * <tr>
 *    <td> 2020-12-29 01:18:50 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td>内容</td>
 * </tr>
 * </table>
 */
#ifndef MYREVIEWWIDGET_H
#define MYREVIEWWIDGET_H
#include "VideoPlayer/videoshowwidget.h"
#include "VideoPlayer/qtavvideowidget.h"


#include <QWidget>
#include <QQuickWidget>
#include <QVideoWidget>

class QDeclarativeGeoMap;
class BusLineTest;
/**
 * @brief 视频回放关键类
 * @details 通过与回放控制类 ReviewWidget 相关联，可以灵活控制回放显示 \n
 * 主要是综合模式下的地图显示和仪表盘显示
 * @todo 将成员成员变量指针，都修改为智能指针
 */
class MyReviewWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new My Review Widget object
     * @param  parent          父类指针
     */
    explicit MyReviewWidget(QWidget *parent = nullptr);
    /**
     * @brief  查看视频显示类指针
     * @return VideoShowWidget<QtAVVideoWidget>* QtAV视频显示图像列表
     */
    inline VideoShowWidget<QtAVVideoWidget>* re_video_show_widgets(){return re_video_show_widgets_;}
    /**
     * @brief  综合模式地图显示对象父指针
     * @note 它和监看模式使用的是同一个指针
     * @return QQuickWidget* QML中的QMap地图父指针
     */
    inline QQuickWidget* re_map_show_widget(){return re_map_show_widget_;}
    /**
     * @brief 获取QML中的地图数据显示指针，方便显示和控制
     * @return QQuickWidget* QML的仪表盘数据显示指针
     */
    inline QQuickWidget* re_speed_show_widget(){return re_speed_show_widget_;}
    /**
     * @brief 综合模式地图显示对象指针
     * @note 它和监看模式使用的是同一个指针
     * @return std::shared_ptr<QDeclarativeGeoMap> QML中的QMap地图指针 
     */
    inline std::shared_ptr<QDeclarativeGeoMap> re_show_map(){return re_show_map_;}
    ~MyReviewWidget();
private:
    VideoShowWidget<QtAVVideoWidget>* re_video_show_widgets_=nullptr;       ///< 主要视频显示窗口
    QQuickWidget* re_map_show_widget_=nullptr;                              ///< 主要地图窗口
    QQuickWidget* re_speed_show_widget_=nullptr;                            ///< 主要速度显示，ToDo 与数据库联动，完成后添加到界面上
    QHBoxLayout* review_layout_=nullptr;                                    ///< 主要布局元素
    std::shared_ptr<QDeclarativeGeoMap> re_show_map_=nullptr;               ///< 主要地图
    BusLineTest* re_bus_line_test_=nullptr;                                 ///< 主要地图
};

#endif // MYREVIEWWIDGET_H
