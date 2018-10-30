#ifndef GEOTILEDMAPPINGMANAGERENGINE_H
#define GEOTILEDMAPPINGMANAGERENGINE_H

#include <QtLocation/QGeoServiceProvider>
#if QT_VERSION >= 0x050500
#include <QtLocation/private/qgeotiledmap_p.h>
#endif
#include <QtLocation/private/qgeotiledmappingmanagerengine_p.h>

#if QT_VERSION >= 0x050500
class GeoTiledMap : public QGeoTiledMap
{
    Q_OBJECT
public:
    GeoTiledMap(QGeoTiledMappingManagerEngine *engine, QObject *parent = 0);
};
#endif

class GeoTileFetcher;

class GeoTiledMappingManagerEngine : public QGeoTiledMappingManagerEngine
{
    Q_OBJECT
public:
    GeoTiledMappingManagerEngine(const QVariantMap &parameters, QGeoServiceProvider::Error *error, QString *errorString);
    ~GeoTiledMappingManagerEngine();
#if QT_VERSION < 0x050500
    QGeoMapData *createMapData();
#else
    QGeoMap *createMap();
#endif
};

#endif
