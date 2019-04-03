#include "frmmain.h"
#include "ui_frmmain.h"
#include "iconhelper.h"
#include "myhelper.h"
#include "myapp.h"
#include "frmconfig.h"
#include "frmnvr.h"
#include "frmipc.h"
#include "frmpollconfig.h"

frmMain::frmMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmMain)
{
    ui->setupUi(this);
    //初始化风格
    this->InitStyle();
    //初始化表格
    this->InitForm();
    this->InitVideo();
    this->LoadVideo();
    this->LoadNVRIPC();
}

frmMain::~frmMain()
{
    delete ui;
}

void frmMain::InitStyle()
{
	this->setStyleSheet("QGroupBox#gboxMain{border-width:0px;}");
    this->setProperty("Form", true);
    //设置窗体标题栏隐藏--Qt::WindowStaysOnTopHint |
    this->setWindowFlags(Qt::FramelessWindowHint |
                         Qt::WindowSystemMenuHint |
                         Qt::WindowMinMaxButtonsHint);

    IconHelper::Instance()->SetIcon(ui->btnMenu_Close, QChar(0xf00d), 10);
    IconHelper::Instance()->SetIcon(ui->btnMenu_Min, QChar(0xf068), 10);
    IconHelper::Instance()->SetIcon(ui->lab_Ico, QChar(0xf03d), 11);
    IconHelper::Instance()->SetIcon(ui->labStyle, QChar(0xf103), 12);
}

void frmMain::change_style()
{
    QAction *action = (QAction *)sender();
    QString style = action->text();
    qDebug()<<style;
    if (style==QStringLiteral("淡蓝色")) {
        qDebug()<<style;
        myApp::AppStyle = QStringLiteral(":/image/blue.css");
    } else if (style == QStringLiteral("蓝色")) {
        myApp::AppStyle = QStringLiteral(":/image/dev.css");
    } else if (style == QStringLiteral("灰色")) {
        myApp::AppStyle = QStringLiteral(":/image/gray.css");
    } else if (style == QStringLiteral("黑色")) {
        myApp::AppStyle = QStringLiteral(":/image/black.css");
    } else if (style == QStringLiteral("灰黑色")) {
        myApp::AppStyle = QStringLiteral(":/image/brown.css");
    } else if (style == QStringLiteral("白色")) {
        myApp::AppStyle = QStringLiteral(":/image/white.css");
    } else if (style == QStringLiteral("银色")) {
        myApp::AppStyle = QStringLiteral(":/image/silvery.css");
    }

    myHelper::SetStyle(myApp::AppStyle);
    myApp::WriteConfig();
}

void frmMain::InitForm()
{
    ui->labFull->installEventFilter(this);
    ui->labFull->setProperty("labForm", true);

    ui->labStart->installEventFilter(this);
    ui->labStart->setProperty("labForm", true);

    ui->labNVR->installEventFilter(this);
    ui->labNVR->setProperty("labForm", true);

    ui->labIPC->installEventFilter(this);
    ui->labIPC->setProperty("labForm", true);

    ui->labPollConfig->installEventFilter(this);
    ui->labPollConfig->setProperty("labForm", true);

    ui->labVideoPlayBack->installEventFilter(this);
    ui->labVideoPlayBack->setProperty("labForm", true);

    ui->labConfig->installEventFilter(this);
    ui->labConfig->setProperty("labForm", true);

    ui->labExit->installEventFilter(this);
    ui->labExit->setProperty("labForm", true);

    ui->labStyle->installEventFilter(this);
    ui->labStyle->setProperty("labForm", true);

    menuStyle = new QMenu(this);
    menuStyle->addAction(QStringLiteral("淡蓝色"), this, SLOT(change_style()));
    menuStyle->addAction(QStringLiteral("蓝色"), this, SLOT(change_style()));
    menuStyle->addAction(QStringLiteral("灰色"), this, SLOT(change_style()));
    menuStyle->addAction(QStringLiteral("黑色"), this, SLOT(change_style()));
    menuStyle->addAction(QStringLiteral("灰黑色"), this, SLOT(change_style()));
    menuStyle->addAction(QStringLiteral("白色"), this, SLOT(change_style()));
    menuStyle->addAction(QStringLiteral("银色"), this, SLOT(change_style()));
    menuStyle->setStyleSheet("font: 10pt \"微软雅黑\";");

    ui->lab_Title->setText(myApp::AppTitle);
    this->setWindowTitle(myApp::AppTitle);

    ui->treeMain->header()->setVisible(false);
    ui->treeMain->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void frmMain::InitVideo()
{
    tempLab = 0;
    video_max = false;

    VideoLab.append(ui->labVideo1);
    VideoLab.append(ui->labVideo2);
    VideoLab.append(ui->labVideo3);
    VideoLab.append(ui->labVideo4);
    VideoLab.append(ui->labVideo5);
    VideoLab.append(ui->labVideo6);
    VideoLab.append(ui->labVideo7);
    VideoLab.append(ui->labVideo8);
    VideoLab.append(ui->labVideo9);
    VideoLab.append(ui->labVideo10);
    VideoLab.append(ui->labVideo11);
    VideoLab.append(ui->labVideo12);
    VideoLab.append(ui->labVideo13);
    VideoLab.append(ui->labVideo14);
    VideoLab.append(ui->labVideo15);
    VideoLab.append(ui->labVideo16);

    VideoLay.append(ui->lay1);
    VideoLay.append(ui->lay2);
    VideoLay.append(ui->lay3);
    VideoLay.append(ui->lay4);

    for (int i = 0; i < 16; i++) {
        VideoLab[i]->installEventFilter(this);
        VideoLab[i]->setProperty("labVideo", true);
        VideoLab[i]->setText(QStringLiteral("通道%1").arg(i + 1));
    }
    //设置右键
    menu = new QMenu(this);
    menu->setStyleSheet("font: 10pt \"微软雅黑\";");
    menu->addAction(QStringLiteral("删除当前视频"), this, SLOT(delete_video_one()));
    menu->addAction(QStringLiteral("删除所有视频"), this, SLOT(delete_video_all()));
    menu->addSeparator();
    menu->addAction(QStringLiteral("截图当前视频"), this, SLOT(snapshot_video_one()));
    menu->addAction(QStringLiteral("截图所有视频"), this, SLOT(snapshot_video_all()));
    menu->addSeparator();
    //设置切换1画面
    QMenu *menu1 = menu->addMenu(QStringLiteral("切换到1画面"));
    menu1->addAction(QStringLiteral("通道1"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("通道2"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("通道3"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("通道4"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("通道5"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("通道6"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("通道7"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("通道8"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("通道9"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("通道10"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("通道11"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("通道12"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("通道13"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("通道14"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("通道15"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("通道16"), this, SLOT(show_video_1()));
    //设置切换4画面
    QMenu *menu4 = menu->addMenu(QStringLiteral("切换到4画面"));
    menu4->addAction(QStringLiteral("通道1-通道4"), this, SLOT(show_video_4()));
    menu4->addAction(QStringLiteral("通道5-通道8"), this, SLOT(show_video_4()));
    menu4->addAction(QStringLiteral("通道9-通道12"), this, SLOT(show_video_4()));
    menu4->addAction(QStringLiteral("通道13-通道16"), this, SLOT(show_video_4()));
    //设置切换到9画面
    QMenu *menu9 = menu->addMenu(QStringLiteral("切换到9画面"));
    menu9->addAction(QStringLiteral("通道1-通道9"), this, SLOT(show_video_9()));
    menu9->addAction(QStringLiteral("通道8-通道16"), this, SLOT(show_video_9()));
    //设置切换到16画面
    menu->addAction(QStringLiteral("切换到16画面"), this, SLOT(show_video_16()));
}

void frmMain::LoadVideo()
{
    //自动应用最后一次的布局配置
    ChangeVideoLayout();
}

void frmMain::ChangeRtspAddr(int ch, QString rtspAddr)
{
    QStringList rtspAddrs = myApp::RtspAddr16.split("|");
    rtspAddrs[ch] = rtspAddr;

    QString tempRtspAddr16;
    for (int i = 0; i < 16; i++) {
        tempRtspAddr16 += rtspAddrs[i] + "|";
    }
    myApp::RtspAddr16 = tempRtspAddr16.mid(0, tempRtspAddr16.length() - 1);
}
//加载vcr表格
void frmMain::LoadNVRIPC()
{
    ui->treeMain->clear();

    QSqlQuery queryNVR;
    QString sqlNVR = "select [NVRID],[NVRName],[NVRIP] from [NVRInfo] where [NVRUse]='启用'";
    queryNVR.exec(sqlNVR);

    while (queryNVR.next()) {
        QString tempNVRID = queryNVR.value(0).toString();
        QString tempNVRName = queryNVR.value(1).toString();
        QString tempNVRIP = queryNVR.value(2).toString();

        QTreeWidgetItem *itemNVR = new QTreeWidgetItem
                (ui->treeMain, QStringList(tempNVRName + "[" + tempNVRIP + "]"));
        itemNVR->setIcon(0, QIcon(":/image/nvr.png"));

        QSqlQuery queryIPC;
        QString sqlIPC = QString("select [IPCID],[IPCName],[IPCRtspAddrMain] from [IPCInfo] where [NVRID]='%1' and [IPCUse]='启用' order by [IPCID] asc").arg(tempNVRID);
        queryIPC.exec(sqlIPC);

        while (queryIPC.next()) {
            QString tempIPCName = queryIPC.value(1).toString();
            QString rtspAddr = queryIPC.value(2).toString();

            QStringList temp = rtspAddr.split("/");
            QString ip = temp[2].split(":")[0];

            QTreeWidgetItem *itemIPC = new QTreeWidgetItem(itemNVR, QStringList(QString(tempIPCName + "[" + ip + "]")));
            itemIPC->setIcon(0, QIcon(":/image/ipc_normal.png"));
            itemNVR->addChild(itemIPC);
        }
    }
    ui->treeMain->expandAll();
}

void frmMain::ChangeVideoLayout()
{
    if (myApp::VideoType == "1_4") {
        removelayout();
        change_video_4(0);
    } else if (myApp::VideoType == "5_8") {
        removelayout();
        change_video_4(4);
    } else if (myApp::VideoType == "9_12") {
        removelayout();
        change_video_4(8);
    } else if (myApp::VideoType == "13_16") {
        removelayout();
        change_video_4(12);
    } else if (myApp::VideoType == "1_9") {
        removelayout();
        change_video_9(0);
    } else if (myApp::VideoType == "8_16") {
        removelayout();
        change_video_9(7);
    } else if (myApp::VideoType == "16") {
        removelayout();
        change_video_16(0);
    }
}

void frmMain::keyPressEvent(QKeyEvent *event)
{
    //空格键进入全屏,esc键退出全屏
    switch(event->key()) {
    case Qt::Key_F1:
        screen_full();
        break;
    case Qt::Key_Escape:
        screen_normal();
        break;
    default:
        QDialog::keyPressEvent(event);
        break;
    }
}

bool frmMain::eventFilter(QObject *obj, QEvent *event)
{
    //将其转为静态指针
    QMouseEvent *MouseEvent = static_cast<QMouseEvent *>(event);
    //设置鼠标双击事件
    if ((event->type() == QEvent::MouseButtonDblClick) &&
            (MouseEvent->buttons() == Qt::LeftButton)) {
        QLabel *labDouble = qobject_cast<QLabel *>(obj);
        if (!video_max) {//如果通道不是最大化。实现最大化
            removelayout();//将显示的视屏移除
            video_max = true;//设置最大化为真
            VideoLay[0]->addWidget(labDouble);//添加窗口到布局界面
            labDouble->setVisible(true);
        } else {//已经全屏则退回原来的模式
            video_max = false;
            ChangeVideoLayout();//更改模式为原来的模式
        }

        labDouble->setFocus();//设置获得焦点事件
        return true;
    } else if (event->type() == QEvent::MouseButtonPress) {//获取简单鼠标点击事件
        if (obj == ui->labFull) {//如果是全屏
            screen_full();//全屏
            return true;
        } else if (obj == ui->labStart) {//启动轮询
            if (ui->labStart->text() == QStringLiteral("启动轮询")) {
                ui->labStart->setText(QStringLiteral("停止轮询"));
            } else {
                ui->labStart->setText(QStringLiteral("启动轮询"));
            }
            return true;
        } else if (obj == ui->labNVR) {//如果是NVR,则开启NVR
            frmNVR nvr;
            nvr.exec();
            LoadNVRIPC();
            return true;
        } else if (obj == ui->labIPC) {//如果是IPC，则开启IPC窗口
            frmIPC ipc;
            ipc.exec();
            LoadNVRIPC();
            return true;
        } else if (obj == ui->labPollConfig) {//开启轮询设置界面
            frmPollConfig pollConfig;
            pollConfig.exec();//显示设置按钮
            return true;
        } else if (obj == ui->labVideoPlayBack) {//设置视频互访
            myHelper::ShowMessageBoxError(QStringLiteral("功能暂未开放!"));
            return true;
        } else if (obj == ui->labConfig) {//设置系统设置
            frmConfig config;
            config.exec();
            ui->lab_Title->setText(myApp::AppTitle);
            this->setWindowTitle(myApp::AppTitle);
            return true;
        } else if (obj == ui->labExit) {//关闭按钮
            on_btnMenu_Close_clicked();
            return true;
        } else if (obj == ui->labStyle) {//风格按钮
            menuStyle->exec(QPoint(myApp::DeskWidth - 155, 31));
            return true;
        } else if (MouseEvent->buttons() == Qt::RightButton) {//途观是鼠标右键的话
            tempLab = qobject_cast<QLabel *>(obj);
            menu->exec(QCursor::pos());//鼠标右键位置
            return true;
        } else {
            tempLab = qobject_cast<QLabel *>(obj);
            //设置当前选中
            ui->lab_Title->setText(QStringLiteral("%1  当前选中[%2]").arg(myApp::AppTitle).arg(tempLab->text()));
            return true;
        }
    }

    return QObject::eventFilter(obj, event);//返回监听事件
}

void frmMain::on_btnMenu_Close_clicked()
{
    exit(0);
}

void frmMain::on_btnMenu_Min_clicked()
{
    this->showMinimized();
}

void frmMain::delete_video_one()
{

}

void frmMain::delete_video_all()
{

}

void frmMain::snapshot_video_one()
{

}

void frmMain::snapshot_video_all()
{

}

void frmMain::removelayout()
{
    for (int i = 0; i < 4; i++) {
        VideoLay[0]->removeWidget(VideoLab[i]);
        VideoLab[i]->setVisible(false);
    }

    for (int i = 4; i < 8; i++) {
        VideoLay[1]->removeWidget(VideoLab[i]);
        VideoLab[i]->setVisible(false);
    }

    for (int i = 8; i < 12; i++) {
        VideoLay[2]->removeWidget(VideoLab[i]);
        VideoLab[i]->setVisible(false);
    }

    for (int i = 12; i < 16; i++) {
        VideoLay[3]->removeWidget(VideoLab[i]);
        VideoLab[i]->setVisible(false);
    }
}

void frmMain::show_video_1()
{
    removelayout();
    myApp::VideoType = "1";
    video_max = true;
    int index = 0;

    QAction *action = (QAction *)sender();
    QString name = action->text();
    if (name == "通道1") {
        index = 0;
    } else if (name == "通道2") {
        index = 1;
    } else if (name == "通道3") {
        index = 2;
    } else if (name == "通道4") {
        index = 3;
    } else if (name == "通道5") {
        index = 4;
    } else if (name == "通道6") {
        index = 5;
    } else if (name == "通道7") {
        index = 6;
    } else if (name == "通道8") {
        index = 7;
    } else if (name == "通道9") {
        index = 8;
    } else if (name == "通道10") {
        index = 9;
    } else if (name == "通道11") {
        index = 10;
    } else if (name == "通道12") {
        index = 11;
    } else if (name == "通道13") {
        index = 12;
    } else if (name == "通道14") {
        index = 13;
    } else if (name == "通道15") {
        index = 14;
    } else if (name == "通道16") {
        index = 15;
    }

    change_video_1(index);
    myApp::WriteConfig();
}

void frmMain::change_video_1(int index)
{
    for (int i = (index + 0); i < (index + 1) ; i++) {
        VideoLay[0]->addWidget(VideoLab[i]);
        VideoLab[i]->setVisible(true);
    }
}

void frmMain::show_video_4()
{
    removelayout();
    video_max = false;
    int index = 0;

    QAction *action = (QAction *)sender();
    QString name = action->text();
    if (name == "通道1-通道4") {
        index = 0;
        myApp::VideoType = "1_4";
    } else if (name == "通道5-通道8") {
        index = 4;
        myApp::VideoType = "5_8";
    } else if (name == "通道9-通道12") {
        index = 8;
        myApp::VideoType = "9_12";
    } else if (name == "通道13-通道16") {
        index = 12;
        myApp::VideoType = "13_16";
    }

    change_video_4(index);
    myApp::WriteConfig();
}

void frmMain::change_video_4(int index)
{
    for (int i = (index + 0); i < (index + 2); i++) {
        VideoLay[0]->addWidget(VideoLab[i]);
        VideoLab[i]->setVisible(true);
    }

    for (int i = (index + 2); i < (index + 4); i++) {
        VideoLay[1]->addWidget(VideoLab[i]);
        VideoLab[i]->setVisible(true);
    }
}

void frmMain::show_video_9()
{
    removelayout();
    video_max = false;
    int index = 0;

    QAction *action = (QAction *)sender();
    QString name = action->text();
    if (name == "通道1-通道9") {
        index = 0;
        myApp::VideoType = "1_9";
    } else if (name == "通道8-通道16") {
        index = 7;
        myApp::VideoType = "8_16";
    }

    change_video_9(index);
    myApp::WriteConfig();
}

void frmMain::change_video_9(int index)
{
    for (int i = (index + 0); i < (index + 3); i++) {
        VideoLay[0]->addWidget(VideoLab[i]);
        VideoLab[i]->setVisible(true);
    }

    for (int i = (index + 3); i < (index + 6); i++) {
        VideoLay[1]->addWidget(VideoLab[i]);
        VideoLab[i]->setVisible(true);
    }

    for (int i = (index + 6); i < (index + 9); i++) {
        VideoLay[2]->addWidget(VideoLab[i]);
        VideoLab[i]->setVisible(true);
    }
}

void frmMain::show_video_16()
{
    removelayout();
    myApp::VideoType = "16";
    video_max = false;
    int index = 0;
    change_video_16(index);
    myApp::WriteConfig();
}

void frmMain::change_video_16(int index)
{
    for (int i = (index + 0); i < (index + 4); i++) {
        VideoLay[0]->addWidget(VideoLab[i]);
        VideoLab[i]->setVisible(true);
    }

    for (int i = (index + 4); i < (index + 8); i++) {
        VideoLay[1]->addWidget(VideoLab[i]);
        VideoLab[i]->setVisible(true);
    }

    for (int i = (index + 8); i < (index + 12); i++) {
        VideoLay[2]->addWidget(VideoLab[i]);
        VideoLab[i]->setVisible(true);
    }

    for (int i = (index + 12); i < (index + 16); i++) {
        VideoLay[3]->addWidget(VideoLab[i]);
        VideoLab[i]->setVisible(true);
    }
}

QString frmMain::GetNVRID(QString NVRIP)
{
    QSqlQuery query;
    QString sql = "select [NVRID] from [NVRInfo]";
    sql += " where [NVRIP]='" + NVRIP + "'";
    query.exec(sql);
    query.next();
    return query.value(0).toString();
}

void frmMain::GetRtspAddr(QString NVRID, QString IPCIP, QString &IPCRtspAddrMain, QString &IPCRtspAddrSub)
{
    QSqlQuery query;
    QString sql = "select [IPCRtspAddrMain],[IPCRtspAddrSub] from [IPCInfo] where [IPCUse]='启用'";
    sql += " and [NVRID]='" + NVRID + "'";
    query.exec(sql);
    while(query.next()) {
        //取出子码流地址,看是否IP相同
        QString rtspAddr = query.value(0).toString();
        QStringList temp = rtspAddr.split("/");
        QString ip = temp[2].split(":")[0];
        if (ip == IPCIP) {
            IPCRtspAddrMain = query.value(0).toString();
            IPCRtspAddrSub = query.value(1).toString();
            break;
        }
    }
}

void frmMain::on_treeMain_doubleClicked(const QModelIndex &index)
{
    //选中的是NVR则不处理
    if (ui->treeMain->currentItem()->parent() == 0) {
        return;
    }

    //当前还没有选择通道
    if (tempLab == 0) {
        return;
    }

    //取出双击摄像机的子码流地址
    //取出NVR编号及IPCID
    QString txt = ui->treeMain->currentItem()->parent()->text(0);
    QString NVRIP = txt.split("[")[1].split("]")[0];
    QString NVRID = GetNVRID(NVRIP);
    QString temp = ui->treeMain->currentIndex().data().toString();
    QString IPCIP = temp.split("[")[1].split("]")[0];

    //根据NVR编号和IP地址查询出该摄像机的子码流
    QString rtspAddr;
    QString IPCRtspAddrMain;
    QString IPCRtspAddrSub;
    GetRtspAddr(NVRID, IPCIP, IPCRtspAddrMain, IPCRtspAddrSub);
    rtspAddr = (myApp::RtspType == 0 ? IPCRtspAddrMain : IPCRtspAddrSub);

    //如果该摄像机不在线
    if (!myHelper::IPCEnable(rtspAddr)) {
        myHelper::ShowMessageBoxError("该摄像机不在线!");
        return;
    }

    QString tempCH = tempLab->text();
    for (int i = 0; i < 16; i++) {
        if (VideoLab[i]->text() == tempCH) {
            ChangeRtspAddr(i, rtspAddr);
            myApp::WriteConfig();
            break;
        }
    }
}

void frmMain::screen_full()
{
    this->setGeometry(qApp->desktop()->geometry());
    this->layout()->setContentsMargins(0, 0, 0, 0);
    ui->widget_main->layout()->setContentsMargins(0, 0, 0, 0);
    ui->widget_title->setVisible(false);
    ui->treeMain->setVisible(false);
}

void frmMain::screen_normal()
{
    this->setGeometry(qApp->desktop()->availableGeometry());
    this->layout()->setContentsMargins(1, 1, 1, 1);
    ui->widget_main->layout()->setContentsMargins(5, 5, 5, 5);
    ui->widget_title->setVisible(true);
    ui->treeMain->setVisible(true);
}

void frmMain::on_labStart_linkActivated(const QString &link)
{

}

void frmMain::on_labConfig_linkActivated(const QString &link)
{

}
