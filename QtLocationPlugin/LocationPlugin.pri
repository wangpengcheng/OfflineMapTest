
QT  += location-private 
QT  += positioning-private 
QT  += network

# 添加location 头部文件
message(Using Default QtLocation headers)
INCLUDEPATH += $$QT.location.includes



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
