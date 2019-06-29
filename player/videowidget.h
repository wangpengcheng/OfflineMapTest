#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H
/****************************************************************************
** @projectName   OfflineMapTest
** QT Version    5.11.1-5.12.3
** This file is part of the OfflineMapTest project.
** @file          videowidget.h
** @brief         VideoWidget 类 头文件
** @details       Play类的显示关键元素，已经弃用
** @author        wangpengcheng
** @QQ            673018396
** @email         wangpengcheng2018@gmail.com
** @address       https://github.com/wangpengcheng/OfflineMapTest
** @date          2019-06-29 周六  18:53:15
** @example
**
** 示例代码
**
*****************************************************************************/
#include <QVideoWidget>

class VideoWidget : public QVideoWidget
{
    Q_OBJECT

public:
    explicit VideoWidget(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // VIDEOWIDGET_H
