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
    QNetworkReply*          _reply;                         //请求返回函数
    QNetworkRequest         _request;                       //请求函数
    QNetworkAccessManager*  _networkManager;                //网络请求管理
    QByteArray              _badMapBox;                     //坏Map管理
    QByteArray              _badTile;                       //坏瓦片
};

#endif
