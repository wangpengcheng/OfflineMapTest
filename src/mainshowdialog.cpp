#include "mainshowdialog.h"
//#include "ui_mainshowdialog.h"
#include "VideoControl/videoshowwidget.h"
MainShowDialog::MainShowDialog(QWidget *parent) :
    QDialog(parent)//, ui(new Ui::MainShowDialog)
{
    //ui->setupUi(this);
    //设置水平布局
    QVBoxLayout* vbox_layout_=new QVBoxLayout(this);
    vbox_layout_->setMargin(5);
    //初始化 stackedWidget
    stacked_widget_ = new QStackedWidget(this);
    stacked_widget_->setObjectName(QStringLiteral("stackedWidget"));
    //初始化map_widget
    QQuickView *map_page_view=new QQuickView();
    //map_page_=new QWidget();
    map_page_view->setSource(QUrl("qrc:/qml/MainShowWindow.qml"));
    map_page_view->setResizeMode(QQuickView::SizeRootObjectToView);
    map_page_=QWidget::createWindowContainer(map_page_view);
   // ui->page=map_page_;
    video_page_=new VideoShowWidget();
//    stacked_widget_->setParent(this);
    stacked_widget_->addWidget(map_page_);
    stacked_widget_->addWidget(video_page_);
//    vbox_layout_->addWidget(video_page_);
//    this->setLayout(vbox_layout_);//设置水平布局
   // ui->page_2=video_page_;
    vbox_layout_->addWidget(stacked_widget_);
    stacked_widget_->setCurrentIndex(1);
    //设置模式，显示最大，最小按钮
    this->setModal(Qt::Widget);//设置窗口模式为Window窗口模式
    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowMinMaxButtonsHint;
    flags |= Qt::WindowCloseButtonHint;
    this->setWindowFlags(flags);
}

MainShowDialog::~MainShowDialog()
{
    delete ui;
}
