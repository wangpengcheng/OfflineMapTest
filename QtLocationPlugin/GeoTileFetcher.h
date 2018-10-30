#ifndef GEOTILEFETCHER_H
#define GEOTILEFETCHER_H

#include <QtLocation/private/qgeotilefetcher_p.h>
#include "MapUrlEngine.h"

class QGeoTiledMappingManagerEngine;
class QNetworkAccessManager;

class GeoTileFetcher : public QGeoTileFetcher
{
    Q_OBJECT
public:
    explicit GeoTileFetcher             (QGeoTiledMappingManagerEngine *parent = 0);
    ~GeoTileFetcher();
private:
    QGeoTiledMapReply*      getTileImage    (const QGeoTileSpec &spec);
private:
    QNetworkAccessManager*  _networkManager;
};

#endif
