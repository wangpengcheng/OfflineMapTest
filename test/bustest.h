#ifndef BUSTEST_H
#define BUSTEST_H
/****************************************************************************
** @projectName   OfflineMapTest
** QT Version    5.11.1
** This file is part of the OfflineMapTest project.
** @file          bustest.h
** @brief         bus 类的测试类
** @details       测试bus对应类和方法
** @author        wangpengcheng
** @QQ            673018396
** @email         wangpengcheng2018@gmail.com
** @address       https://github.com/wangpengcheng/OfflineMapTest
** @date          2018-12-10 周一  21:54:47
** @example
**
** 示例代码
**    //找到qml中的map节点
**  QDeclarativeGeoMap *qMap=pRoot->findChild<QDeclarativeGeoMap *>("maptest1");
**  BusTest bus_test;
**  bus_test.ShowTest(qMap);
**  bus_test.MoveTest();
**  bus_test.UpdataPositionTest();
**  bus_test.LuShuTest();
**  bus_test.ChangePathTest();
**
*****************************************************************************/
#ifndef QDECLARATIVEGEOMAP_H
#include <QtLocation/private/qdeclarativegeomap_p.h>
#endif
#ifndef TOOL_H
#include "src/tool.h"
#endif
class Bus;
class BusTest
{
public:
    BusTest();
    ~BusTest();
    void ShowTest(QDeclarativeGeoMap *qMap);//显示测试函数
    void MoveTest();//移动测试
    void UpdataPositionTest();//网络更新位置测试
    void UpdataPositionBySocketTest();//socket更新网络测试
    void SaveCoordinateToSqlTest();//数据坐标存储测试
    void LuShuTest();//路书测试
    void ChangePathTest();//路径变换测试
    void AddCoordinateToList(QList<QGeoCoordinate> &temp);//添加路径关键点
    void MainTest();//主要测试函数
    inline Bus* bus_test(){return this->bus_test_;}
private:
    Bus *bus_test_;
    Tool tool;
};

#endif // BUSTEST_H
