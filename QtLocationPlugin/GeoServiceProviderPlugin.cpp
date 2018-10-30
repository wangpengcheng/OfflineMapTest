#include "GeoServiceProviderPlugin.h"
#include "GeoTiledMappingManagerEngine.h"

#include <QtLocation/private/qgeotiledmappingmanagerengine_p.h>

Q_EXTERN_C Q_DECL_EXPORT const char *qt_plugin_query_metadata();
Q_EXTERN_C Q_DECL_EXPORT QT_PREPEND_NAMESPACE(QObject) *qt_plugin_instance();

//-----------------------------------------------------------------------------
const QT_PREPEND_NAMESPACE(QStaticPlugin) qt_static_plugin_GeoServiceProviderFactory()
{
    QT_PREPEND_NAMESPACE(QStaticPlugin) plugin = { qt_plugin_instance, qt_plugin_query_metadata};
    return plugin;
}


//-----------------------------------------------------------------------------
QGeoMappingManagerEngine*
GeoServiceProviderFactory::createMappingManagerEngine(
    const QVariantMap &parameters, QGeoServiceProvider::Error *error, QString *errorString) const
{
    return new GeoTiledMappingManagerEngine(parameters, error, errorString);
}

//-----------------------------------------------------------------------------
QGeoRoutingManagerEngine*
GeoServiceProviderFactory::createRoutingManagerEngine(
    const QVariantMap &, QGeoServiceProvider::Error *, QString *) const
{
    return NULL;
}

//-----------------------------------------------------------------------------
QPlaceManagerEngine*
GeoServiceProviderFactory::createPlaceManagerEngine(
    const QVariantMap &, QGeoServiceProvider::Error *, QString *) const
{
    return NULL;
}
