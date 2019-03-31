#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->map_control->setResizeMode(QQuickWidget::SizeRootObjectToView);
    ui->map_control->setSource(QUrl("qrc:/qml/MapControlModel.qml"));
    QDeclarativeGeoMap *control_map=ui->map_control->rootObject()->findChild<QDeclarativeGeoMap *>("control_show_map");
}

MainWindow::~MainWindow()
{
    delete ui;
}
