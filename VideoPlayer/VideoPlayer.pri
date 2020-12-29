#TEMPLATE = app
#TARGET = player

QT       += core gui network

HEADERS += \
    $$PWD/myvideowidget.h \
    $$PWD/qtavplayercontrols.h \
    $$PWD/qtavvideowidget.h \
    $$PWD/screencontrol.h \
    $$PWD/streamvideowidget.h \
    $$PWD/videodecodethread.h \
    $$PWD/videosavethread.h \
    $$PWD/videoshowwidget.h
SOURCES += \
    $$PWD/myvideowidget.cpp \
    $$PWD/qtavplayercontrols.cpp \
    $$PWD/qtavvideowidget.cpp \
    $$PWD/screencontrol.cpp \
    $$PWD/streamvideowidget.cpp \
    $$PWD/videodecodethread.cpp \
    $$PWD/videosavethread.cpp \
    $$PWD/videoshowwidget.cpp


#target.path = $$[QT_INSTALL_EXAMPLES]/multimediawidgets/player
#INSTALLS += target

INCLUDEPATH 	+= $$PWD

FORMS += \
    $$PWD/videoshowwidget.ui
