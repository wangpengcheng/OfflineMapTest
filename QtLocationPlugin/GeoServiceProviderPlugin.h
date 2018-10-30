#ifndef GEOSERVICEPROVIDER_H
#define GEOSERVICEPROVIDER_H

#include <QtCore/QObject>
#include <QtLocation/QGeoServiceProviderFactory>
#include <QtPlugin>

class GeoServiceProviderFactory: public QObject, public QGeoServiceProviderFactory
{
    Q_OBJECT
    Q_INTERFACES(QGeoServiceProviderFactory)
    Q_PLUGIN_METADATA(IID "org.qt-project.qt.geoservice.serviceproviderfactory/5.0" FILE "maps_plugin.json")

public:
    QGeoMappingManagerEngine*   createMappingManagerEngine      (const QVariantMap &parameters, QGeoServiceProvider::Error *error, QString *errorString) const;
    QGeoRoutingManagerEngine*   createRoutingManagerEngine      (const QVariantMap &parameters, QGeoServiceProvider::Error *error, QString *errorString) const;
    QPlaceManagerEngine*        createPlaceManagerEngine        (const QVariantMap &parameters, QGeoServiceProvider::Error *error, QString *errorString) const;
};

#endif
