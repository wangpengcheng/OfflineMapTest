#include "myreviewwidget.h"
#include "ui_myreviewwidget.h"

MyReviewWidget::MyReviewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyReviewWidget)
{
    ui->setupUi(this);
}

MyReviewWidget::~MyReviewWidget()
{
    delete ui;
}
