#ifndef SCREENCONTROL_H
#define SCREENCONTROL_H

/*
 *ScreenControl 类用来控制大屏显示
 * 主要功能包括；屏幕数量统计；分辨率统计；
 * 屏幕合并和拆分；
 * 屏幕复制、指定屏幕窗口等功能
 *
 * 王鹏程 2018-11-4 16:39
 * QQ: 673018396
 * 完整项目地址：
 * https://github.com/wangpengcheng/OfflineMapTest
 *
*/

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
