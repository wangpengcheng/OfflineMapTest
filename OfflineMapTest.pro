#TEMPLATE = app

#QT += qml quick  location  network
#QT += core gui
#QT +=location-private positioning-private
#QT += positioning
#QT += widgets
#CONFIG += c++11

#SOURCES += main.cpp \
#    screencontrol.cpp \
#   # qdeclarativegeomap.cpp \
#    tool.cpp \

#RESOURCES += qml.qrc

## Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH =

#include(QtLocationPlugin/LocationPlugin.pri)
##include(esri/esri.pri)
#INCLUDEPATH += \
#    QtLocationPlugin \



#LOCATION_PLUGIN_DESTDIR = $${OUT_PWD}/QtLocationPlugin
#LOCATION_PLUGIN_NAME    = GeoServiceProviderFactory
##LOCATION_PLUGIN_DESTDIR = $${OUT_PWD}/esri
##LOCATION_PLUGIN_NAME    = GeoServiceProviderFactoryEsri

#DISTFILES += \
#    img/bus_station.png \
#    img/bus_station_copy.png

#HEADERS += \
#    screencontrol.h \
#    screencontroltest.h \
#   # qdeclarativegeomap_p.h \
#    tool.h \
#    busstation.h
TEMPLATE = app

QT += qml  quick
QT += location positioning
QT += core gui
QT += network widgets

CONFIG += c++11

SOURCES += main.cpp \
    tool.cpp \
    busstation.cpp \
    screencontrol.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

include(QtLocationPlugin/LocationPlugin.pri)
include(test/test.pri)


INCLUDEPATH += \
    QtLocationPlugin \


LOCATION_PLUGIN_DESTDIR = $${OUT_PWD}/QtLocationPlugin
LOCATION_PLUGIN_NAME    = GeoServiceProviderFactory

HEADERS += \
    tool.h \
    screencontrol.h \
    busstation.h
