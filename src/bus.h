#ifndef BUS_H
#define BUS_H
/****************************************************************************
** @projectName   OfflineMapTest
** QT Version    5.11.1
** This file is part of the OfflineMapTest project.
** @file          bus.cpp
** @brief         Bus class
** @details       实现Bus类方法，在地图上显示公交bus，并且提供网络请求接口和自动动画接口
** @author        wangpengcheng
** @QQ            673018396
** @email         wangpengcheng2018@gmail.com
** @address       https://github.com/wangpengcheng/OfflineMapTest
** @date          2018-12-10 周一  17:06:21
** @example
**
** 示例代码
**
*****************************************************************************/
#ifndef QQUICKITEM_H
#include <QQuickItem>
#endif
#ifndef  QDECLARATIVEGEOMAPQUICKITEM_H
#include <QtLocation/private/qdeclarativegeomapquickitem_p.h>
#endif
/*
 * bus 类的主要设计思路和数据类型：
 * 基本信息数据定义：
 * 1.公交车ID 2.公交车名称  3.所属线路编号 4.附加基本信息;公交驾驶员信息
 * 功能实现成员变量：
 * 1.指向地图 2.储存线路 3.公交车图标 4.信息关键点（停靠关键点） 5.小车转动角度,6.时间定时器
*/
class Bus: public QDeclarativeGeoMapQuickItem
{
public:
    Bus();
private:

};

#endif // BUS_H
