#ifndef FRMINPUTBOX_H
#define FRMINPUTBOX_H

#include <QDialog>

namespace Ui
{
    class frmInputBox;
}

class frmInputBox : public QDialog
{
    Q_OBJECT

public:
    explicit frmInputBox(QWidget *parent = 0);
    ~frmInputBox();

    void SetMessage(QString title);
    QString GetValue()const {
        return value;
    }

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

private slots:
    void on_btnOk_clicked();

private:
    Ui::frmInputBox *ui;

    QPoint mousePoint;  //鼠标拖动自定义标题栏时的坐标
    bool mousePressed;  //鼠标是否按下
    void InitStyle();   //初始化无边框窗体

    QString value;
};

#endif // FRMINPUTBOX_H
