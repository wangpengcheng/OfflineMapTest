#include "mainshowdialog.h"
#include "ui_mainshowdialog.h"
MainShowDialog::MainShowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainShowDialog)
{
    ui->setupUi(this);
    //设置窗口模式为Window窗口模式
    //设置模式，显示最大，最小按钮
    this->setModal(Qt::Widget);
    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowMinMaxButtonsHint;
    flags |= Qt::WindowCloseButtonHint;
    this->setWindowFlags(flags);
    InitStackWidget();
    ui->show_tab_choose->setCurrentIndex(0);


}

MainShowDialog::~MainShowDialog()
{
    delete ui;
    if(stacked_widget_!=nullptr){
        delete [] stacked_widget_;
    }
    if(map_page_!=nullptr){
        delete [] map_page_;
    }
//    if(video_page_!=nullptr){
//        delete [] video_page_;
//    }
    if(map_show_vbox_layout_!=nullptr){
        delete [] map_show_vbox_layout_;
    }
    if(video_show_vbox_layout_!=nullptr){
        delete [] video_show_vbox_layout_;
    }
    if(aggregative_gridLayout_!=nullptr){
        delete [] aggregative_gridLayout_;
    }
    if(speed_show_chart_widget_!=nullptr){
        delete [] speed_show_chart_widget_;
    }
}
void MainShowDialog::InitStackWidget()
{
    this->stacked_widget_=ui->show_tab_choose;
    //创建地图
    QQuickView *map_page_view=new QQuickView();
    map_page_view->setSource(QUrl("qrc:/qml/MainShowWindow.qml"));
    map_page_view->setResizeMode(QQuickView::SizeRootObjectToView);
    //获取地图参数
    show_map_=std::shared_ptr<QDeclarativeGeoMap>(map_page_view->rootObject()->findChild<QDeclarativeGeoMap *>("show_map"));
    map_page_=QWidget::createWindowContainer(map_page_view);
    //创建地图布局
    map_show_vbox_layout_=new QVBoxLayout(ui->map_show_page);
    map_show_vbox_layout_->setMargin(0);//设置边距
    map_show_vbox_layout_->addWidget(map_page_);//添加到布局中
    //创建video_page_
    //创建video_page布局
    video_widget_=new VideoShowWidget();
    video_show_vbox_layout_=new QVBoxLayout(ui->video_show_page);
    video_show_vbox_layout_->setMargin(2);
    video_widget_->change_video_4(0);
    video_show_vbox_layout_->addWidget(ui->widget_main);
    video_page_=ui->widget_main;
    ui->horizontalLayout_3->addWidget(video_widget_);

//    ui->video_show_page=video_page_;
//    ui->show_tab_choose->addWidget(video_page_);
    aggregative_gridLayout_=new QGridLayout(ui->aggregative_show_page);

    //设置仪表盘面板
    speed_show_chart_widget_=new QQuickWidget();
    speed_show_chart_widget_->setResizeMode(QQuickWidget::SizeRootObjectToView);
    speed_show_chart_widget_->setSource(QUrl("qrc:/qml/MyCharts.qml"));
}

void MainShowDialog::on_show_tab_choose_currentChanged(int arg1)
{
    if(arg1==2){
        aggregative_gridLayout_->removeWidget(speed_show_chart_widget_);
        //综合页面进行布局
        aggregative_gridLayout_->addWidget(video_page_,0,0,2,2);
        aggregative_gridLayout_->addWidget(map_page_,0,2,3,2);
        aggregative_gridLayout_->addWidget(speed_show_chart_widget_,2,0,1,2);
    }else if (arg1==0) {
        map_show_vbox_layout_->addWidget(map_page_);
    }else if (arg1==1) {
        video_show_vbox_layout_->addWidget(video_page_);
    }
    qDebug()<<"This current is "+arg1;
}
