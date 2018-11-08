#include "MapEngine.h"
#include "GeoMapReply.h"

#include <QtLocation/private/qgeotilespec_p.h>
#include <QtNetwork/QNetworkAccessManager>
#include <QFile>

//-----------------------------------------------------------------------------
GeoTiledMapReply::GeoTiledMapReply(QNetworkAccessManager *networkManager, const QNetworkRequest &request, const QGeoTileSpec &spec, QObject *parent)
    : QGeoTiledMapReply(spec, parent)
    , _reply(NULL)
    , _request(request)
    , _networkManager(networkManager)
{
    if(_request.url().isEmpty()) {
        if(!_badMapBox.size()) {
            QFile b(":/res/notile.png");
            if(b.open(QFile::ReadOnly))
                _badMapBox = b.readAll();
        }
        setMapImageData(_badMapBox);
        setMapImageFormat("png");
        setFinished(true);
        setCached(false);
    } else {
        FetchTileTask* task = getMapEngine()->createFetchTileTask(UrlFactory::GaodeSatellite, spec.x(), spec.y(), spec.zoom());
        connect(task, &MapTask::error, this, &GeoTiledMapReply::cacheError);
        getMapEngine()->addTask(task);
    }
}

//-----------------------------------------------------------------------------
GeoTiledMapReply::~GeoTiledMapReply()
{
    if (_reply) {
        _reply->deleteLater();
        _reply = 0;
    }
}
//-----------------------------------------------------------------------------
void
GeoTiledMapReply::abort()
{
    if (_reply)
        _reply->abort();
}

//-----------------------------------------------------------------------------
void
GeoTiledMapReply::replyDestroyed()
{
    _reply = 0;
}

//-----------------------------------------------------------------------------
void
GeoTiledMapReply::networkReplyFinished()
{
    if (!_reply) {
        return;
    }
    if (_reply->error() != QNetworkReply::NoError) {
        return;
    }
    QByteArray a = _reply->readAll();
    setMapImageData(a);
    QString format = getMapEngine()->urlFactory()->getImageFormat(UrlFactory::GaodeSatellite, a);
    if(!format.isEmpty()) {
        setMapImageFormat(format);
    }
    setFinished(true);
    _reply->deleteLater();
    _reply = 0;
}

//-----------------------------------------------------------------------------
void
GeoTiledMapReply::networkReplyError(QNetworkReply::NetworkError error)
{
    if (!_reply) {
        return;
    }
    if (error != QNetworkReply::OperationCanceledError) {
        qWarning() << "Fetch tile error:" << _reply->errorString();
    }
    _reply->deleteLater();
    _reply = 0;
    if(!_badTile.size()) {
        QFile b(":/res/notile.png");
        if(b.open(QFile::ReadOnly))
            _badTile = b.readAll();
    }
    setMapImageData(_badTile);
    setMapImageFormat("png");
    setFinished(true);
    setCached(false);
}

//-----------------------------------------------------------------------------
void
GeoTiledMapReply::cacheError(MapTask::TaskType type, QString /*errorString*/)
{

    if(type != MapTask::taskFetchTile) {
    }
    //-- Tile not in cache. Get it off the Internet.
    QNetworkProxy proxy = _networkManager->proxy();
    QNetworkProxy tProxy;
    tProxy.setType(QNetworkProxy::DefaultProxy);
    _networkManager->setProxy(tProxy);
    _reply = _networkManager->get(_request);
    _reply->setParent(0);
    connect(_reply, SIGNAL(finished()),                         this, SLOT(networkReplyFinished()));
    connect(_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkReplyError(QNetworkReply::NetworkError)));
    connect(_reply, SIGNAL(destroyed()),                        this, SLOT(replyDestroyed()));
    _networkManager->setProxy(proxy);
}

