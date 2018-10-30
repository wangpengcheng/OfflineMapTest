#include "MapEngine.h"

#include <QRegExp>
#include <QNetworkReply>
#include <QEventLoop>
#include <QTimer>
#include <QString>
#include <QByteArray>
#include <QDebug>

UrlFactory::UrlFactory()
    : _timeout(5 * 1000)

{
}

//-----------------------------------------------------------------------------
UrlFactory::~UrlFactory()
{
}


//-----------------------------------------------------------------------------
QString
UrlFactory::getImageFormat(MapType type, const QByteArray& image)
{
    QString format;
    if(image.size() > 2)
    {
        if((char)image[0] == (char)0xff && (char)image[1] == (char)0xd8)
            format = "jpg";
        else if((char)image[0] == (char)0x89 && (char)image[1] == (char)0x50)
            format = "png";
        else {
            switch (type) {
            case GaodeStreet:
                format = "png";
                break;
            case GaodeSatellite:
                format = "jpg";
                break;
            default:
                qWarning("UrlFactory::getImageFormat() Unknown map id %d", type);
                break;
            }
        }
    }
    return format;
}

//-----------------------------------------------------------------------------
QNetworkRequest
UrlFactory::getTileURL(MapType type, int x, int y, int zoom)
{
    //-- Build URL
    QNetworkRequest request;
    QString url = _getURL(type, x, y, zoom);
    if(url.isEmpty())
        return request;
    request.setUrl(QUrl(url));
    request.setRawHeader("Accept", "*/*");
    request.setRawHeader("User-Agent", _userAgent);
    switch (type) {
    case GaodeStreet:
    case GaodeSatellite:
        request.setRawHeader("Referrer", "https://www.gaode.com/maps/");
        break;
    default:
        break;
    }
    qDebug()<<"hello"+url;
    return request;
}


//-----------------------------------------------------------------------------
QString
UrlFactory::_getURL(MapType type,
                    int x,
                    int y,
                    int zoom)
{
    //x,y,z change
    QString zz="L"+QString::number(zoom);
    QString yy="R"+QString("%1").arg(y+1,8,16,QLatin1Char('0'));//注意y坐标的计算机方式
    QString xx="C"+QString("%1").arg(x,8,16,QLatin1Char('0'));
    switch (type) {
        case GaodeStreet:
        {
            qDebug()<<QString("file:///tmp/esri_tiles/esri_100-l-3-%1-%2-%3.png").arg(x).arg(y).arg(zoom);

            //return QString("http://wprd03.is.autonavi.com/appmaptile?style=7&x=%1&y=%2&z=%3").arg(x).arg(y).arg(zoom);
            //return QString("file:///tmp/esri_tiles/esri_100-l-3-%1-%2-%3.png").arg(x).arg(y).arg(zoom);

        }
            break;
        case GaodeSatellite:
        {
             //return QString("http://wprd03.is.autonavi.com/appmaptile?style=6&x=%1&y=%2&z=%3").arg(x).arg(y).arg(zoom);
            //return QString("file:///tmp/esri_tiles/esri_100-l-3-%1-%2-%3.png").arg(zoom).arg(x).arg(y);
            QString result=QString("file:///F:/GitHub/OfflineMapTest/_alllayers/%1/%2/%3.png").arg(zz).arg(yy).arg(xx);
             //QString reslut=QString(" file:///media/wangpengcheng/文档/GitHub/OfflineMapTest/_alllayers/%1/%2/%3.png").arg(zz).arg(yy).arg(xx);
            qDebug()<<result;
            return result;
            break;
        }
        default:
            qWarning("Unknown map id %d\n", type);
            break;
      }

    return QString::null;
}


