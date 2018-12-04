#ifndef QWIDGET_H
#include<QWidget>
#endif
#ifndef QWINDOW_H
#include <QWindow>
#endif
#ifndef QLIST_H
#include <QList>
#endif
#ifndef QDEBUG_H
#include <QDebug>
#endif

#include "test/screencontroltest.h"
ScreenControlTest::ScreenControlTest()
{

}
ScreenControlTest::ScreenControlTest(QDesktopWidget *desktop):m_screencontrol(desktop)
{

}
void ScreenControlTest::ConstructFunctionTest()
{
    tool.TestNoteTool("ConstructFunctionTest ",0);
    //ToDo
    if(m_screencontrol.video_player_list_.size()==m_screencontrol.video_player_list_.size()
     &&m_screencontrol.video_player_list_.size()==m_screencontrol.video_widget_list_.size())
    {
        qDebug()<<"Init test is ok";
    }
    tool.TestNoteTool("ConstructFunctionTest ",1);
}
void ScreenControlTest::SetWindowTest()
{
    tool.TestNoteTool("SetWindowTest ",0);
    QList<QWidget*> test_widget_list;
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
    tool.TestNoteTool("SetWindowTest ",1);
}
void ScreenControlTest::InitTest()
{

    tool.TestNoteTool("InitTest",0);
    m_screencontrol.Init();
    if(m_screencontrol.video_player_list_.size()==m_screencontrol.video_player_list_.size()
     &&m_screencontrol.video_player_list_.size()==m_screencontrol.video_widget_list_.size())
    {
        qDebug()<<"Init test is ok";
    }
    tool.TestNoteTool("IniTest",1);

}
void ScreenControlTest::SetModelTest()
{
    tool.TestNoteTool("SetModelTest ",0);
    int model_x=3;
    int model_y=4;
    m_screencontrol.SetModel(model_x,model_y);
    if(m_screencontrol.widget_width()==m_screencontrol.screen_width()/model_y)
    {
        qDebug()<<"This Test is OK";
    }
    tool.TestNoteTool("SetModelTest ",1);
}
void ScreenControlTest::MainTest()
{
    tool.TestNoteTool("MainTest ",0);
    //SetWindowTest();
   // InitTest();
    ConstructFunctionTest();
    SetModelTest();
    tool.TestNoteTool("MainTest ",1);
}
