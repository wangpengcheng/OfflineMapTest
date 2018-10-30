#ifndef GEOMAPREPLY_H
#define GEOMAPREPLY_H

#include <QtNetwork/QNetworkReply>
#include <QtLocation/private/qgeotiledmapreply_p.h>

#include "MapEngineData.h"

class GeoTiledMapReply : public QGeoTiledMapReply
{
    Q_OBJECT
public:
    GeoTiledMapReply(QNetworkAccessManager*  networkManager, const QNetworkRequest& request, const QGeoTileSpec &spec, QObject *parent = 0);
    ~GeoTiledMapReply();
    void abort();

private slots:
    void replyDestroyed         ();
    void networkReplyFinished   ();
    void networkReplyError      (QNetworkReply::NetworkError error);
    void cacheError             (MapTask::TaskType type, QString errorString);

private:
    QNetworkReply*          _reply;
    QNetworkRequest         _request;
    QNetworkAccessManager*  _networkManager;
    QByteArray              _badMapBox;
    QByteArray              _badTile;
};

#endif
