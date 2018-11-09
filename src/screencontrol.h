#ifndef SCREENCONTROL_H
#define SCREENCONTROL_H

/****************************************************************************
** @projectName   OfflineMapTest
** QT Version     5.11.1
** This file is part of the OfflineMapTest project.
** @file          screencontrol.h
** @brief         ScreenControl class to control the big screen
** @details       主要功能包括；屏幕数量统计；分辨率统计；
**                屏幕合并和拆分；
**                屏幕复制、指定屏幕窗口等功能
** @author        wangpengcheng
** @QQ            673018396
** @email         wangpengcheng2018@gmail.com
** @address       https://github.com/wangpengcheng/OfflineMapTest
** @date          2018-11-09 周五  18:18:07
** @example
**
** 详见test/screencontroltest.h 中的ScreenControlTest 类
**
** QT Version    5.11.1
*****************************************************************************/

class QDesktopWidget;
class QWidget;
class ScreenControl
{
public:
    ScreenControl();
    ScreenControl(QDesktopWidget *desktop);
    QDesktopWidget* desktop();
    int screen_count();
    void SetWindowScreen(QWidget * widget,
                         const int screen_number);//设置窗口所在屏幕
    QDesktopWidget* m_desktop;//desktop硬件

private:
    int m_screen_count;//屏幕总数

};

#endif // SCREENCONTROL_H
