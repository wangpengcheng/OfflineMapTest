#ifndef TOOL_H
#define TOOL_H
/*
 * tool一般工具类，实现所有常用工具转化
 * 王鹏程 QQ:673018396
 * 2018-10-30 10:51
 * 完整项目地址：
 * https://github.com/wangpengcheng/OfflineMapTest
*/

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


};

#endif // TOOL_H
