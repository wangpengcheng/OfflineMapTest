/**
 * @file tool.h
 * @brief Tool class Header 
 * @details       Tool 类实现各种工具功能 \n
 * QT Version     5.11.1
 * 
 * @bug QML兼容出现问题，不能在QML中使用它提供的函数和方法
 * @todo 修复QML兼容bug,去除qml中的冗余代码
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2020-12-29 00:58:05
 * @copyright Copyright (c) 2020  IRLSCU
 * 
 * @par 修改日志:
 * <table>
 * <tr>
 *    <th> Commit date</th>
 *    <th> Version </th> 
 *    <th> Author </th>  
 *    <th> Description </th>
 * </tr>
 * <tr>
 *    <td> 2018-10-30 18:21:11 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 完成类的基本功能 </td>
 * </tr>
 * <tr>
 *    <td> 2020-12-29 00:58:05 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 添加注释文档 </td>
 * </tr>
 * </table>
 * 
 * @example
 * 详见 test/tool_test.cpp 文件中的ToolTest类使用方法
 */
#ifndef TOOL_H
#define TOOL_H

#include <QtPositioning>
#include <QLocation>
#include <QGeoCoordinate>
#include <QtMath>
#include <QDebug>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <math.h>

#define DELETE_OBJECT(obj)                 \
    {                                      \
        if (obj != nullptr)                \
        {                                  \
            delete obj;                    \
            obj = nullptr;                 \
            qDebug() << obj << " deleted"; \
        }                                  \
    }

#define DELETE_QOBJECT(obj)                \
    {                                      \
        if (obj && obj->parent())          \
        {                                  \
            delete obj;                    \
            obj = nullptr;                 \
            qDebug() << obj << " deleted"; \
        }                                  \
    }
/**
 * @brief 基本工具类
 */
class Tool : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Tool object
     * @param  parent           节点的父类指针
     */
    explicit Tool(QObject *parent = nullptr);
    /**
     * @brief Destroy the Tool object
     */
    ~Tool();
    /**
     * @brief 将经度转换为弧度制
     * @param  x                想对球面二维坐标x
     * @param  y                相对球面二维坐标y
     * @return double           常用值 
     */
    Q_INVOKABLE static double TransfromLatToDouble(double x, double y);
    /**
     * @brief 将维度转换为数值
     * @param  x                想对球面二维坐标x
     * @param  y                相对球面二维坐标y
     *  @return double          常用值 
     */
    Q_INVOKABLE static double TransfromLonToDouble(double x, double y);
    /**
     * @brief 转换坐标系到星火坐标系 
     * @details 即将设置经纬度坐标偏差将wps84坐标设置为GGJ02坐标体系中国 
     * @param  lat              经度
     * @param  lon              纬度
     * @return QGeoCoordinate   相对坐标
     */
    Q_INVOKABLE static QGeoCoordinate WPS84ToGCJ02(double lat, double lon);
    /**
     * @brief 转换坐标系到星火坐标系 
     * @param  temp             QGeoCoordinate 坐标数值
     * @return QGeoCoordinate   转换后的坐标数值
     */
    Q_INVOKABLE static QGeoCoordinate WPS84ToGCJ02FromCoord(QGeoCoordinate temp);
    /**
     * @brief  计算地球坐标两点之间距离
     * @param  point1           点1
     * @param  point2           点2
     * @return double           最终的精确距离 
     */
    Q_INVOKABLE static double GetDistance(QGeoCoordinate point1, QGeoCoordinate point2);
    /**
     * @brief 测试信息工具类 
     * @param  TestName         名称
     * @param  i                选择模式1-start，2-end
     */
    Q_INVOKABLE static void TestNoteTool(const QString TestName,
                                         const int i);
    /**
     * @brief  创建文件函数
     * @param  director_name    文件夹名字
     * @param  file_name        文件名称
     * @param  file_type        文件后缀
     * @return QString          文件路径
     */
    static QString CreatFile(QString director_name,
                             QString file_name,
                             QString file_type);
    /**
     * @brief  Json 请求同步函数，通过线程阻塞实现，json的同步请求。
     * @param  url              传输的地址
     * @param  send_data        请求的数据
     * @return QJsonObject      最终获取的数据
     */
    static QJsonObject NetWorkGet(QString url,
                                  QJsonObject send_data);
    /**
     * @brief  windows命令执行函数，主要是为了执行 ScreenControl中的脚本
     * @param  command          命令文件夹路径
     */
    static void RunWindowsCommand(QString command);
};

#endif // TOOL_H
