#include "mainshowdialog.h"
#include "ui_mainshowdialog.h"
#include <QTimeLine>
MainShowDialog::MainShowDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainShowDialog)
{
    ui->setupUi(this);
    //设置窗口模式为Window窗口模式
    //设置模式，显示最大，最小按钮
//    this->setModal(Qt::Widget);
//    Qt::WindowFlags flags = Qt::Dialog;
//    flags |= Qt::WindowMinMaxButtonsHint;
//    flags |= Qt::WindowCloseButtonHint;
//    this->setWindowFlags(flags);
    //初始化选项框
    InitStackWidget();
    on_show_tab_choose_currentChanged(2);
    ui->show_tab_choose->setCurrentIndex(2);
    connect(this->video_widget_,SIGNAL(play_changed(int)),this,SLOT(print_layout(int)));

}

MainShowDialog::~MainShowDialog()
{
    delete ui;
    if(stacked_widget_!=nullptr){
        delete [] stacked_widget_;
        stacked_widget_=nullptr;
    }
//    if(map_page_!=nullptr){
//        delete [] map_page_;
//        map_page_=nullptr;
//    }
//    if(video_page_!=nullptr){
//        delete [] video_page_;
//    }
//    if(video_widget_!=nullptr){
//        delete [] video_widget_;
//        video_widget_=nullptr;
//    }
    if(map_show_vbox_layout_!=nullptr){
        delete [] map_show_vbox_layout_;
        map_show_vbox_layout_=nullptr;
    }
    if(video_show_vbox_layout_!=nullptr){
        delete [] video_show_vbox_layout_;
        video_show_vbox_layout_=nullptr;
    }
    if(aggregative_gridLayout_!=nullptr){
        delete [] aggregative_gridLayout_;
        aggregative_gridLayout_=nullptr;
    }
    if(speed_show_chart_widget_!=nullptr){
        delete [] speed_show_chart_widget_;
        speed_show_chart_widget_=nullptr;
    }
}
void MainShowDialog::InitStackWidget()
{
    this->stacked_widget_=ui->show_tab_choose;
    //创建地图
//    QQuickView *map_page_view=new QQuickView();
//    map_page_view->setSource(QUrl("qrc:/qml/MainShowWindow.qml"));
//    map_page_view->setResizeMode(QQuickView::SizeRootObjectToView);
    map_page_=new QQuickWidget(QUrl("qrc:/qml/MainShowWindow.qml"));
    map_page_->setResizeMode(QQuickWidget::SizeRootObjectToView);
    //获取地图参数
    show_map_=std::shared_ptr<QDeclarativeGeoMap>(map_page_->rootObject()->findChild<QDeclarativeGeoMap *>("show_map"));
    //创建地图布局
    map_show_vbox_layout_=new QVBoxLayout(ui->map_show_page);
    map_show_vbox_layout_->setMargin(0);//设置边距
    map_show_vbox_layout_->addWidget(map_page_);//添加到布局中
    //创建video_page_
    //创建video_page布局
    video_widget_=new VideoShowWidget();
//    //视频显示布局
//    video_show_vbox_layout_=new QHBoxLayout(ui->video_show_page);
//    video_show_vbox_layout_->setMargin(2);
//    video_show_vbox_layout_->setSpacing(0);
//    video_show_vbox_layout_->setContentsMargins(2, 2, 2, 2);
//    video_widget_->change_video_4(0);

//    video_page_=new QWidget();
//    video_show_vbox_layout_->addWidget(video_page_);
//    video_vbox_layout_=new QVBoxLayout(video_page_);
//    video_vbox_layout_->addWidget(video_widget_);
    ui->horizontalLayout->setMargin(1);
    ui->horizontalLayout->setSpacing(1);
    //ui->videoshow_v_div->setContentsMargins(2,2,2,2);
    ui->horizontalLayout->addWidget(video_widget_);

//    ui->video_show_page=video_page_;
//    ui->show_tab_choose->addWidget(video_page_);
//    aggregative_gridLayout_=new QGridLayout();
//    aggregative_gridLayout_->setSpacing(0);
//    aggregative_gridLayout_->setMargin(2);
//    ui->aggregative_horizontalLayout->addLayout(aggregative_gridLayout_);
    //设置仪表盘面板
    speed_show_chart_widget_=new QQuickWidget();
    speed_show_chart_widget_->setResizeMode(QQuickWidget::SizeRootObjectToView);
    speed_show_chart_widget_->setSource(QUrl("qrc:/qml/MyCharts.qml"));
}

void MainShowDialog::on_show_tab_choose_currentChanged(int arg1)
{
    if(arg1==2){
//        ui->verticalLayout_2->insertWidget(0,video_widget_);
//        //ui->verticalLayout_2->addWidget(video_widget_);
//        ui->verticalLayout_2->addWidget(speed_show_chart_widget_);
//        //综合页面进行布局
//        ui->aggregative_horizontalLayout->addWidget(map_page_);
        ui->horizontalLayout_3->addWidget(map_page_);
        ui->verticalLayout_3->addWidget(video_widget_);
        ui->verticalLayout_4->addWidget(speed_show_chart_widget_);
    }else if (arg1==0) {
        map_show_vbox_layout_->addWidget(map_page_);
    }else if (arg1==1) {
        ui->horizontalLayout->addWidget(video_widget_);
    }
    qDebug()<<QString("This current is %1").arg(arg1);
}
void MainShowDialog::print_layout(int index){

//        qDebug()<<"row"<<aggregative_gridLayout_->rowCount();
//        qDebug()<<"col"<<aggregative_gridLayout_->columnCount();
}
