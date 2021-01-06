/**
 * @file busstation.h
 * @brief BusStation class inhert QDeclarativeGeoMapQuickItem;
 * @details it can be used in the QDeclarativeGeoMap to add bus station  \n
 * QT Version    5.12.2
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2018-11-7 20:48:43
 * @copyright Copyright (c) 2020  IRLSCU
 * 
 * @par 修改日志:
 * <table>
 * <tr>
 *    <th> Commit date</th>
 *    <th> Version </th> 
 *    <th> Author </th>  
 *    <th> Description </th>
 * <tr>
 *    <td> 2018-11-7 20:48:43 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 完善类 </td>
 * </tr>
 * <tr>
 *    <td> 2020-12-28 23:42:22 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td>添加文档</td>
 * </tr>
 * </table>
 * 
 * @example busstation.h
 * This is an example of how to use the BusStation class.
 * More details about this example.
 * 
 * @code{.cpp}
 * QQmlApplicationEngine engine; //load qml file
 * engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
 * Tool tool;//创建tool工具类
 * QObject *pRoot=engine.rootObjects().first();//获取qml第一个对象：
 * QDeclarativeGeoMap *qMap=pRoot->findChild<QDeclarativeGeoMap *>("maptest1"); //找到map节点
 * if(qMap!=0)
 * {
 *    QGeoCoordinate station_1=tool.WPS84ToGCJ02(30.5565134000,103.9940400000);
 *    QString station1_id="station1";
 *    qDebug()<<station1_id;
 *    BusStation *station1=new BusStation(station_1);
 *    qMap->addMapItem(station1);
 * }else
 * {
 *    qDebug("Can not get this Object");
 * }
 * @endcode 
 */
#ifndef BUSSTATION_H
#define BUSSTATION_H
#include <QtLocation/private/qdeclarativegeomapquickitem_p.h>
class QQuickImage;
class QQuickText;
/**
 * @brief 公交站抽象类，主要包含公交站点基本信息
 */
class BusStation : public QDeclarativeGeoMapQuickItem
{
public:
    /**
     * @brief Construct a new Bus Station object
     */
    explicit BusStation();
    /**
     * @brief Destroy the Bus Station object
     */
    ~BusStation();
    /**
     * @brief Construct a new Bus Station object
     * @param  coordinate      坐标点
     */
    BusStation(const QGeoCoordinate coordinate);
    /**
     * @brief Construct a new Bus Station object 二参数构造函数
     * @param  coordinate       坐标点
     * @param  station_id       站点编号
     */
    BusStation(const QGeoCoordinate coordinate,
               const QString station_id);
    /**
     * @brief Construct a new Bus Station object
     * @param  coordinate       坐标点
     * @param  station_id       站点编号
     * @param  station_name     站点名称
     */
    BusStation(const QGeoCoordinate coordinate,
               const QString station_id,
               const QString station_name);
    /**
     * @brief Construct a new Bus Station object
     * @param  coordinate       坐标点
     * @param  station_id       站点编号
     * @param  station_name     站点名称
     * @param  iocn_url         ioc路径
     */
    BusStation(const QGeoCoordinate coordinate,
               const QString station_id,
               const QString station_name,
               const QUrl iocn_url);
    /**
     * @brief Set the Bus Station Id object
     * @param  station_id       站点编号
     */
    void SetBusStationId(const QString station_id);
    /**
     * @brief  获取站点编号
     * @return QString 
     */
    QString bus_station_id();
    /**
     * @brief Set the Bus Station Name object
     * @param  station_name     站点名称
     */
    void SetBusStationName(const QString station_name);
    /**
     * @brief 获取站点名称
     * @return QString  站点名称
     */
    QString bus_station_name();
    /**
     * @brief 设置站点图标
     * @param  iocn             站点图标指针
     */
    void SetBusStationIocn(QQuickImage *iocn);
    /**
     * @brief 设置站点图标源
     * @param  source           站点图标源URL
     */
    void SetBusStationIocn(const QUrl source);
    /**
     * @brief  获取站点图标对象指针
     * @return QQuickImage* 
     */
    QQuickImage *bus_station_iocn();
    /**
     * @brief 设置显示的站点文本框
     * @param  station_information 站点文本框指针
     */
    void SetBusStationInformation(QQuickText *station_information);
    /**
     * @brief 获取站点文本框
     * @return QQuickText* 
     */
    QQuickText *bus_station_information();
    /**
     * @brief  设置图标缩放比例
     * @param  Scale            图标缩放
     */
    void SetIocnScale(double Scale);
    /**
     * @brief 初始化相关参数 
     */
    void StationInit();
    /**
     * @brief 更新数据函数
     */
    void Updata();

private:
    QString bus_station_id_;              ///< 公交站编号
    QString bus_station_name_;            ///< 公交站名称
    QQuickImage *bus_station_iocn_;       ///< 公交车站点图标指针
    QQuickText *bus_station_information_; ///< 公交车基本信息
};

#endif // BUSSTATION_H
