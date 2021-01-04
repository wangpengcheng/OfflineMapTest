
#include<QWidget>
#include <QWindow>
#include <QList>
#include <QDebug>


#include "test/screencontroltest.h"
ScreenControlTest::ScreenControlTest()
{

}
ScreenControlTest::ScreenControlTest(QDesktopWidget *desktop):m_screencontrol(desktop)
{

}
void ScreenControlTest::ConstructFunctionTest()
{
    Tool::TestNoteTool("ConstructFunctionTest ",0);
    //ToDo
    if(m_screencontrol.video_player_list_.size()==m_screencontrol.video_player_list_.size()
     &&m_screencontrol.video_player_list_.size()==m_screencontrol.video_widget_list_.size())
    {
        qDebug()<<"Init test is ok";
    }
    Tool::TestNoteTool("ConstructFunctionTest ",1);
}
void ScreenControlTest::SetWindowTest()
{
    Tool::TestNoteTool("SetWindowTest ",0);
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
    Tool::TestNoteTool("SetWindowTest ",1);
}
void ScreenControlTest::InitTest()
{

    Tool::TestNoteTool("InitTest",0);
    m_screencontrol.Init();
    if(m_screencontrol.video_player_list_.size()==m_screencontrol.video_player_list_.size()
     &&m_screencontrol.video_player_list_.size()==m_screencontrol.video_widget_list_.size())
    {
        qDebug()<<"Init test is ok";
    }
    Tool::TestNoteTool("IniTest",1);

}
void ScreenControlTest::SetModelTest()
{
    Tool::TestNoteTool("SetModelTest ",0);
    int model_x=3;
    int model_y=4;
    m_screencontrol.SetModel(model_x,model_y);
    if(m_screencontrol.widget_width()==m_screencontrol.screen_width()/model_y)
    {
        qDebug()<<"This Test is OK";
    }
    Tool::TestNoteTool("SetModelTest ",1);
}
void ScreenControlTest::MainTest()
{
    Tool::TestNoteTool("MainTest ",0);
    //SetWindowTest();
   // InitTest();
    ConstructFunctionTest();
    SetModelTest();
    Tool::TestNoteTool("MainTest ",1);
}
