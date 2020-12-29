#TEMPLATE = app
#TARGET = player

QT       += core gui network
QT += qml-private quick-private gui-private core-private
SOURCES += \
    $$PWD/tool.cpp \
    $$PWD/busstation.cpp \
    $$PWD/busline.cpp \
    $$PWD/bus.cpp \
    $$PWD/mapcontrlconnect.cpp \
    $$PWD/mainshowdialog.cpp

HEADERS += \
    $$PWD/tool.h \
    $$PWD/busstation.h \
    $$PWD/busline.h \
    $$PWD/bus.h \
    $$PWD/mapcontrlconnect.h \
    $$PWD/mainshowdialog.h \


FORMS += \
    $$PWD/mainshowdialog.ui
