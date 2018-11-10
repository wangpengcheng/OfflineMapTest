#include "MapEngine.h"

#include <QRegExp>
#include <QNetworkReply>
#include <QEventLoop>
#include <QTimer>
#include <QString>
#include <QByteArray>
#include <QDebug>
#include <math.h>
#ifndef  QCOREAPPLICATION_H
#include <QCoreApplication>
#endif
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
UrlFactory::getTileURL(const MapType type,
                       const int x,
                       const int y,
                       const int zoom)
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
    qDebug()<<url;
    return request;
}


//-----------------------------------------------------------------------------
QString
UrlFactory::_getURL(const MapType type,
                    const int x,
                    const int y,
                    const int zoom)
{
    //判断z值：
    if(zoom<0||zoom>18){
        qWarning("Unknown map zoom %d\n", zoom);
        return QString::null;
    }
    //x,y,z change
       QString zz="L"+QString::number(zoom);
       QString yy="R"+QString("%1").arg(y,8,16,QLatin1Char('0'));//注意y坐标的计算机方式
       QString xx="C"+QString("%1").arg(x,8,16,QLatin1Char('0'));
    switch (type) {
    case GaodeStreet:
    {
        qDebug()<<QString("file:///tmp/esri_tiles/esri_100-l-3-%1-%2-%3.png").arg(x).arg(y).arg(zoom);

        return QString("http://wprd03.is.autonavi.com/appmaptile?style=7&x=%1&y=%2&z=%3").arg(x).arg(y).arg(zoom);
      //  return QString("file:///tmp/esri_tiles/esri_100-l-3-%1-%2-%3.png").arg(x).arg(y).arg(zoom);

    }
        break;
    case GaodeSatellite:
    {
       //  return QString("http://wprd03.is.autonavi.com/appmaptile?style=7&x=%1&y=%2&z=%3").arg(x).arg(y).arg(zoom);
        //return QString("file:///tmp/esri_tiles/esri_100-l-3-%1-%2-%3.png").arg(zoom).arg(x).arg(y);
         QString path_string=QCoreApplication::applicationDirPath();
         if(path_string!=""){
             QString temp_str="file:///"+path_string+"/_alllayers/%1/%2/%3.png";
              qDebug()<<temp_str.arg(zz).arg(yy).arg(xx);
             return temp_str.arg(zz).arg(yy).arg(xx);
         }else {
               QString temp_str="file:///"+path_string+"/_alllayers/%1/%2/%3.png";
               qDebug()<<temp_str.arg(zz).arg(yy).arg(xx);
            return QString("file:///F:/GitHub/OfflineMapTest/_alllayers/%1/%2/%3.png").arg(zz).arg(yy).arg(xx);
         }

    }
        break;

    default:
        qWarning("Unknown map id %d\n", type);
        break;
    }
    return QString::null;
}


