#include "mapcontrlconnect.h"

MapContrlConnect::MapContrlConnect()
{

}
MapContrlConnect::MapContrlConnect(std::shared_ptr<QDeclarativeGeoMap> show_map,
                                   std::shared_ptr<QDeclarativeGeoMap> control_map):
    show_map_ptr_(show_map),control_map_ptr(control_map)
{
    Init();
}

//MapContrlConnect::~MapContrlConnect()
//{

//}
void MapContrlConnect::Init()
{
    QObject::connect(control_map_ptr,SIGNAL(zoomLevelChanged(qreal)));
}
