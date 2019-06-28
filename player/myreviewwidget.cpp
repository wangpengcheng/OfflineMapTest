#include "myreviewwidget.h"
#include "src/tool.h"
#include <QtLocation/private/qdeclarativegeomap_p.h>
#include "test/buslinetest.h"
MyReviewWidget::MyReviewWidget(QWidget *parent) :
    QWidget(parent)
{
    //初始化显示函数
    re_video_show_widgets_=new VideoShowWidget<QtAVVideoWidget>();
    //初始化地图窗口
    re_map_show_widget_=new QQuickWidget(QUrl("qrc:/qml/MainShowWindow.qml"));
    re_map_show_widget_->setResizeMode(QQuickWidget::SizeRootObjectToView);
    re_video_show_widgets_->setParent(this);
    re_map_show_widget_->setParent(this);
    review_layout_= new QHBoxLayout(this);
    review_layout_->addWidget(re_video_show_widgets_);
    review_layout_->addWidget(re_map_show_widget_);
    //初始化地图
    re_show_map_=std::shared_ptr<QDeclarativeGeoMap>(re_map_show_widget_->rootObject()->findChild<QDeclarativeGeoMap *>("show_map"));
    //初始化地图线路
    if(re_show_map_!=nullptr)
    {
        re_bus_line_test_=new BusLineTest();
        //准备数据
        //TODO: 这里只是为了简便实用，建议动态创建线路
        re_bus_line_test_->MainTest();
        re_bus_line_test_->ShowTest(re_show_map_.get());
    }
}

MyReviewWidget::~MyReviewWidget()
{
    DELETE_QOBJECT(re_video_show_widgets_);
    DELETE_QOBJECT(re_map_show_widget_);
    DELETE_QOBJECT(re_speed_show_widget_);
    DELETE_OBJECT(re_bus_line_test_);
}



