#ifndef MAPCONTRLCONNECT_H
#define MAPCONTRLCONNECT_H
/****************************************************************************
** @projectName   OfflineMapTest
** QT Version    5.12.2
** This file is part of the OfflineMapTest project.
** @file          mapcontrolconnect.h
** @brief         MapControlConnect 控制类头文件
** @details       主要功能是连接和同步，两个地图之间的操作；主要运用是智能指针
** @author        wangpengcheng
** @QQ            673018396
** @email         wangpengcheng2018@gmail.com
** @address       https://github.com/wangpengcheng/OfflineMapTest
** @date          2019-03-31 周日  22:12:19
** @example
**
** 示例代码
**
**  MapContrlConnect map_connect(qMap,control_map);
**
*****************************************************************************/
#include <QObject>
#include <QtLocation/private/qdeclarativegeomap_p.h>
#include <iostream>
#include <memory>
class MapContrlConnect : public QObject
{
    Q_OBJECT
public:
    MapContrlConnect();

    MapContrlConnect(std::shared_ptr<QDeclarativeGeoMap> show_map,
                     std::shared_ptr<QDeclarativeGeoMap> control_map);
    ~MapContrlConnect();
    void Init();

signals:

public slots:
    void change_show_zoom(qreal zoomLevel);
    void change_show_center(const QGeoCoordinate &center);
private:
    std::shared_ptr<QDeclarativeGeoMap> show_map_ptr_=nullptr;
    std::shared_ptr<QDeclarativeGeoMap> control_map_ptr_=nullptr;
//    QDeclarativeGeoMap *show_map_ptr_=nullptr;
//    QDeclarativeGeoMap *control_map_ptr_=nullptr;

};

#endif // MAPCONTRLCONNECT_H
