#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QtPlugin>
#include <QDebug>
#include <QDir>
#include <QWidget>
#include <QDesktopWidget>
#include <QDialog>
#include <QtLocation/private/qdeclarativegeomap_p.h>
#include <QtLocation/private/qdeclarativecirclemapitem_p.h>
/*
 * tool 测试类
 *
 * #include "tool.h"
 * #include "test/tool_test.h"
*/
#include "screencontrol.h"
#include "test/screencontroltest.h"

int main(int argc, char *argv[])
{

    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);
    //get file path
    QString runPath = QCoreApplication::applicationFilePath();
    qDebug()<<runPath;
    qDebug()<<QDir::currentPath();
    /*
    //use Plugin
    Q_IMPORT_PLUGIN(GeoServiceProviderFactory);
    //add qucik
    QQmlApplicationEngine engine;
    //load qml file
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    */
    //获取当前硬件控件
    QDesktopWidget *desktop=QApplication::desktop();
    //创建测试类
   // ScreenControlTest1  kao;
    //测试窗口
    // kao.m_screencontrol;

  //  QRect result=desktop->screenGeometry();
   // qDebug()<<result.width();
    qDebug()<<"--------This test start--------";

    int temp_count=desktop->screenCount();
    qDebug()<<"this screen numbers  is "<<temp_count;
    for(int i=0;i<temp_count;++i)
    {
           QWidget *temp=new QWidget();
           temp->setGeometry(desktop->screenGeometry(i));
           QString  temp_string=QString("this screen's number is %1").arg(i);
           temp->setWindowTitle(temp_string);
           temp->resize(500,600);
         //  temp->move(500,500);
           temp->show();
           qDebug()<<temp_string;
    }
    qDebug()<<"--------This test end--------";

    return app.exec();

}

