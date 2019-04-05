#include "mainshowdialog.h"
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
    map_page_view->setSource(QUrl("qrc:/qml/MainShowWindow.qml"));
    map_page_view->setResizeMode(QQuickView::SizeRootObjectToView);
    show_map_=std::shared_ptr<QDeclarativeGeoMap>(map_page_view->rootObject()->findChild<QDeclarativeGeoMap *>("show_map"));
    map_page_=QWidget::createWindowContainer(map_page_view);
    //初始化video_page
    video_page_=new VideoShowWidget();
    //设置QstatckedWidget
    stacked_widget_->addWidget(map_page_);
    stacked_widget_->addWidget(video_page_);
    //添加绑定
    vbox_layout_->addWidget(stacked_widget_);
    //默认选择第一地图页
    stacked_widget_->setCurrentIndex(0);
    //设置窗口模式为Window窗口模式
    //设置模式，显示最大，最小按钮
    this->setModal(Qt::Widget);
    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowMinMaxButtonsHint;
    flags |= Qt::WindowCloseButtonHint;
    this->setWindowFlags(flags);
}

MainShowDialog::~MainShowDialog()
{

}
