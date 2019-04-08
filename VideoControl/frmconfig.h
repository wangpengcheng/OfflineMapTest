#ifndef FRMCONFIG_H
#define FRMCONFIG_H

#include <QDialog>

namespace Ui
{
    class frmConfig;
}

class frmConfig : public QDialog
{
    Q_OBJECT

public:
    explicit frmConfig(QWidget *parent = 0);
    ~frmConfig();

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private slots:
    void on_btnOk_clicked();
    void on_btnClearNVR_clicked();
    void on_btnClearIPC_clicked();
    void on_btnClearPoll_clicked();
    void on_btnClearAll_clicked();

private:
    Ui::frmConfig *ui;

    QPoint mousePoint;  //鼠标拖动自定义标题栏时的坐标
    bool mousePressed;  //鼠标是否按下
    void InitStyle();   //初始化无边框窗体
    void InitForm();    //初始化窗体数据

};

#endif // FRMCONFIG_H
