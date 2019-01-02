
QT  += location-private positioning-private network

contains(QT_VERSION, 5.5.1) {
#    message(Using Local QtLocation headers for Qt 5.5.1)
#    INCLUDEPATH += \
#    $$PWD/qtlocation/include \
} else {
    message(Using Default QtLocation headers)
    INCLUDEPATH += $$QT.location.includes

}


HEADERS += \
    $$PWD/MapEngine.h \
    $$PWD/MapEngineData.h \
    $$PWD/MapUrlEngine.h \
    $$PWD/TileCacheWorker.h \
    $$PWD/GeoMapReply.h \
    $$PWD/GeoServiceProviderPlugin.h \
    $$PWD/GeoTileFetcher.h \
    $$PWD/GeoTiledMappingManagerEngine.h \

SOURCES += \
    $$PWD/MapEngine.cpp \
    $$PWD/MapUrlEngine.cpp \
    $$PWD/TileCacheWorker.cpp \
    $$PWD/GeoMapReply.cpp \
    $$PWD/GeoServiceProviderPlugin.cpp \
    $$PWD/GeoTileFetcher.cpp \
    $$PWD/GeoTiledMappingManagerEngine.cpp \

OTHER_FILES += \
    $$PWD/maps_plugin.json
