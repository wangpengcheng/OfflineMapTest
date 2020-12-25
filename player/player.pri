#TEMPLATE = app
#TARGET = player


HEADERS += \
    $$PWD/myreviewwidget.h \
    $$PWD/qtavplayercontrols.h \
    $$PWD/reviewwidget.h
SOURCES += \
    $$PWD/myreviewwidget.cpp \
    $$PWD/qtavplayercontrols.cpp \
    $$PWD/reviewwidget.cpp


#target.path = $$[QT_INSTALL_EXAMPLES]/multimediawidgets/player
#INSTALLS += target

INCLUDEPATH 	+= $$PWD

FORMS += \
    $$PWD/myreviewwidget.ui \
    $$PWD/reviewwidget.ui
