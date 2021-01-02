#include "frmconfig.h"
#include "ui_frmconfig.h"
#include "myhelper.h"
#include "iconhelper.h"
#include "myapp.h"

frmConfig::frmConfig(QWidget *parent) : QDialog(parent),
                                        ui(new Ui::frmConfig)
{
    ui->setupUi(this);

    this->InitStyle();
    this->InitForm();
}

frmConfig::~frmConfig()
{
    delete ui;
}

void frmConfig::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton))
    {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void frmConfig::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void frmConfig::mouseReleaseEvent(QMouseEvent *e)
{
    mousePressed = false;
}

void frmConfig::InitStyle()
{
    this->setProperty("Form", true);
    //窗体居中显示
    myHelper::FormInCenter(this, myApp::DeskWidth, myApp::DeskHeight);
    this->mousePressed = false;
    //设置窗体标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint |
                         Qt::WindowSystemMenuHint |
                         Qt::WindowMinMaxButtonsHint);
    //设置图形字体
    IconHelper::Instance()->SetIcon(ui->lab_Ico, QChar(0xf03d), 11);
    IconHelper::Instance()->SetIcon(ui->btnMenu_Close, QChar(0xf00d), 10);
    //关联关闭按钮
    connect(ui->btnMenu_Close, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(close()));
}

void frmConfig::InitForm()
{
    ui->txtAppTitle->setText(myApp::AppTitle);
    ui->txtNVRType->setText(myApp::NVRType);
    ui->txtIPCType->setText(myApp::IPCType);
    ui->txtNVRType->setCursorPosition(0);
    ui->txtIPCType->setCursorPosition(0);

    ui->btnUseVideoOffLineCheck->SetCheck(myApp::UseVideoOffLineCheck);
    for (int i = 5; i <= 60; i = i + 5)
    {
        ui->cboxVideoOffLineCheckInterval->addItem(QString("%1").arg(i));
    }
    ui->cboxVideoOffLineCheckInterval->setCurrentIndex(ui->cboxVideoOffLineCheckInterval->findText(QString("%1").arg(myApp::VideoOffLineCheckInterval)));

    for (int i = 100; i <= 3000; i = i + 100)
    {
        ui->cboxDelayTime->addItem(QString("%1").arg(i));
    }
    ui->cboxDelayTime->setCurrentIndex(ui->cboxDelayTime->findText(QString("%1").arg(myApp::VideoDelayTime)));

    ui->cboxRtspType->setCurrentIndex(myApp::RtspType);
    ui->btnAutoRun->SetCheck(myApp::AutoRun);
    ui->btnAutoPoll->SetCheck(myApp::AutoPoll);
    ui->cboxPollType->setCurrentIndex(myApp::PollType);

    ui->cboxPollSleep->addItem("0");
    for (int i = 100; i <= 2000; i = i + 100)
    {
        ui->cboxPollSleep->addItem(QString("%1").arg(i));
    }
    ui->cboxPollSleep->setCurrentIndex(ui->cboxPollSleep->findText(QString("%1").arg(myApp::PollSleep)));

    for (int i = 10; i <= 120; i = i + 10)
    {
        ui->cboxPollInterval->addItem(QString("%1").arg(i));
    }
    ui->cboxPollInterval->setCurrentIndex(ui->cboxPollInterval->findText(QString("%1").arg(myApp::PollInterval)));
}

void frmConfig::on_btnOk_clicked()
{
    myApp::AppTitle = ui->txtAppTitle->text();
    myApp::NVRType = ui->txtNVRType->text();
    myApp::IPCType = ui->txtIPCType->text();
    myApp::UseVideoOffLineCheck = ui->btnUseVideoOffLineCheck->GetCheck();
    myApp::VideoOffLineCheckInterval = ui->cboxVideoOffLineCheckInterval->currentText().toInt();
    myApp::VideoDelayTime = ui->cboxDelayTime->currentText().toInt();
    myApp::RtspType = ui->cboxRtspType->currentIndex();
    myApp::AutoRun = ui->btnAutoRun->GetCheck();
    myApp::AutoPoll = ui->btnAutoPoll->GetCheck();
    myApp::PollType = ui->cboxPollType->currentIndex();
    myApp::PollInterval = ui->cboxPollInterval->currentText().toInt();
    myApp::PollSleep = ui->cboxPollSleep->currentText().toInt();

    //设置开机启动（只有windows系统才是这样设置开机启动）
#ifdef Q_OS_WIN
    QString strPath = QApplication::applicationFilePath();
    strPath = strPath.replace("/", "\\");
    if (myApp::AutoRun)
    {
        myHelper::AutoRunWithSystem(true, "VM", strPath);
    }
    else
    {
        myHelper::AutoRunWithSystem(false, "VM", strPath);
    }
#endif

    //调用保存配置文件函数
    myApp::WriteConfig();
    done(1);
    this->close();
}

void frmConfig::on_btnClearNVR_clicked()
{
    if (myHelper::ShowMessageBoxQuesion(QStringLiteral("确定要清空NVR数据吗?")) == 1)
    {
        QSqlQuery query;
        QString sql = "delete from [NVRInfo] where [NVRID]!='000255'";
        query.exec(sql);
        myHelper::ShowMessageBoxInfo(QStringLiteral("清空NVR数据成功!"));
    }
}

void frmConfig::on_btnClearIPC_clicked()
{
    if (myHelper::ShowMessageBoxQuesion(QStringLiteral("确定要清空IPC数据吗?")) == 1)
    {
        QSqlQuery query;
        QString sql = "delete from [IPCInfo]";
        query.exec(sql);
        myHelper::ShowMessageBoxInfo(QStringLiteral("清空IPC数据成功!"));
    }
}

void frmConfig::on_btnClearPoll_clicked()
{
    if (myHelper::ShowMessageBoxQuesion(QStringLiteral("确定要清空轮询数据吗?")) == 1)
    {
        QSqlQuery query;
        QString sql = "delete from [PollInfo]";
        query.exec(sql);
        myHelper::ShowMessageBoxInfo(QStringLiteral("清空轮询数据成功!"));
    }
}

void frmConfig::on_btnClearAll_clicked()
{
    if (myHelper::ShowMessageBoxQuesion(QStringLiteral("确定要恢复出厂值吗?")) == 1)
    {
        QSqlQuery query;
        QString sql = "delete from [NVRInfo] where [NVRID]!='000255'";
        query.exec(sql);
        myHelper::Sleep(100);
        sql = "delete from [IPCInfo]";
        query.exec(sql);
        myHelper::Sleep(100);
        sql = "delete from [PollInfo]";
        query.exec(sql);
        myHelper::ShowMessageBoxInfo(QStringLiteral("恢复出厂值成功!"));
    }
}
