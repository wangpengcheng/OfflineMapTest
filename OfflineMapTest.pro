
TEMPLATE = app
QT += qml  quick
QT += location positioning
QT += core gui
QT += network widgets
QT += multimedia multimediawidgets #add video and music
QT += quickwidgets
QT += network  #add network
QT += webview
CONFIG += c++11

SOURCES += main.cpp \
    src/tool.cpp \
    src/busstation.cpp \
    src/screencontrol.cpp \
    src/busline.cpp \
    src/bus.cpp

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
    src/tool.h \
    src/screencontrol.h \
    src/busstation.h \
    src/busline.h \
    src/bus.h

DISTFILES +=
