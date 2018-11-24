#include "tool.h"

#ifndef QT_QTPOSITIONING_MODULE_H
#include <QtPositioning>
#endif

#ifndef  QLOCATION_H
#include <QLocation>
#endif

#ifndef QGEOCOORDINATE_H
#include <QGeoCoordinate>
#endif

#ifndef QMATH_H
#include <QtMath>
#endif
#ifndef QDEBUG_H
#include <QDebug>
#endif
Tool::Tool(QObject *parent)//:QObject(nullptr)
{

}

/*
 * 将经纬度映射到瓦片坐标体系，
 * 即将设置经纬度坐标偏差将wps84坐标设置为GGJ02坐标体系中国
 * 模块开始
 * mondel start
 */
/*定义基本常量*/
const long long  pi =3.1415926535897932384626;
const long long  a =6378245.0;
const long long  ee=0.00669342162296594323;

//将纬度lat转换为常用度数
double Tool::TransfromLatToDouble(const double x,
                                  const double y)
{
    double temp_result=0;
    temp_result += -100.0 + 2.0 * x + 3.0 * y + 0.2 * y * y + 0.1 * x * y + 0.2 * qSqrt(qAbs(x));
    temp_result += (20.0 *  qSin(6.0 * x * pi) + 20.0 * qSin(2.0 * x * pi)) * 2.0 / 3.0;
    temp_result += (20.0 * qSin(y * pi) + 40.0 * qSin(y / 3.0 * pi)) * 2.0 / 3.0;
    temp_result += (160.0 * qSin(y / 12.0 * pi) + 320 * qSin(y * pi / 30.0)) * 2.0 / 3.0;
    return temp_result;
}

//将经度转化为常用度数
double Tool::TransfromLonToDouble(const double x,
                                  const double y)
{
    double temp_result;
    temp_result = 300.0 + x + 2.0 * y + 0.1 * x * x + 0.1 * x * y + 0.1 * qSqrt(qAbs(x));
    temp_result += (20.0 * qSin(6.0 * x * pi) + 20.0 * qSin(2.0 * x * pi)) * 2.0 / 3.0;
    temp_result += (20.0 * qSin(x * pi) + 40.0 * qSin(x / 3.0 * pi)) * 2.0 / 3.0;
    temp_result += (150.0 * qSin(x / 12.0 * pi) + 300.0 * qSin(x / 30.0 * pi)) * 2.0 / 3.0;
    return temp_result;
}

//对GPS坐标做处理，Wps84转Gcj-02
QGeoCoordinate Tool::WPS84ToGCJ02(const double lat,
                                  const double lon)
{

    double dLat,dLon,radLat,magic,sqrtMagic,mgLat, mgLon;
    dLat = TransfromLatToDouble(lon - 105.0, lat - 35.0);
    dLon = TransfromLonToDouble(lon - 105.0, lat - 35.0);
    radLat = lat/(180.0) * pi;
    magic = qSin(radLat);
    magic = 1 - ee*magic* magic;
    sqrtMagic = qSqrt(magic);
    dLat = (dLat*180.0)/((a*(1 - ee))/(magic*sqrtMagic)*pi);
    dLon = (dLon * 180.0) / (a / sqrtMagic * qCos(radLat) * pi);
    mgLat = lat + dLat;
    mgLon = lon + dLon;
    QGeoCoordinate result(mgLat, mgLon);
    return  result;
}
/*
 * 地图经纬度坐标转换
 * 模块结束
 *mondel start
 */

/*测试工具模块开始*/
/*测试提示*/
void Tool::TestNoteTool(const QString TestName,
                         const int i)
{
    if(i==0)
    {
        qDebug()<<QString("----------This %1 test Start----------").arg(TestName);
    }else if (i==1) {
        qDebug()<<QString("----------This %1 test End  ----------").arg(TestName);
    }else {
        qDebug()<<"Please input the right option";
    }

}
