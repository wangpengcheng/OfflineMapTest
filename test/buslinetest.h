#ifndef BUSLINETEST_H
#define BUSLINETEST_H
/****************************************************************************
** @projectName   OfflineMapTest
** QT Version    5.11.1
** This file is part of the OfflineMapTest project.
** @file          buslinetest.h
** @brief         BusLineTest class to test BusLine Class
** @details       Test BusLine Class
** @author        wangpengcheng
** @QQ            673018396
** @email         wangpengcheng2018@gmail.com
** @address       https://github.com/wangpengcheng/OfflineMapTest
** @date          2018-12-05 周三  20:32:44
** @example
** #include "test/buslinetest.h"//head
** //main
** QQmlApplicationEngine engine;//add qucik
** engine.load(QUrl(QStringLiteral("qrc:/main.qml")));//load qml file
** BusLineTest test;
** test.MainTest();
** QObject *pRoot=engine.rootObjects().first(); //qt 获取qml第一个对象：
** QDeclarativeGeoMap *qMap=pRoot->findChild<QDeclarativeGeoMap *>("maptest1");//找到map节点
** if(qMap!=0)
** {
**     test.ShowTest(qMap);
** }else{
**       qDebug("Can not get this Object");
** }
**
**
*****************************************************************************/
#ifndef QLIST_H
#include <QList>
#endif
#ifndef QGEOCOORDINATE_H
#include <QGeoCoordinate>
#endif
#ifndef QDECLARATIVEGEOMAP_H
#include <QtLocation/private/qdeclarativegeomap_p.h>
#endif
#include "src/busline.h"
class Tool;
class BusLineTest
{
public:
    BusLineTest();
    ~BusLineTest();
    void ConstructFunctionTest();//构造函数测试()
    void MainTest();//主要测试函数
    void AddCoordinateToList(QList<QGeoCoordinate> &temp);//添加准备数据
    void ShowTest(QDeclarativeGeoMap *qMap);//显示测试
private:
    BusLine *bus_line_;
    Tool tool;

};

#endif // BUSLINETEST_H
