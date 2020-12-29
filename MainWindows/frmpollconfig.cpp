#include "frmpollconfig.h"
#include "ui_frmpollconfig.h"
#include "myhelper.h"
#include "iconhelper.h"
#include "myapp.h"
#include "excelhelper.h"

frmPollConfig::frmPollConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmPollConfig)
{
    ui->setupUi(this);

    this->InitStyle();
    this->InitForm();
    this->LoadNVRIPC();
    this->LoadPollInfo();
}

frmPollConfig::~frmPollConfig()
{
    delete ui;
}

void frmPollConfig::InitStyle()
{
    this->setProperty("Form", true);
    this->setGeometry(qApp->desktop()->availableGeometry());
    //设置窗体标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint |
                         Qt::WindowSystemMenuHint |
                         Qt::WindowMinMaxButtonsHint);
    //设置图形字体
    IconHelper::Instance()->SetIcon(ui->lab_Ico, QChar(0xf03d), 11);
    IconHelper::Instance()->SetIcon(ui->btnMenu_Close, QChar(0xf00d), 10);
    //关联关闭按钮
    connect(ui->btnMenu_Close, SIGNAL(clicked()), this, SLOT(close()));
}

void frmPollConfig::InitForm()
{
    ui->treeMain->header()->setVisible(false);
    ui->treeMain->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //最后一列自动填充
    ui->tableMain->horizontalHeader()->setStretchLastSection(true);
    //奇数偶数行不同背景色
    ui->tableMain->setAlternatingRowColors(true);
    //选中整行,每次只允许选中一行
    ui->tableMain->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableMain->setSelectionMode(QAbstractItemView::SingleSelection);

    queryModule = new QSqlQueryModel(this);
    LoadPollInfo();

    QString columnNames[6]; //列名数组
    int columnWidths[6];    //列宽数组

    //初始化表格列名和列宽
    columnNames[0] = QStringLiteral("编号");
    columnNames[1] = QStringLiteral("名称");
    columnNames[2] = QStringLiteral("NVR编号");
    columnNames[3] = QStringLiteral("NVR名称");
    columnNames[4] = QStringLiteral("主码流地址");
    columnNames[5] = QStringLiteral("子码流地址");

    int width = myApp::DeskWidth - 246;
    columnWidths[0] = width * 0.06;
    columnWidths[1] = width * 0.11;
    columnWidths[2] = width * 0.08;
    columnWidths[3] = width * 0.11;
    columnWidths[4] = width * 0.23;
    columnWidths[5] = width * 0.23;

    //依次设置列标题列宽
    for (int i = 0; i < 6; i++) {
        queryModule->setHeaderData(i, Qt::Horizontal, columnNames[i]);
        ui->tableMain->setColumnWidth(i, columnWidths[i]);
    }
}

void frmPollConfig::LoadNVRIPC()
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

        //查询没有添加在轮询表中的摄像机信息
        QSqlQuery queryIPC;
        QString sqlIPC = "select [IPCID],[IPCName],[IPCRtspAddrMain] from [IPCInfo]";
        sqlIPC += " where [NVRID]='" + tempNVRID;
        sqlIPC += "' and [IPCUse]='启用'";
        sqlIPC += " order by [IPCID] asc";
        queryIPC.exec(sqlIPC);

        while (queryIPC.next()) {
            QString tempIPCID = queryIPC.value(0).toString();

            //如果该摄像机已经存在轮询表,则跳过
            if (IsExistIPCID(tempIPCID)) {
                continue;
            }

            QString tempIPCName = queryIPC.value(1).toString();
            QString rtspAddr = queryIPC.value(2).toString();

            QStringList temp = rtspAddr.split("/");
            QString ip = temp[2].split(":")[0];

            temp = QStringList(QString(tempIPCName + "[" + ip + "](" + tempIPCID + ")"));
            QTreeWidgetItem *itemIPC = new QTreeWidgetItem(itemNVR, temp);
            itemIPC->setIcon(0, QIcon(":/image/ipc_normal.png"));
            itemNVR->addChild(itemIPC);
        }
    }
    ui->treeMain->expandAll();
}

void frmPollConfig::LoadPollInfo()
{
    QString sql = "select * from [PollInfo]";
    queryModule->setQuery(sql);
    ui->tableMain->setModel(queryModule);
}

QString frmPollConfig::GetNVRID(QString NVRIP)
{
    QSqlQuery query;
    QString sql = "select [NVRID] from [NVRInfo]";
    sql += " where [NVRIP]='" + NVRIP + "'";
    query.exec(sql);
    query.next();
    return query.value(0).toString();
}

bool frmPollConfig::IsExistIPCID(QString IPCID)
{
    QSqlQuery query;
    QString sql = "select [IPCID] from [PollInfo]";
    sql += " where [IPCID]='" + IPCID + "'";
    query.exec(sql);
    return query.next();
}

void frmPollConfig::GetIPCInfo(QString NVRID, QString IPCID, QString &IPCName,
                               QString &IPCRtspAddrMain, QString &IPCRtspAddrSub)
{
    QSqlQuery query;
    QString sql = "select [IPCName],[IPCRtspAddrMain],[IPCRtspAddrSub]";
    sql += " from [IPCInfo] where [IPCID]='" + IPCID;
    sql += "' and [IPCUse]='启用'";
    sql += " and [NVRID]='" + NVRID + "'";
    query.exec(sql);
    query.next();
    IPCName = query.value(0).toString();
    IPCRtspAddrMain = query.value(1).toString();
    IPCRtspAddrSub = query.value(2).toString();
}

void frmPollConfig::GetIPCInfo(QString NVRID, QStringList &IPCID, QStringList &IPCName, QStringList &IPCRtspAddrMain, QStringList &IPCRtspAddrSub)
{
    QSqlQuery query;
    QString sql = "select [IPCID],[IPCName],[IPCRtspAddrMain],[IPCRtspAddrSub]";
    sql += " from [IPCInfo] where [NVRID]='" + NVRID;
    sql += "' and [IPCUse]='启用'";
    query.exec(sql);
    while(query.next()) {
        QString tempIPCID = query.value(0).toString();

        //如果该摄像机已经存在轮询表,则跳过
        if (IsExistIPCID(tempIPCID)) {
            continue;
        }

        IPCID << tempIPCID;
        IPCName << query.value(1).toString();
        IPCRtspAddrMain << query.value(2).toString();
        IPCRtspAddrSub << query.value(3).toString();
    }
}

void frmPollConfig::GetIPCInfo(QStringList &IPCID, QStringList &IPCName,
                               QStringList &NVRID, QStringList &NVRName,
                               QStringList &IPCRtspAddrMain, QStringList &IPCRtspAddrSub)
{
    QSqlQuery query;
    QString sql = "select [IPCID],[IPCName],[NVRID],[NVRName],[IPCRtspAddrMain],[IPCRtspAddrSub]";
    sql += " from [IPCInfo] where [IPCUse]='启用'";
    query.exec(sql);
    while(query.next()) {
        QString tempIPCID = query.value(0).toString();

        //如果该摄像机已经存在轮询表,则跳过
        if (IsExistIPCID(tempIPCID)) {
            continue;
        }

        IPCID << tempIPCID;
        IPCName << query.value(1).toString();
        NVRID << query.value(2).toString();
        NVRName << query.value(3).toString();
        IPCRtspAddrMain << query.value(4).toString();
        IPCRtspAddrSub << query.value(5).toString();
    }
}

void frmPollConfig::AddPollInfo(QString IPCID, QString IPCName,
                                QString NVRID, QString NVRName,
                                QString IPCRtspAddrMain, QString IPCRtspAddrSub)
{
    QSqlQuery query;
    QString sql = "insert into [PollInfo](";
    sql += "[IPCID],[IPCName],[NVRID],[NVRName],[IPCRtspAddrMain],[IPCRtspAddrSub])";
    sql += "values('";
    sql += QString("%1").arg(IPCID) + "','";
    sql += QString("%1").arg(IPCName) + "','";
    sql += QString("%1").arg(NVRID) + "','";
    sql += QString("%1").arg(NVRName) + "','";
    sql += QString("%1").arg(IPCRtspAddrMain) + "','";
    sql += QString("%1").arg(IPCRtspAddrSub) + "')";
    query.exec(sql);
}

void frmPollConfig::on_btnAddOne_clicked()
{
    QString temp = ui->treeMain->currentIndex().data().toString();
    if (temp == "") {
        myHelper::ShowMessageBoxError(QStringLiteral("请选择要添加的摄像机!"));
        return;
    }

    //判断选择的是NVR还是IPC,NVR的话则将该NVR的所有IPC添加过去
    if (ui->treeMain->currentItem()->parent() == 0) {
        //如果该NVR没有摄像机,则无需添加
        if (ui->treeMain->currentItem()->childCount() == 0) {
            return;
        }
        //选择的是NVR,将该NVR下的所有IPC添加过去
        //取出该NVR的IP地址,查询出该NVR的编号,查询出NVR下的所有IPC
        QString NVRIP = temp.split("[")[1].split("]")[0];
        QString NVRName = temp.split("[")[0];
        QString NVRID = GetNVRID(NVRIP);

        QStringList IPCID;
        QStringList IPCName;
        QStringList IPCRtspAddrMain;
        QStringList IPCRtspAddrSub;
        GetIPCInfo(NVRID, IPCID, IPCName, IPCRtspAddrMain, IPCRtspAddrSub);

        //启用事务机制加快添加速度,循环添加摄像机信息到轮询表
        QSqlDatabase::database().transaction();
        for(int i = 0; i < IPCID.count(); i++) {
            AddPollInfo(IPCID[i], IPCName[i], NVRID, NVRName, IPCRtspAddrMain[i], IPCRtspAddrSub[i]);
        }
        QSqlDatabase::database().commit();
    } else {
        //取出NVR编号及IPCID
        QString txt = ui->treeMain->currentItem()->parent()->text(0);
        QString NVRIP = txt.split("[")[1].split("]")[0];
        QString NVRName = txt.split("[")[0];
        QString NVRID = GetNVRID(NVRIP);
        QString IPCID = temp.split("(")[1].split(")")[0];
        QString IPCName;
        QString IPCRtspAddrMain;
        QString IPCRtspAddrSub;
        GetIPCInfo(NVRID, IPCID, IPCName, IPCRtspAddrMain, IPCRtspAddrSub);
        AddPollInfo(IPCID, IPCName, NVRID, NVRName, IPCRtspAddrMain, IPCRtspAddrSub);
    }

    LoadNVRIPC();
    LoadPollInfo();
}

void frmPollConfig::on_btnAddAll_clicked()
{
    QStringList IPCID;
    QStringList IPCName;
    QStringList NVRID;
    QStringList NVRName;
    QStringList IPCRtspAddrMain;
    QStringList IPCRtspAddrSub;
    GetIPCInfo(IPCID, IPCName, NVRID, NVRName, IPCRtspAddrMain, IPCRtspAddrSub);

    QSqlDatabase::database().transaction();
    for (int i = 0; i < IPCID.count(); i++) {
        AddPollInfo(IPCID[i], IPCName[i], NVRID[i], NVRName[i], IPCRtspAddrMain[i], IPCRtspAddrSub[i]);
    }
    QSqlDatabase::database().commit();

    LoadNVRIPC();
    LoadPollInfo();
}

void frmPollConfig::on_btnRemoveOne_clicked()
{
    QString tempIPCID = queryModule->record(
                            ui->tableMain->currentIndex().row())
                        .value(0).toString();
    QSqlQuery query;
    QString sql = "delete from [PollInfo] where [IPCID]='" + tempIPCID + "'";
    query.exec(sql);

    LoadNVRIPC();
    LoadPollInfo();
}

void frmPollConfig::on_btnRemoveAll_clicked()
{
    QSqlQuery query;
    QString sql = "delete from [PollInfo]";
    query.exec(sql);

    LoadNVRIPC();
    LoadPollInfo();
}

void frmPollConfig::on_btnExcel_clicked()
{
    QString columnNames[6];
    int columnWidths[6];

    columnNames[0] = QStringLiteral("编号");
    columnNames[1] = QStringLiteral("名称");
    columnNames[2] = QStringLiteral("NVR编号");
    columnNames[3] = QStringLiteral("NVR名称");
    columnNames[4] = QStringLiteral("主码流地址");
    columnNames[5] = QStringLiteral("子码流地址");

    columnWidths[0] = 80;
    columnWidths[1] = 120;
    columnWidths[2] = 80;
    columnWidths[3] = 120;
    columnWidths[4] = 200;
    columnWidths[5] = 200;

    QStringList content;
    QSqlQuery query;
    QString sql = "select * from [PollInfo] order by [IPCID] asc";
    query.exec(sql);
    int columnCount = query.record().count();

    //循环遍历数据,存储到QStringList中
    while (query.next()) {
        QString temp = "";
        for (int i = 0; i < columnCount; i++) {
            temp += query.value(i).toString() + ";";
        }
        content << temp.mid(0, temp.length() - 1); //去掉末尾的分号
    }

    //调用导出数据函数
    QString title = QStringLiteral("轮询摄像机信息");
    ExcelHelper::Instance()->ToExcel(myApp::AppPath + "DB/" + title + ".xls", title, title, columnNames, columnWidths, columnCount, content);

    if (myHelper::ShowMessageBoxQuesion(QStringLiteral("导出数据到Excel成功,现在就打开吗？")) == 1) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(myApp::AppPath + "DB/" + title + ".xls"));
    }
}

void frmPollConfig::on_treeMain_doubleClicked(const QModelIndex &index)
{
    this->on_btnAddOne_clicked();
}

void frmPollConfig::on_tableMain_doubleClicked(const QModelIndex &index)
{
    this->on_btnRemoveOne_clicked();
}
