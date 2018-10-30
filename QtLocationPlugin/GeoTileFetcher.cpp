#include "MapEngine.h"
#include "GeoTileFetcher.h"
#include "GeoMapReply.h"

#include <QtCore/QLocale>
#include <QtNetwork/QNetworkRequest>
#include <QtLocation/private/qgeotilespec_p.h>

//-----------------------------------------------------------------------------
GeoTileFetcher::GeoTileFetcher(QGeoTiledMappingManagerEngine *parent)
    : QGeoTileFetcher(parent)
    , _networkManager(new QNetworkAccessManager(this))
{
}

//-----------------------------------------------------------------------------
GeoTileFetcher::~GeoTileFetcher()
{

}

//-----------------------------------------------------------------------------
QGeoTiledMapReply*
GeoTileFetcher::getTileImage(const QGeoTileSpec &spec)
{
    //-- Build URL
    QNetworkRequest request = getMapEngine()->urlFactory()->getTileURL(UrlFactory::GaodeSatellite, spec.x(), spec.y(), spec.zoom());

    return new GeoTiledMapReply(_networkManager, request, spec);
}
