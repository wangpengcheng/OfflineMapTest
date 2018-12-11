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
    void MainTest();//主要测试函数
private:
    Bus *bus_test_;
    Tool tool;
};

#endif // BUSTEST_H
