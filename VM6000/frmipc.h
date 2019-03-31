#ifndef FRMIPC_H
#define FRMIPC_H

#include <QDialog>

class QSqlQueryModel;
class QModelIndex;

namespace Ui
{
    class frmIPC;
}

class frmIPC : public QDialog
{
    Q_OBJECT

public:
    explicit frmIPC(QWidget *parent = 0);
    ~frmIPC();

private slots:
    void on_btnAdd_clicked();
    void on_btnDelete_clicked();
    void on_btnUpdate_clicked();
    void on_btnExcel_clicked();
    void on_tableMain_pressed(const QModelIndex &index);
    void on_cboxNVRID_activated(const QString &arg1);
    void on_txtIPCRtspAddrMain_textChanged(const QString &arg1);
    void on_cboxIPCID_activated(const QString &arg1);

private:
    Ui::frmIPC *ui;

    QSqlQueryModel *queryModule;

    void InitStyle();   //初始化无边框窗体
    void InitForm();    //初始化窗体数据
    void LoadIPCInfo(); //载入网络摄像机数据
    void BindNVRID();   //绑定NVR编号到下拉框

    bool IsExistIPCID(QString NVRID, QString IPCID);
    QString GetNVRName(QString NVRID);

};

#endif // FRMIPC_H
