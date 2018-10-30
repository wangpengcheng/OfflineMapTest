#include "MapEngine.h"
#include "GeoTiledMappingManagerEngine.h"
#include "GeoTileFetcher.h"

#include <QtLocation/private/qgeocameracapabilities_p.h>
#include <QtLocation/private/qgeomaptype_p.h>
#if QT_VERSION < 0x050500
#include <QtLocation/private/qgeotiledmapdata_p.h>
#else
#include <QtLocation/private/qgeotiledmap_p.h>
#if QT_VERSION >= 0x050600
#include <QtLocation/private/qgeofiletilecache_p.h>
#else
#include <QtLocation/private/qgeotilecache_p.h>
#endif
#endif

#include <QDir>
#include <QStandardPaths>

#if QT_VERSION >= 0x050500
//-----------------------------------------------------------------------------
GeoTiledMap::GeoTiledMap(QGeoTiledMappingManagerEngine *engine, QObject *parent)
    : QGeoTiledMap(engine, parent)
{
}
#endif

//-----------------------------------------------------------------------------
GeoTiledMappingManagerEngine::GeoTiledMappingManagerEngine(const QVariantMap &parameters, QGeoServiceProvider::Error *error, QString *errorString)
:   QGeoTiledMappingManagerEngine()
{
    QGeoCameraCapabilities cameraCaps;
    cameraCaps.setMinimumZoomLevel(2.0);
    cameraCaps.setMaximumZoomLevel(MAX_MAP_ZOOM);
    cameraCaps.setSupportsBearing(true);
    setCameraCapabilities(cameraCaps);

    setTileSize(QSize(256, 256));

    setTileFetcher(new GeoTileFetcher(this));

    *error = QGeoServiceProvider::NoError;
    errorString->clear();


}

//-----------------------------------------------------------------------------
GeoTiledMappingManagerEngine::~GeoTiledMappingManagerEngine()
{
}

#if QT_VERSION < 0x050500

//-----------------------------------------------------------------------------
QGeoMapData *GeoTiledMappingManagerEngine::createMapData()
{
    return new QGeoTiledMapData(this, 0);
}

#else

//-----------------------------------------------------------------------------
QGeoMap*
GeoTiledMappingManagerEngine::createMap()
{
    return new GeoTiledMap(this);
}

#endif

