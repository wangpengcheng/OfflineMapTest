#include "frmmain.h"
#include "ui_frmmain.h"
#include "iconhelper.h"
#include "myhelper.h"
#include "myapp.h"
#include "frmconfig.h"
#include "frmnvr.h"
#include "frmipc.h"
#include "frmpollconfig.h"
#include "src/mainshowdialog.h"
#include "src/mapcontrlconnect.h"
#include "test/buslinetest.h"
#include "test/bustest.h"
#include "videodecodethread.h"
#include "streamvideowidget.h"
#include "player/player.h"
#include "src/tool.h"
#include "src/bus.h"
frmMain::frmMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmMain)
{
    ui->setupUi(this);
    //初始化风格
    this->InitStyle();
    //初始化表格
    this->InitForm();
    //初始化视频
    this->InitVideo();
    //初始化TabWidget
    this->InitTabWidget();
    //初始化视频加载
    this->LoadVideo();
    //初始化NVRIPC
    this->LoadNVRIPC();
    //初始化右侧按钮
    this->InitMenu();
    //初始化ShowDialog
    this->InitShowDialog();
}

frmMain::~frmMain()
{
    delete ui;

    DELETE_QOBJECT(menuStyle);
    DELETE_QOBJECT(menu);
    DELETE_QOBJECT(menu8);
    DELETE_QOBJECT(video_vbox_layout_);
    DELETE_QOBJECT(video_control_widget_);
    DELETE_QOBJECT(map_control_widget_);
    DELETE_QOBJECT(map_control_view_);
    DELETE_QOBJECT(map_vbox_layout_);
    DELETE_QOBJECT(aggregative_gridLayout_);
    DELETE_QOBJECT(speed_chart_widget_);
    DELETE_QOBJECT(map_connect_);
    DELETE_OBJECT(bus_test_);
    DELETE_OBJECT(bus_line_test_);
}

void frmMain::InitStyle()
{
	this->setStyleSheet("QGroupBox#gboxMain{border-width:0px;}");
    this->setProperty("Form", true);
    //设置窗体标题栏隐藏--Qt::WindowStaysOnTopHint |
//    this->setWindowFlags(Qt::FramelessWindowHint |
//                         Qt::WindowSystemMenuHint |
//                         Qt::WindowMinMaxButtonsHint);
//    this->setModal(Qt::Widget);
//    Qt::WindowFlags flags = Qt::Dialog;
//    flags |= Qt::WindowMinMaxButtonsHint;
//    flags |= Qt::WindowCloseButtonHint;
//    this->setWindowFlags(flags);
    ui->btnMenu_Close->hide();
    ui->btnMenu_Min->hide();

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
    //------ set button listern start ------
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

    ui->labResetScreen->installEventFilter(this);
    ui->labResetScreen->setProperty("labForm", true);

    //------ set button listern end ------

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

void frmMain::InitTabWidget(){
      //添加视频控制
     video_vbox_layout_=new QVBoxLayout();
     ui->video_control_page->setLayout(video_vbox_layout_);
     video_vbox_layout_->setMargin(2);
     video_vbox_layout_->addWidget(ui->widget_main);
     video_control_widget_=ui->widget_main;
     //添加地图控制
     map_control_widget_=new QWidget();
     map_control_view_=new QQuickView();
     map_control_view_->setResizeMode(QQuickView::SizeRootObjectToView);
     map_control_view_->setSource(QUrl("qrc:/qml/MapControlModel.qml"));
     map_control_widget_=QWidget::createWindowContainer(map_control_view_);
     //创建地图布局控件
     map_vbox_layout_=new QVBoxLayout(ui->map_control_page);
     map_vbox_layout_->setMargin(2);//设置边距
     map_vbox_layout_->addWidget(map_control_widget_);

     //获取控制地图
     control_map_=std::shared_ptr<QDeclarativeGeoMap>(map_control_view_->rootObject()->findChild<QDeclarativeGeoMap *>("control_show_map"));
     //初始化综合模式
     //由于综合模式的特殊性，不得不使用QTabWidget的信号来实现切换
     //QVBoxLayout* aggregative_vbox_layout_=new QVBoxLayout(ui->aggregative_model);
     //初始化网格布局
     aggregative_gridLayout_=new QGridLayout(ui->aggregative_model);
     //设置仪表盘面板
     speed_chart_widget_=new QQuickWidget();
     speed_chart_widget_->setResizeMode(QQuickWidget::SizeRootObjectToView);
     speed_chart_widget_->setSource(QUrl("qrc:/qml/MyCharts.qml"));
     //初始化回放布局
     video_review_layout_=new QVBoxLayout(ui->video_review);
     video_review_control_=new Player(ui->video_review);
     video_review_layout_->addWidget(video_review_control_);
}

void frmMain::InitVideo()
{
    tempLab = 0;
    video_max_ = false;
    video_count_=12;
    video_type_="1_12";
    //添加QLab
    for(int i=0;i<video_count_;++i){
        QLabel *widget = new QLabel();
        widget->setObjectName(QString("video%1").arg(i + 1));
        widget->installEventFilter(this);
        widget->setFocusPolicy(Qt::StrongFocus);
        widget->setAlignment(Qt::AlignCenter);
        //二选一可以选择显示文字,也可以选择显示背景图片
        widget->setLineWidth(2);
        widget->setText(QString(QStringLiteral("通道 %1")).arg(i + 1));
        //widget->setPixmap(QPixmap(":/bg_novideo.png"));
        video_labs_.append(widget);
    }
}

void frmMain::InitMenu()
{
    //设置右键
    menu = new QMenu(this);
    menu->setStyleSheet(QStringLiteral("font: 10pt \"微软雅黑\";"));
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
//    menu1->addAction(QStringLiteral("通道13"), this, SLOT(show_video_1()));
//    menu1->addAction(QStringLiteral("通道14"), this, SLOT(show_video_1()));
//    menu1->addAction(QStringLiteral("通道15"), this, SLOT(show_video_1()));
//    menu1->addAction(QStringLiteral("通道16"), this, SLOT(show_video_1()));
    //设置切换4画面
    QMenu *menu4 = menu->addMenu(QStringLiteral("切换到4画面"));
    menu4->addAction(QStringLiteral("通道1-通道4"), this, SLOT(show_video_4()));
    menu4->addAction(QStringLiteral("通道5-通道8"), this, SLOT(show_video_4()));
    menu4->addAction(QStringLiteral("通道9-通道12"), this, SLOT(show_video_4()));
   // menu4->addAction(QStringLiteral("通道13-通道16"), this, SLOT(show_video_4()));
    //设置切换6画面
    QMenu *menu6=menu->addMenu(QStringLiteral("切换到6画面"));
    menu6->addAction(QStringLiteral("通道1-通道6"), this, SLOT(show_video_6()));
    menu6->addAction(QStringLiteral("通道7-通道12"), this, SLOT(show_video_6()));
    //设置切换到7画面
    QMenu *menu7 = menu->addMenu(QStringLiteral("切换到7画面"));
    menu7->addAction(QStringLiteral("通道1-通道7"), this, SLOT(show_video_7()));
    menu7->addAction(QStringLiteral("通道6-通道12"), this, SLOT(show_video_7()));
    //设置切换到12画面
    menu->addAction(QStringLiteral("切换到12画面"), this, SLOT(show_video_12()));
    menu8=menu->addMenu(QStringLiteral("视频控制"));
}
void frmMain::LoadVideo()
{
    //自动应用最后一次的布局配置
    ChangeVideoLayout();
}
//更改rtsp地址
void frmMain::ChangeRtspAddr(int ch, QString rtspAddr)
{
    QStringList rtspAddrs = myApp::RtspAddr12.split("|");
    rtspAddrs[ch] = rtspAddr;
    qDebug()<<rtspAddr;
    QString tempRtspAddr12;
    for (int i = 0; i < 12; ++i) {
        tempRtspAddr12 += rtspAddrs[i] + "|";
    }
    //更改配置
    myApp::RtspAddr12 = tempRtspAddr12.mid(0, tempRtspAddr12.length() - 1);
    //点击应用更换画面

}
//加载vcr表格
void frmMain::LoadNVRIPC()
{
    ui->treeMain->clear();

    QSqlQuery queryNVR;
    QString sqlNVR = QStringLiteral("select [NVRID],[NVRName],[NVRIP] from [NVRInfo] where [NVRUse]='启用'");
    queryNVR.exec(sqlNVR);

    while (queryNVR.next()) {
        //获取NVRID的ID
        QString tempNVRID = queryNVR.value(0).toString();
        //获取NVRID的名称
        QString tempNVRName = queryNVR.value(1).toString();
        //获取NVRID的IP
        QString tempNVRIP = queryNVR.value(2).toString();
        //创建新想treewidget
        QTreeWidgetItem *itemNVR = new QTreeWidgetItem
                (ui->treeMain, QStringList(tempNVRName + "[" + tempNVRIP + "]"));
        itemNVR->setIcon(0, QIcon(":/image/nvr.png"));

        QSqlQuery queryIPC;
        QString sqlIPC = QString(QStringLiteral("select [IPCID],[IPCName],[IPCRtspAddrMain] from [IPCInfo] where [NVRID]='%1' and [IPCUse]='启用' order by [IPCID] asc")).arg(tempNVRID);
        queryIPC.exec(sqlIPC);

        while (queryIPC.next()) {
            QString temp_id=queryIPC.value(0).toString();
            QString tempIPCName = queryIPC.value(1).toString();
            QString rtspAddr = queryIPC.value(2).toString();

            QStringList temp = rtspAddr.split("/");
            QString ip = temp[2].split(":")[0];

            QTreeWidgetItem *itemIPC = new QTreeWidgetItem(itemNVR, QStringList(QString(tempIPCName + "[" + ip + "]")));
            itemIPC->setIcon(0, QIcon(":/image/ipc_normal.png"));
            itemNVR->addChild(itemIPC);
            //根据列表初始化
            //创建解码线程
            qDebug()<<rtspAddr;
            qDebug()<<temp_id;
            VideoDecodeThread* temp_decode=new VideoDecodeThread(rtspAddr);
            QSharedPointer<VideoDecodeThread> test_temp(temp_decode);
            //绑定视频存储的信号函数
            connect(this,&frmMain::signal_send_record_id,test_temp.get(),&VideoDecodeThread::StartSaveVideo);
            connect(this,&frmMain::signal_send_stop,test_temp.get(),&VideoDecodeThread::StopSaveVideo);

            qDebug()<<test_temp.get()->net_stream_address();
            decode_list_.insert(temp_id,test_temp);

        }
    }
    qDebug()<<decode_list_;
    ui->treeMain->expandAll();
}
//初始化显示窗口
void frmMain::InitShowDialog()
{
    //初始化显示窗口
    show_dialog_=new MainShowDialog();
    //设置显示两个窗口位置
    //show_dialog_->setGeometry(QApplication::desktop()->screenGeometry(1));
    show_dialog_->move(QApplication::desktop()->screenGeometry(1).center());
    show_dialog_->resize(800,600);

    //this->setGeometry(QApplication::desktop()->screenGeometry(0));
    this->move(QApplication::desktop()->screenGeometry(0).center());
    this->resize(800,600);
    //连接显示地图和控制地图
    if(control_map_!=nullptr&&
       show_dialog_->show_map()!=nullptr)
    {
        //连接地图
        map_connect_=new MapContrlConnect(show_dialog_->show_map(),
                                          this->control_map_);

    }else {
        myHelper::ShowMessageBoxError("Can not connect two map ,this input pointer is empty!");
    }
    //显示地图添加车辆和站点
    if(show_dialog_->show_map()!=nullptr){
        //使用测试类中的数据,添加线路
        //TODO 连接数据库，进行数据的加载
        bus_line_test_=new BusLineTest();
        bus_line_test_->MainTest();
        bus_line_test_->ShowTest(show_dialog_->show_map().get());
        //添加车辆
        bus_test_=new BusTest();//直接在堆上分配内存
        bus_test_->ShowTest(show_dialog_->show_map().get());
        //连接车辆的信号和槽
        connect(this,&frmMain::signal_send_record_id,bus_test_->bus_test(),&Bus::StartSaveGPS);
        connect(this,&frmMain::signal_send_stop,bus_test_->bus_test(),&Bus::StopSaveGPS);//
        //网络测试
        //bus_test_->UpdataPositionBySocketTest();
        bus_test_->LuShuTest();//开始路书

    }else {
        qDebug()<<"show map is empty!";
    }
    show_dialog_->show();
    //ToDo连接视频模块,因为Qt sginal原因，不能直接使用槽连接；希望下一步完成本类的槽函数
    //连接TabWidgets 和MainShowDialog 的stackWidgets
    connect(this->ui->tab_choose,SIGNAL(currentChanged(int)),this->show_dialog_->stacked_widget(),SLOT(setCurrentIndex(int)));
    //视频布局控制槽连接
    connect(this,SIGNAL(signal_change_video_1(int)),show_dialog_->video_widget(),SLOT(change_video_1(int)));
    connect(this,SIGNAL(signal_change_video_4(int)),show_dialog_->video_widget(),SLOT(change_video_4(int)));
    connect(this,SIGNAL(signal_change_video_6(int)),show_dialog_->video_widget(),SLOT(change_video_6(int)));
    connect(this,SIGNAL(signal_change_video_7(int)),show_dialog_->video_widget(),SLOT(change_video_7(int)));
    connect(this,SIGNAL(signal_change_video_12(int)),show_dialog_->video_widget(),SLOT(change_video_12(int)));

    //show_dialog_->video_review_show_widget()->resize(400,800);
    //视频回放，显示设置
    this->video_review_control()->GetPlyer()->setVideoOutput(show_dialog_->video_review_show_widget());
    //show_dialog_->video_review_show_widget()->show();
    //初始化bus
    review_bus_=new Bus(Tool::WPS84ToGCJ02(30.5563134000,103.9938400000));
    review_bus_->SetMap(show_dialog_->re_show_map().get());
    //连接信号更新的槽
    connect(video_review_control_,&Player::SendQGeoCoordinate,review_bus_,&Bus::SetCoordinate);
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
    }
    /*else if (myApp::VideoType == "13_16") {
        removelayout();
        change_video_4(12);
    }*/
    else if (myApp::VideoType == "1_6") {
        removelayout();
        change_video_6(0);
    } else if (myApp::VideoType == "7_12") {
        removelayout();
        change_video_6(6);
    }else if(myApp::VideoType=="1_7"){
        removelayout();
        change_video_7(0);
    }else if(myApp::VideoType=="6_12"){
        removelayout();
        change_video_7(5);
    } else if (myApp::VideoType == "1_12") {
        removelayout();
        change_video_12();
    }else {
        removelayout();
        change_video_4(0);
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
        QWidget::keyPressEvent(event);
        break;
    }
}
//
bool frmMain::eventFilter(QObject *obj, QEvent *event)
{
    //将其转为静态指针
    QMouseEvent *MouseEvent = static_cast<QMouseEvent *>(event);
    //设置鼠标双击事件
    if ((event->type() == QEvent::MouseButtonDblClick) &&
            (MouseEvent->buttons() == Qt::LeftButton)) {
        QLabel *labDouble = qobject_cast<QLabel *>(obj);
        if (!video_max_) {//如果通道不是最大化。实现最大化
            removelayout();//将显示的视屏移除
            video_max_ = true;//设置最大化为真
            ui->gridLayout->addWidget(labDouble,0,0);//添加窗口到布局界面
            labDouble->setVisible(true);
        } else {//已经全屏则退回原来的模式
            video_max_ = false;
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
        } else if(obj==ui->labResetScreen){
            if(myHelper::ShowMessageBoxQuesion(QStringLiteral("确定重新设置屏幕？可能需要重新设置"))==1){
                //执行bat脚本重设屏幕
                qDebug()<<"start reset screen";
                QString temp("cd /d F:/GitHub/OfflineMapTest/ScreenControl && Eyefinity.exe e0,3,2 m16,20,8,12,0,4");
                Tool::RunWindowsCommand(temp);
            };
            return true;
        }else if (MouseEvent->buttons() == Qt::RightButton) {//途观是鼠标右键的话
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
    for(int i=0;i<video_count_;++i)
    {
        ui->gridLayout->removeWidget(video_labs_.at(i));
        video_labs_.at(i)->setVisible(false);
    }
}

void frmMain::show_video_1()
{
    myApp::VideoType = "0_0";
    video_max_ = true;
    int index = 0;

    QAction *action = qobject_cast<QAction *>(sender());
    QString name = action->text();
    if (name == QStringLiteral("通道1")) {
        index = 0;
        myApp::VideoType = "0_0";
    } else if (name == QStringLiteral("通道2")) {
        index = 1;
        myApp::VideoType = "0_1";
    } else if (name == QStringLiteral("通道3")) {
        index = 2;
        myApp::VideoType = "0_2";
    } else if (name == QStringLiteral("通道4")) {
        index = 3;
        myApp::VideoType = "0_3";
    } else if (name == QStringLiteral("通道5")) {
        index = 4;
        myApp::VideoType = "0_4";
    } else if (name == QStringLiteral("通道6")) {
        index = 5;
        myApp::VideoType = "0_5";
    } else if (name == QStringLiteral("通道7")) {
        index = 6;
        myApp::VideoType = "0_6";
    } else if (name == QStringLiteral("通道8")) {
        index = 7;
        myApp::VideoType = "0_7";
    } else if (name == QStringLiteral("通道9")) {
        index = 8;
        myApp::VideoType = "0_8";
    } else if (name == QStringLiteral("通道10")) {
        index = 9;
        myApp::VideoType = "0_9";
    } else if (name == QStringLiteral("通道11")) {
        index = 10;
        myApp::VideoType = "0_10";
    } else if (name == QStringLiteral("通道12")) {
        index = 11;
        myApp::VideoType = "0_11";
    }
    if(this->video_type_!=myApp::VideoType){
        this->video_type_=myApp::VideoType;
        change_video_1(index);
        myApp::WriteConfig();
    }else {
        qDebug()<<"Is aleardy in this model ,no change need.";
    }

}

void frmMain::change_video_1(int index)
{
    if(index>=0&&index<12){
        emit signal_change_video_1(index);
        removelayout();
        video_max_=true;
        ui->gridLayout->addWidget(video_labs_.at(index),0,0);
        video_labs_.at(index)->setVisible(true);
        //更改显示窗口连接
        //show_dialog_->video_widget()->change_video_1(index);

    }else {
        qDebug()<<"Please give right input!!!";
    }

}

void frmMain::show_video_4()
{
    video_max_ = false;
    int index = 0;
    QAction *action = qobject_cast<QAction *>(sender());
    QString name = action->text();
    if (name == QStringLiteral("通道1-通道4")) {
        index = 0;
        myApp::VideoType = "1_4";
    } else if (name == QStringLiteral("通道5-通道8")) {
        index = 4;
        myApp::VideoType = "5_8";
    } else if (name == QStringLiteral("通道9-通道12")) {
        index = 8;
        myApp::VideoType = "9_12";
    }
    /*else if (name == QStringLiteral("通道13-通道16")) {
        index = 12;
        myApp::VideoType = "13_16";
    }*/
    if(this->video_type_!=myApp::VideoType){
        this->video_type_=myApp::VideoType;
        change_video_4(index);
        myApp::WriteConfig();
    }else {
        qDebug()<<"Is aleardy in this model ,no change need.";
    }
}

void frmMain::change_video_4(int index)
{
    if(index>=0&&index<9){
        //抛出信号
        emit signal_change_video_4(index);
        removelayout();
        ui->gridLayout->addWidget(video_labs_.at(index+0),0,0);
        ui->gridLayout->addWidget(video_labs_.at(index+1),0,1);
        ui->gridLayout->addWidget(video_labs_.at(index+2),1,0);
        ui->gridLayout->addWidget(video_labs_.at(index+3),1,1);
        for(int i=index;i<index+4;++i){
            video_labs_.at(i)->setVisible(true);
        }
         //show_dialog_->video_widget()->change_video_4(index);
         //qDebug()<<show_dialog_->video_widget();
    }else{
        qDebug()<<"Please give right input!!!";
    }
}
void frmMain::show_video_6()
{
    video_max_ = false;
    int index = 0;
    QAction *action = qobject_cast<QAction *>(sender());
    QString name = action->text();
    if (name == QStringLiteral("通道1-通道6")) {
        index = 0;
        myApp::VideoType = "1_6";
    } else if (name == QStringLiteral("通道7-通道12")) {
        index = 6;
        myApp::VideoType = "7_12";
    }
    /*else if (name == QStringLiteral("通道13-通道16")) {
        index = 12;
        myApp::VideoType = "13_16";
    }*/
    if(this->video_type_!=myApp::VideoType){
        this->video_type_=myApp::VideoType;
        change_video_6(index);
        myApp::WriteConfig();
    }else {
        qDebug()<<"Is aleardy in this model ,no change need.";
    }

}
void frmMain::change_video_6(int index){
    if(index>=0&&index<7){
        emit signal_change_video_6(index);
        removelayout();
        ui->gridLayout->addWidget(video_labs_.at(index+0),0,0,1,2);
        ui->gridLayout->addWidget(video_labs_.at(index+1),0,2,1,2);
        ui->gridLayout->addWidget(video_labs_.at(index+2),1,0,1,2);
        ui->gridLayout->addWidget(video_labs_.at(index+3),1,2,1,2);
        ui->gridLayout->addWidget(video_labs_.at(index+4),2,0,1,2);
        ui->gridLayout->addWidget(video_labs_.at(index+5),2,2,1,2);
        for(int i=index;i<index+6;++i){
            video_labs_.at(i)->setVisible(true);
        }
        //show_dialog_->video_widget()->change_video_6(index);

    }else{
        qDebug()<<"Please give right input!!!";
    }
}
void frmMain::show_video_7()
{
    video_max_ = false;
    int index = 0;
    QAction *action = qobject_cast<QAction *>(sender());
    QString name = action->text();
    if (name == QStringLiteral("通道1-通道7")) {
        index = 0;
        myApp::VideoType = "1_7";
    } else if (name == QStringLiteral("通道6-通道12")) {
        index = 5;
        myApp::VideoType = "6_12";
    }
    if(this->video_type_!=myApp::VideoType){
        this->video_type_=myApp::VideoType;
        change_video_7(index);
        myApp::WriteConfig();
    }else {
        qDebug()<<"Is aleardy in this model ,no change need.";
    }
}

void frmMain::change_video_7(int index)
{
    if(index>=0&&index<6){
        emit signal_change_video_7(index);
        removelayout();
        //设置布局
        ui->gridLayout->addWidget(video_labs_.at(index+0),0,0,2,3);
        ui->gridLayout->addWidget(video_labs_.at(index+1),0,3,1,1);
        ui->gridLayout->addWidget(video_labs_.at(index+2),1,3,1,1);
        ui->gridLayout->addWidget(video_labs_.at(index+3),2,3,1,1);
        ui->gridLayout->addWidget(video_labs_.at(index+4),2,0,1,1);
        ui->gridLayout->addWidget(video_labs_.at(index+5),2,1,1,1);
        ui->gridLayout->addWidget(video_labs_.at(index+6),2,2,1,1);
        for (int i = 0; i < 7; ++i) {
            video_labs_.at(index+i)->setVisible(true);
        }
         //show_dialog_->video_widget()->change_video_7(index);
    }else{
        qDebug()<<"Please give right input!!!";
    }
}
void frmMain::show_video_12()
{
    video_max_ = false;
    myApp::VideoType = "1_12";
    if(this->video_type_!=myApp::VideoType){
        this->video_type_=myApp::VideoType;
        change_video_12();
        myApp::WriteConfig();
    }else {
        qDebug()<<"Is aleardy in this model ,no change need.";
    }
}

void frmMain::change_video_12()
{
    //发射信号
    emit signal_change_video_12(0);
    //删除原有布局
    removelayout();
    //重新设置布局
    change_video(0,3,4);
    //show_dialog_->video_widget()->change_video_12(0);
}
void frmMain::change_video(int index, int v_row,int v_col)
{
    int count = 0;
    int row = 0;
    int column = 0;
    //videoMax = false;
    for (int i = index; i < video_count_; ++i) {
            ui->gridLayout->addWidget(video_labs_.at(i), row, column);
            video_labs_.at(i)->setVisible(true);
            //widgets.at(i)->VideoPlay();//播放视频
            count++;
            column++;
            //到达行界限就开始下一行
            if (column == v_col) {
                row++;
                column = 0;
            }

        if (count == (v_row * v_col)) {
            break;
        }
    }
}
QString frmMain::GetNVRID(QString NVRIP)
{
    QSqlQuery query;
    QString sql = QStringLiteral("select [NVRID] from [NVRInfo]");
    sql += " where [NVRIP]='" + NVRIP + "'";
    query.exec(sql);
    query.next();
    return query.value(0).toString();
}

void frmMain::GetRtspAddr(QString NVRID, QString IPCIP, QString &IPCRtspAddrMain, QString &IPCRtspAddrSub)
{
    QSqlQuery query;
    QString sql = QStringLiteral("select [IPCRtspAddrMain],[IPCRtspAddrSub] from [IPCInfo] where [IPCUse]='启用'");
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
//双击子树
void frmMain::on_treeMain_doubleClicked(const QModelIndex &index)
{
    qDebug()<<"double check";
    //选中的是NVR则不处理
    if (ui->treeMain->currentItem()->parent() == 0) {
        return;
    }
    //当前还没有选择通道
    if (tempLab == 0) {
        return;
    }
    qDebug()<<tempLab->text();
    //取出双击摄像机的子码流地址
    //取出NVR编号及IPCID
    QString txt = ui->treeMain->currentItem()->parent()->text(0);
    QString NVRIP = txt.split("[")[1].split("]")[0];
    QString NVRID = GetNVRID(NVRIP);
    qDebug()<<"IP :"<<NVRID;
    QString temp = ui->treeMain->currentIndex().data().toString();
    QString ipc_id= temp.split("[")[0].right(3);
    qDebug()<<"ipc_id"<<ipc_id;
    QString IPCIP = temp.split("[")[1].split("]")[0];
    //获取当前解码器序列号；

    //根据NVR编号和IP地址查询出该摄像机的子码流
    QString rtspAddr;
    QString IPCRtspAddrMain;
    QString IPCRtspAddrSub;
    GetRtspAddr(NVRID, IPCIP, IPCRtspAddrMain, IPCRtspAddrSub);
    //检查主码流类型
    rtspAddr = (myApp::RtspType == 0 ? IPCRtspAddrMain : IPCRtspAddrSub);
    qDebug()<<"rtsp adress ::"<<rtspAddr;
    //如果该摄像机不在线
//    if (!myHelper::IPCEnable(rtspAddr)) {
//        myHelper::ShowMessageBoxError(QStringLiteral("该摄像机不在线!"));
//        return;
//    }
    //获取templab的文字信息
    QString tempCH = tempLab->text();
    for (int i = 0; i < 12; i++) {
        if (video_labs_[i]->text() == tempCH) {
            ChangeRtspAddr(i, rtspAddr);
            //连接解码器和显示画面
            QSharedPointer<VideoDecodeThread> get=decode_list_.find(ipc_id).value();
            qDebug()<<get.get();

            show_dialog_->video_widget()->video_widgets().at(i)->set_decode_thread(get);
//            decode_list_.find(IPCIP).value().get()->StartDecode();
//            //设置开始存储
//            //添加新按钮控制线程的播放和显示
//            if(!get->is_save()){
//                get.get()->set_is_save(true);
//                get->set_is_save_by_time();//设置按照固定时长来写入视频数据
//            }


            //视频暂停按钮
            if(get->is_save()){
                menu8->addAction(QStringLiteral("停止播放"),get.get(),SLOT(StopDecode()));
                qDebug()<<"add ed";
            }
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

void frmMain::on_tab_choose_currentChanged(int index)
{
    if(index==2){
        aggregative_gridLayout_->removeWidget(speed_chart_widget_);
        //添加布局
        ui->treeMain->setVisible(false);//隐藏侧边面板
        aggregative_gridLayout_->addWidget(video_control_widget_,0,0,2,2);
        aggregative_gridLayout_->addWidget(map_control_widget_,0,2,3,2);
        aggregative_gridLayout_->addWidget(speed_chart_widget_,2,0,1,2);
    }else if(index==0){//选择了地图
        //地图还原
        map_vbox_layout_->addWidget(map_control_widget_);
    }else if(index==1){
        //视频控制还原
        ui->treeMain->setVisible(true);
        video_vbox_layout_->addWidget(video_control_widget_);
    }
//    aggregative_gridLayout_->update();
//    show_dialog_->stacked_widget()->update();


}

int frmMain::CreateRecord()
{
    int result=NULL;
    Tool::TestNoteTool("CreateRecord",0);
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString video_time=current_date_time.toString("yyyy-MM-dd hh:mm:ss:zzz");
    QJsonObject temp_data;
    temp_data.insert("record_time",video_time);
    temp_data.insert("car_id",1);//默认车辆编号为1
    QString request_url="http://localhost/re_save_record.php";
    QJsonObject test=Tool::NetWorkGet(request_url,temp_data);
    qDebug()<<test.size();
    qDebug()<<test.isEmpty();
    result=test.value("result").toInt();
    Tool::TestNoteTool("NetWorkGetTest",1);
    return result;
}
//开始存储数据的信号函数
void frmMain::StartSaveData()
{
    qDebug()<<"------ save data start------";
    //先创建record记录表
    this->save_record_id_=CreateRecord();
    qDebug()<<"This Record id is :"<<save_record_id_;
    //发射存储信号
    emit(signal_send_record_id(save_record_id_));
}
void frmMain::StopSaveData()
{
    //发送停止信号
    emit(signal_send_stop());
    qDebug()<<"------ save data end------";
}

void frmMain::on_pushButton_clicked()
{

}
void frmMain::on_save_data_button_clicked()
{
    //如果已经在开始录制
    if(is_save_data_)
    {
        //停止录制
        StopSaveData();
        //更改按钮
        ui->save_data_button->setText(QStringLiteral("开始录制"));
        qDebug()<<"stop save";
    }else{
        //开始录制
        StartSaveData();
        //更改按钮
        ui->save_data_button->setText(QStringLiteral("停止录制"));
        qDebug()<<"start save";
    }
    is_save_data_=!is_save_data_;
}
