#ifndef MYREVIEWWIDGET_H
#define MYREVIEWWIDGET_H

#include <QWidget>

namespace Ui {
class MyReviewWidget;
}

class MyReviewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyReviewWidget(QWidget *parent = nullptr);
    ~MyReviewWidget();

private:
    Ui::MyReviewWidget *ui;
};

#endif // MYREVIEWWIDGET_H
