#ifndef FRMNVR_H
#define FRMNVR_H

#include <QDialog>

class QSqlQueryModel;
class QModelIndex;

namespace Ui
{
    class frmNVR;
}

class frmNVR : public QDialog
{
    Q_OBJECT

public:
    explicit frmNVR(QWidget *parent = 0);
    ~frmNVR();

private slots:
    void on_btnAdd_clicked();
    void on_btnDelete_clicked();
    void on_btnUpdate_clicked();
    void on_btnExcel_clicked();
    void on_tableMain_pressed(const QModelIndex &index);

private:
    Ui::frmNVR *ui;

    QSqlQueryModel *queryModule;

    void InitStyle();   //初始化无边框窗体
    void InitForm();    //初始化窗体数据
    void LoadNVRInfo(); //载入硬盘录像机数据

    bool IsExistNVRID(QString NVRID);
    bool IsExistNVRIP(QString NVRIP);

};

#endif // FRMNVR_H
