#-------------------------------------------------
#
# Project created by QtCreator 2014-08-02T17:18:07
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VM6000
TEMPLATE = app

SOURCES += \
    main.cpp \
    iconhelper.cpp \
    myapp.cpp \
    switchbutton.cpp \
    excelhelper.cpp \
    frmmessagebox.cpp \    
    frmmain.cpp \
    frminputbox.cpp \    
    frmconfig.cpp \    
    frmnvr.cpp \
    frmipc.cpp \
    frmpollconfig.cpp

HEADERS  += \
    myhelper.h \
    iconhelper.h \
    myapp.h \
    switchbutton.h \
    excelhelper.h \
    frmmessagebox.h \
    frmmain.h \
    frminputbox.h \    
    frmconfig.h \    
    frmnvr.h \
    frmipc.h \
    frmpollconfig.h

FORMS    += \
    frmmessagebox.ui \
    frmmain.ui \
    frminputbox.ui \
    frmconfig.ui \
    frmnvr.ui \
    frmipc.ui \
    frmpollconfig.ui

INCLUDEPATH 	+= $$PWD

MOC_DIR         = temp/moc
RCC_DIR         = temp/rcc
UI_DIR          = temp/ui
OBJECTS_DIR     = temp/obj
DESTDIR         = bin

win32:RC_FILE=main.rc

RESOURCES += \
    rc.qrc
