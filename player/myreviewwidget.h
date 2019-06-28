#ifndef MYREVIEWWIDGET_H
#define MYREVIEWWIDGET_H

#include <QWidget>
#include <QQuickWidget>
#include <QVideoWidget>
//使用视频显示窗口
#include "VideoControl/videoshowwidget.h"
#include "VideoControl/qtavvideowidget.h"
class QDeclarativeGeoMap;
class BusLineTest;
class MyReviewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyReviewWidget(QWidget *parent = nullptr);
    //显示存取函数
    inline VideoShowWidget<QtAVVideoWidget>* re_video_show_widgets(){return re_video_show_widgets_;}
    inline QQuickWidget* re_map_show_widget(){return re_map_show_widget_;}
    inline QQuickWidget* re_speed_show_widget(){return re_speed_show_widget_;}
    inline std::shared_ptr<QDeclarativeGeoMap> re_show_map(){return re_show_map_;}
    ~MyReviewWidget();
private:
    //主要视频显示窗口
    VideoShowWidget<QtAVVideoWidget>* re_video_show_widgets_=nullptr;
    //主要地图窗口
    QQuickWidget* re_map_show_widget_=nullptr;
    //主要速度显示
    QQuickWidget* re_speed_show_widget_=nullptr;
    QHBoxLayout* review_layout_=nullptr;//主要布局元素
    //主要地图
    std::shared_ptr<QDeclarativeGeoMap> re_show_map_=nullptr;
    //线路显示指针
    BusLineTest* re_bus_line_test_=nullptr;
};

#endif // MYREVIEWWIDGET_H
