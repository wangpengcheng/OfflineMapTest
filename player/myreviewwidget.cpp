#include "myreviewwidget.h"
#include "src/tool.h"
#include <QtLocation/private/qdeclarativegeomap_p.h>
#include "test/buslinetest.h"
MyReviewWidget::MyReviewWidget(QWidget *parent) :
    QWidget(parent)
{
    //初始化显示函数
    re_video_show_widgets_=new VideoShowWidget<MyVideoWidget>();
    //初始化地图窗口
    re_map_show_widget_=new QQuickWidget(QUrl("qrc:/qml/MainShowWindow.qml"));
    re_map_show_widget_->setResizeMode(QQuickWidget::SizeRootObjectToView);
    re_video_show_widgets_->setParent(this);
    re_map_show_widget_->setParent(this);
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
    this->resize(800,600);
    //初始化布局选项
    UpDateLayOut();
}

MyReviewWidget::~MyReviewWidget()
{
    DELETE_QOBJECT(re_video_show_widgets_);
    DELETE_QOBJECT(re_map_show_widget_);
    DELETE_QOBJECT(re_speed_show_widget_);
    DELETE_OBJECT(re_bus_line_test_);
}

void MyReviewWidget::UpDateLayOut()
{
    if(re_map_show_widget_!=nullptr&&
       re_map_show_widget_->parentWidget()!=nullptr){
        //设置布局
        re_map_show_widget_->setGeometry(re_map_show_widget_->parentWidget()->x()+re_map_show_widget_->parentWidget()->width()/2,
                                         re_map_show_widget_->parentWidget()->y(),
                                         re_map_show_widget_->parentWidget()->width()/2,
                                         re_map_show_widget_->parentWidget()->height());
    }else{
        qDebug()<<"re_map_show_widget_ is empty or haven't parent";
    }
    if(re_video_show_widgets_!=nullptr&&
       re_video_show_widgets_->parentWidget()!=nullptr){
       //设置布局
        re_video_show_widgets_->setGeometry(this->geometry().x(),
                                            this->y(),
                                            this->width()/2,
                                            this->height());
    }
}
void MyReviewWidget::resizeEvent(QResizeEvent* event){
    QWidget::resizeEvent(event);
    UpDateLayOut();
}

