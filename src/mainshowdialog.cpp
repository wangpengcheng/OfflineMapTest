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
    //this->setLayout(vbox_layout_);
    //创建地图
    map_page_=new QQuickWidget();
    map_page_->setResizeMode(QQuickWidget::SizeRootObjectToView);
    map_page_->setSource(QUrl("qrc:/qml/MapControlModel.qml"));
    //创建地图布局
    map_show_vbox_layout_=new QVBoxLayout(ui->map_show_page);
    map_show_vbox_layout_->setMargin(5);//设置

}

MainShowDialog::~MainShowDialog()
{
    delete ui;
}
