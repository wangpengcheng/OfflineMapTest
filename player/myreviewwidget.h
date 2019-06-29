#ifndef MYREVIEWWIDGET_H
#define MYREVIEWWIDGET_H
/****************************************************************************
** @projectName   OfflineMapTest
** QT Version    5.11.1-5.12.3
** This file is part of the OfflineMapTest project.
** @file          myreviewwidget.h
** @brief         显示窗口回放的关键类
** @details       通过与回放控制类ReviewWidget相关联，可以灵活控制回放显示
** @author        wangpengcheng
** @QQ            673018396
** @email         wangpengcheng2018@gmail.com
** @address       https://github.com/wangpengcheng/OfflineMapTest
** @date          2019-06-29 周六  18:39:05
** @example
**
** 示例代码
**
*****************************************************************************/

#include <QWidget>
#include <QQuickWidget>
#include <QVideoWidget>
#include "VideoControl/videoshowwidget.h"
#include "VideoControl/qtavvideowidget.h"

class QDeclarativeGeoMap;
class BusLineTest;

class MyReviewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyReviewWidget(QWidget *parent = nullptr);
    inline VideoShowWidget<QtAVVideoWidget>* re_video_show_widgets(){return re_video_show_widgets_;}
    inline QQuickWidget* re_map_show_widget(){return re_map_show_widget_;}
    inline QQuickWidget* re_speed_show_widget(){return re_speed_show_widget_;}
    inline std::shared_ptr<QDeclarativeGeoMap> re_show_map(){return re_show_map_;}
    ~MyReviewWidget();
private:
    VideoShowWidget<QtAVVideoWidget>* re_video_show_widgets_=nullptr;       //主要视频显示窗口
    QQuickWidget* re_map_show_widget_=nullptr;                              //主要地图窗口
    QQuickWidget* re_speed_show_widget_=nullptr;                            //主要速度显示，ToDo 与数据库联动，完成后添加到界面上
    QHBoxLayout* review_layout_=nullptr;                                    //主要布局元素
    std::shared_ptr<QDeclarativeGeoMap> re_show_map_=nullptr;               //主要地图
    BusLineTest* re_bus_line_test_=nullptr;                                 //主要地图
};

#endif // MYREVIEWWIDGET_H
