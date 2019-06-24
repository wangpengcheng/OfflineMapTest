#TEMPLATE = app
#TARGET = player


HEADERS += \
    $$PWD/player.h \
    $$PWD/playercontrols.h \
    $$PWD/playlistmodel.h \
    $$PWD/videowidget.h \
    $$PWD/histogramwidget.h \
    $$PWD/myreviewwidget.h
SOURCES += \
    $$PWD/player.cpp \
    $$PWD/playercontrols.cpp \
    $$PWD/playlistmodel.cpp \
    $$PWD/videowidget.cpp \
    $$PWD/histogramwidget.cpp \
    $$PWD/myreviewwidget.cpp

#target.path = $$[QT_INSTALL_EXAMPLES]/multimediawidgets/player
#INSTALLS += target

INCLUDEPATH 	+= $$PWD

FORMS += \
    $$PWD/myreviewwidget.ui
