
#ifndef QWIDGET_H
#include<QWidget>
#endif
#ifndef QWINDOW_H
#include <QWindow>
#endif

#ifndef QLIST_H
#include <QList>
#endif

#include <QDebug>
#include "test/screencontroltest.h"
ScreenControlTest::ScreenControlTest()
{

}
ScreenControlTest::ScreenControlTest(QDesktopWidget *desktop):m_screencontrol(desktop)
{

}
void ScreenControlTest::SetWindowTest()
{
    QList<QWidget*> test_widget_list;
    qDebug()<<"--------This test start--------";

    int temp_count=this->m_screencontrol.screen_count();
    qDebug()<<"this screen numbers  is "<<temp_count;
    for(int i=0;i<temp_count;++i)
    {
           QWidget *temp=new QWidget();
           this->m_screencontrol.SetWindowScreen(temp,i);
           QString  temp_string=QString("this screen's number is %1").arg(i);
           temp->setWindowTitle(temp_string);
           temp->resize(800,800);
           temp->show();
           qDebug()<<temp_string;
           test_widget_list.append(temp);
    }
    qDebug()<<"--------This test end--------";


}
void ScreenControlTest::initTest()
{

    tool.TestNoteTool("initTest",0);
    m_screencontrol.init();
    tool.TestNoteTool("iniTest",1);

}
