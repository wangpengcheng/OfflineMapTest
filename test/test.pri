
QT  += location-private positioning-private network

INCLUDEPATH += $$QT.location.includes

HEADERS += \
    $$PWD/tool_test.h \
    $$PWD/screencontroltest.h \
    $$PWD/busstationtest.h


SOURCES += \
    $$PWD/tool_test.cpp \
    $$PWD/screencontroltest.cpp \
    $$PWD/busstationtest.cpp


#OTHER_FILES += \
#    $$PWD/maps_plugin.json
