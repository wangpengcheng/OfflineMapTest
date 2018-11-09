#ifndef TOOL_H
#define TOOL_H
/****************************************************************************
** @projectName   OfflineMapTest
** QT Version     5.11.1
** This file is part of the OfflineMapTest project.
** @file          tool.h
** @brief         Tool class
** @details       Tool 类实现各种工具功能
** @author        wangpengcheng
** @QQ            673018396
** @email         wangpengcheng2018@gmail.com
** @address       https://github.com/wangpengcheng/OfflineMapTest
** @date          2018-10-30 周二  18:21:11
** @example
**
** 详见test/tool_test.h文件中的ToolTest类使用方法
**
*****************************************************************************/
#include <QObject>
class QGeoCoordinate;
class Tool: public QObject
{
    Q_OBJECT
    public:
        Tool();
        Tool(const Tool &temp);
       // ~Tool();
        double TransfromLatToDouble(double x,double y);
        double TransfromLonToDouble(double x,double y);
        QGeoCoordinate WPS84ToGCJ02(double lat, double lon);
        //测试信息工具类
        void TestNoteTool(const QString TestName,
                           const int i);//选择模式1-start，2-end


};

#endif // TOOL_H
