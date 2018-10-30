#ifndef MAP_URL_ENGINE_H
#define MAP_URL_ENGINE_H

#include <QString>
#include <QPoint>
#include <QByteArray>
#include <QNetworkProxy>
#include <QNetworkReply>
#include <QMutex>

#define MAX_MAP_ZOOM (20.0)

class UrlFactory : public QObject {
    Q_OBJECT
public:

    enum MapType
    {
        Invalid                ,
        GaodeStreet                ,
        GaodeSatellite          ,
    };

    UrlFactory      ();
    ~UrlFactory     ();

    QNetworkRequest getTileURL          (MapType type, int x, int y, int zoom);
    QString         getImageFormat      (MapType type, const QByteArray& image);


private slots:
\

private:
    QString _getURL                     (MapType type, int x, int y, int zoom);

private:
    int             _timeout;
    QByteArray      _userAgent;

};

#endif
