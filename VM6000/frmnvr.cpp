#include "frmnvr.h"
#include "ui_frmnvr.h"
#include "myhelper.h"
#include "iconhelper.h"
#include "myapp.h"
#include "excelhelper.h"

frmNVR::frmNVR(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmNVR)
{
    ui->setupUi(this);

    this->InitStyle();
    this->InitForm();
}

frmNVR::~frmNVR()
{
    delete ui;
}

void frmNVR::InitStyle()
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

void frmNVR::InitForm()
{
    for (int i = 1; i <= 255; i++) {
        QString tempNVRID;
        if (i < 10) {
            tempNVRID = QString("00000%1").arg(i);
        } else if (i < 100) {
            tempNVRID = QString("0000%1").arg(i);
        } else if (i < 1000) {
            tempNVRID = QString("000%1").arg(i);
        }
        ui->cboxNVRID->addItem(tempNVRID);
    }

    QStringList tempNVRType = myApp::NVRType.split(";");
    foreach (QString nvrType, tempNVRType) {
        if (nvrType.trimmed() != "") {
            ui->cboxNVRType->addItem(nvrType);
        }
    }

    //最后一列自动填充
    ui->tableMain->horizontalHeader()->setStretchLastSection(true);
    //奇数偶数行不同背景色
    ui->tableMain->setAlternatingRowColors(true);
    //选中整行,每次只允许选中一行
    ui->tableMain->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableMain->setSelectionMode(QAbstractItemView::SingleSelection);

    queryModule = new QSqlQueryModel(this);
    LoadNVRInfo();

    QString columnNames[8]; //列名数组
    int columnWidths[8];    //列宽数组

    //初始化表格列名和列宽
    columnNames[0] = QStringLiteral("编号");
    columnNames[1] = QStringLiteral( "名称");
    columnNames[2] = QStringLiteral("地址");
    columnNames[3] = QStringLiteral("IP地址");
    columnNames[4] = QStringLiteral("类型");
    columnNames[5] = QStringLiteral("用户名");
    columnNames[6] = QStringLiteral("密码");
    columnNames[7] = QStringLiteral("状态");

    int width = myApp::DeskWidth - 246;
    columnWidths[0] = width * 0.08;
    columnWidths[1] = width * 0.16;
    columnWidths[2] = width * 0.20;
    columnWidths[3] = width * 0.12;
    columnWidths[4] = width * 0.08;
    columnWidths[5] = width * 0.12;
    columnWidths[6] = width * 0.12;
    columnWidths[7] = width * 0.08;

    //依次设置列标题列宽
    for (int i = 0; i < 8; i++) {
        queryModule->setHeaderData(i, Qt::Horizontal, columnNames[i]);
        ui->tableMain->setColumnWidth(i, columnWidths[i]);
    }
}

void frmNVR::LoadNVRInfo()
{
    QString sql = "select * from [NVRInfo] order by [NVRID] asc";
    queryModule->setQuery(sql);
    ui->tableMain->setModel(queryModule);
}

bool frmNVR::IsExistNVRID(QString NVRID)
{
    QSqlQuery query;
    QString sql = "select [NVRID] from [NVRInfo]";
    sql += " where [NVRID]='" + NVRID + "'";
    query.exec(sql);
    return query.next();
}

bool frmNVR::IsExistNVRIP(QString NVRIP)
{
    QSqlQuery query;
    QString sql = "select [NVRIP] from [NVRInfo]";
    sql += " where [NVRIP]='" + NVRIP + "'";
    query.exec(sql);
    return query.next();
}

void frmNVR::on_btnAdd_clicked()
{
    QString NVRID = ui->cboxNVRID->currentText();
    QString NVRName = ui->txtNVRName->text();
    QString NVRAddr = ui->txtNVRAddr->text();
    QString NVRIP = ui->txtNVRIP->text();
    QString NVRType = ui->cboxNVRType->currentText();
    QString NVRUserName = ui->txtNVRUserName->text();
    QString NVRUserPwd = ui->txtNVRUserPwd->text();
    QString NVRUse = ui->cboxNVRUse->currentText();

    if (NVRName == "") {
        myHelper::ShowMessageBoxError(QStringLiteral("名称不能为空,请重新填写!"));
        ui->txtNVRName->setFocus();
        return;
    }

    if (NVRIP == "") {
        myHelper::ShowMessageBoxError(QStringLiteral("IP地址不能为空,请重新填写!"));
        ui->txtNVRIP->setFocus();
        return;
    }

    if (!myHelper::IsIP(NVRIP)) {
        myHelper::ShowMessageBoxError(QStringLiteral("IP地址不合法,请重新填写!"));
        ui->txtNVRIP->setFocus();
        return;
    }

    //检测编号和IP是否唯一
    if (IsExistNVRID(NVRID)) {
        myHelper::ShowMessageBoxError(QStringLiteral("编号已经存在,请重新选择!"));
        return;
    }

    if (IsExistNVRIP(NVRIP)) {
        myHelper::ShowMessageBoxError(QStringLiteral("IP地址已经存在,请重新填写!"));
        ui->txtNVRIP->setFocus();
        return;
    }

    QSqlQuery query;
    QString sql = "insert into [NVRInfo](";
    sql += "[NVRID],[NVRName],[NVRAddr],[NVRIP],";
    sql += "[NVRType],[NVRUserName],[NVRUserPwd],[NVRUse])";
    sql += "values('";
    sql += NVRID + "','";
    sql += NVRName + "','";
    sql += NVRAddr + "','";
    sql += NVRIP + "','";
    sql += NVRType + "','";
    sql += NVRUserName + "','";
    sql += NVRUserPwd + "','";
    sql += NVRUse + "')";
    query.exec(sql);

    LoadNVRInfo();

    ui->cboxNVRID->setCurrentIndex(ui->cboxNVRID->currentIndex() + 1);
}

void frmNVR::on_btnDelete_clicked()
{
    if (ui->tableMain->currentIndex().row() < 0) {
        myHelper::ShowMessageBoxError(QStringLiteral("请选择要删除的硬盘录像机!"));
        return;
    }

    QString tempNVRID = queryModule->record(
                            ui->tableMain->currentIndex().row())
                        .value(0).toString();

    if (tempNVRID == "000255") {
        myHelper::ShowMessageBoxError(QStringLiteral("默认NVR不能删除!"));
        return;
    }

    if (myHelper::ShowMessageBoxQuesion(QStringLiteral("确定要删除硬盘录像机吗?对应摄像机将同步删除!")) == 1) {
        QSqlQuery query;
        QString sql = "delete from [NVRInfo] where [NVRID]='" + tempNVRID + "'";
        query.exec(sql);
        myHelper::Sleep(100);

        //同步删除对应摄像机信息
        sql = "delete from [IPCInfo] where [NVRID]='" + tempNVRID + "'";
        query.exec(sql);
        myHelper::Sleep(100);

        //同步删除对应轮询表信息
        sql = "delete from [PollInfo] where [NVRID]='" + tempNVRID + "'";
        query.exec(sql);
        myHelper::Sleep(100);

        LoadNVRInfo();
    }
}

void frmNVR::on_btnUpdate_clicked()
{
    if (ui->tableMain->currentIndex().row() < 0) {
        myHelper::ShowMessageBoxError(QStringLiteral("请选择要修改的硬盘录像机!"));
        return;
    }

    //获取原有NVRID
    QString tempNVRID = queryModule->record(
                            ui->tableMain->currentIndex().row())
                        .value(0).toString();
    QString tempNVRIP = queryModule->record(
                            ui->tableMain->currentIndex().row())
                        .value(3).toString();

    if (tempNVRID == "000255") {
        myHelper::ShowMessageBoxError(QStringLiteral("默认NVR不能修改!"));
        return;
    }

    QString NVRID = ui->cboxNVRID->currentText();
    QString NVRName = ui->txtNVRName->text();
    QString NVRAddr = ui->txtNVRAddr->text();
    QString NVRIP = ui->txtNVRIP->text();
    QString NVRType = ui->cboxNVRType->currentText();
    QString NVRUserName = ui->txtNVRUserName->text();
    QString NVRUserPwd = ui->txtNVRUserPwd->text();
    QString NVRUse = ui->cboxNVRUse->currentText();

    if (NVRID != tempNVRID) {
        //检测编号是否和已经存在的除自己之外的编号相同
        if (IsExistNVRID(NVRID)) {
            myHelper::ShowMessageBoxError(QStringLiteral("编号已经存在,请重新选择!"));
            return;
        }
    }

    if (NVRIP != tempNVRIP) {
        //检测IP地址是否和已经存在的除自己之外的IP地址相同
        if (IsExistNVRIP(NVRIP)) {
            myHelper::ShowMessageBoxError(QStringLiteral("IP地址已经存在,请重新填写!"));
            ui->txtNVRIP->setFocus();
            return;
        }
    }

    if (!myHelper::IsIP(NVRIP)) {
        myHelper::ShowMessageBoxError(QStringLiteral("IP地址不合法,请重新填写!"));
        ui->txtNVRIP->setFocus();
        return;
    }

    QSqlQuery query;
    QString sql = "update [NVRInfo] set";
    sql += " [NVRID]='" + NVRID;
    sql += "',[NVRName]='" + NVRName;
    sql += "',[NVRAddr]='" + NVRAddr;
    sql += "',[NVRIP]='" + NVRIP;
    sql += "',[NVRType]='" + NVRType;
    sql += "',[NVRUserName]='" + NVRUserName;
    sql += "',[NVRUserPwd]='" + NVRUserPwd;
    sql += "',[NVRUse]='" + NVRUse;
    sql += "' where [NVRID]='" + tempNVRID + "'";
    query.exec(sql);
    myHelper::Sleep(100);

    //同步更新摄像机对应硬盘录像机信息
    sql = "update [IPCInfo] set";
    sql += " [NVRID]='" + NVRID;
    sql += "',[NVRName]='" + NVRName;
    sql += "' where [NVRID]='" + tempNVRID + "'";
    query.exec(sql);
    myHelper::Sleep(100);

    //同步更新轮询表信息
    sql = "update [PollInfo] set";
    sql += " [NVRID]='" + NVRID;
    sql += "',[NVRName]='" + NVRName;
    sql += "' where [NVRID]='" + tempNVRID + "'";
    query.exec(sql);
    myHelper::Sleep(100);

    LoadNVRInfo();
}

void frmNVR::on_btnExcel_clicked()
{
    QString columnNames[8];
    int columnWidths[8];

    columnNames[0] = QStringLiteral("编号");
    columnNames[1] = QStringLiteral("名称");
    columnNames[2] = QStringLiteral("地址");
    columnNames[3] = QStringLiteral("IP地址");
    columnNames[4] = QStringLiteral("类型");
    columnNames[5] = QStringLiteral("用户名");
    columnNames[6] = QStringLiteral("密码");
    columnNames[7] = QStringLiteral("状态");
    columnWidths[0] = 80;
    columnWidths[1] = 120;
    columnWidths[2] = 150;
    columnWidths[3] = 120;
    columnWidths[4] = 60;
    columnWidths[5] = 60;
    columnWidths[6] = 60;
    columnWidths[7] = 60;

    QStringList content;
    QSqlQuery query;
    QString sql = "select * from [NVRInfo] order by [NVRID] asc";
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
    QString title = QStringLiteral("硬盘录像机信息");
    ExcelHelper::Instance()->ToExcel(myApp::AppPath + "DB/" + title + ".xls", title, title, columnNames, columnWidths, columnCount, content);

    if (myHelper::ShowMessageBoxQuesion(QStringLiteral("导出数据到Excel成功,现在就打开吗？")) == 1) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(myApp::AppPath + "DB/" + title + ".xls"));
    }
}

void frmNVR::on_tableMain_pressed(const QModelIndex &index)
{
    QSqlRecord record = queryModule->record(index.row());
    ui->cboxNVRID->setCurrentIndex(ui->cboxNVRID->findText(record.value(0).toString()));
    ui->txtNVRName->setText(record.value(1).toString());
    ui->txtNVRAddr->setText(record.value(2).toString());
    ui->txtNVRIP->setText(record.value(3).toString());
    ui->cboxNVRType->setCurrentIndex(ui->cboxNVRType->findText(record.value(4).toString()));
    ui->txtNVRUserName->setText(record.value(5).toString());
    ui->txtNVRUserPwd->setText(record.value(6).toString());
    ui->cboxNVRUse->setCurrentIndex(ui->cboxNVRUse->findText(record.value(7).toString()));
}
