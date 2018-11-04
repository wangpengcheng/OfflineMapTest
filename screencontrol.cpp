#include "screencontrol.h"


#ifndef QLIST_H
#include <QList>
#endif
#ifndef QDESKTOPWIDGET_H
#include <QDesktopWidget>
#endif

ScreenControl::ScreenControl()
{

}
ScreenControl::ScreenControl(QDesktopWidget *desktop)
{
    m_desktop=desktop;
    m_screen_count=desktop->screenCount();
}

int ScreenControl::screen_count()
{
    return this->m_screen_count;
}

QDesktopWidget* ScreenControl::desktop()
{
    return this->m_desktop;
}

void ScreenControl::SetWindowScreen(QWidget *widget,const int screen_number)
{
   // QRect temp=m_desktop->screenGeometry(screen_number);
    widget->setGeometry(this->desktop()->screenGeometry(screen_number));
}
