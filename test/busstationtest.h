#ifndef BUSSTATIONTEST_H
#define BUSSTATIONTEST_H

/****************************************************************************
** @projectName   OfflineMapTest
** QT Version    5.11.1
** This file is part of the OfflineMapTest project.
** @file          busttationtest.h
** @brief         BusStationTest class to test BusStation class
** @details       BusStation的测试类，完成基本函数功能的测定，但是SetText方法还未完成
**                等待BusStation类的SetText()方法完成后，再进行编写测试
** @author        wangpengcheng
** @QQ            673018396
** @email         wangpengcheng2018@gmail.com
** @address       https://github.com/wangpengcheng/OfflineMapTest
** @date          2018-11-09 周五  21:41:02
** @example
** #include<busstationtest.h>//head
** //main
** QQmlApplicationEngine engine;//add qucik
** engine.load(QUrl(QStringLiteral("qrc:/main.qml")));//load qml file
** BusStationTest test;
** test.MainTest();
** QObject *pRoot=engine.rootObjects().first(); //qt 获取qml第一个对象：
** QDeclarativeGeoMap *qMap=pRoot->findChild<QDeclarativeGeoMap *>("maptest1");//找到map节点
** if(qMap!=0)
** {
**     test.ShowTest(qMap);
** }else{
**       qDebug("Can not get this Object");
**       }
**
*****************************************************************************/

#include "src/busstation.h"
#ifndef  TOOL_H
#include "src/tool.h"
#endif
class BusStationTest
{
public:
    BusStationTest();
    ~BusStationTest();
    void ConstructFunctionTest();//构造函数测试
    void SetBusStationIdTest();//设置站点ID 测试
    void SetBusStationNameTest();//设置站点名称测试
    void SetBusStationIocnTest();//设置站点图标测试
    void SetBusStationInformationTest();//设置站点图标测试
    void SetIocnScaleTest();//图标缩放测试
    void ShowTest(QDeclarativeGeoMap *qMap);
    void MainTest();//主要测试类
    BusStation *bus_station_test_;//成员类
    Tool tool;
};

#endif // BUSSTATIONTEST_H
