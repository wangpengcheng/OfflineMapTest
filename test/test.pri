
QT  += location-private positioning-private network

INCLUDEPATH += $$QT.location.includes

HEADERS += \
    $$PWD/tool_test.h \
    $$PWD/screencontroltest.h \
    $$PWD/busstationtest.h \
    $$PWD/buslinetest.h \
    $$PWD/bustest.h


SOURCES += \
    $$PWD/tool_test.cpp \
    $$PWD/screencontroltest.cpp \
    $$PWD/busstationtest.cpp \
    $$PWD/buslinetest.cpp \
    $$PWD/bustest.cpp


#OTHER_FILES += \
#    $$PWD/maps_plugin.json
