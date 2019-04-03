#-------------------------------------------------
#
# Project created by QtCreator 2014-08-02T17:18:07
#
#-------------------------------------------------
#This file is a VideoControl moudel of this project ,it comes from liudianwu
# Thanks liudianwu!!!!
# 2019-4-1 10:39:25
#-------------------------------------------------
QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#TARGET = VM6000
#TEMPLATE = app

SOURCES += \
    $$PWD/iconhelper.cpp \
    $$PWD/myapp.cpp \
    $$PWD/excelhelper.cpp \
    $$PWD/frmmessagebox.cpp \
    $$PWD/frmmain.cpp \
    $$PWD/frminputbox.cpp \
    $$PWD/frmconfig.cpp \
    $$PWD/frmnvr.cpp \
    $$PWD/frmipc.cpp \
    $$PWD/frmpollconfig.cpp \
    $$PWD/switchbutton.cpp \
    $$PWD/videoshowwidget.cpp \
    $$PWD/myvideowidget.cpp

HEADERS  += \
    $$PWD/myhelper.h \
    $$PWD/iconhelper.h \
    $$PWD/myapp.h \
    $$PWD/excelhelper.h \
    $$PWD/frmmessagebox.h \
    $$PWD/frmmain.h \
    $$PWD/frminputbox.h \
    $$PWD/frmnvr.h \
    $$PWD/frmipc.h \
    $$PWD/frmpollconfig.h \
    $$PWD/switchbutton.h \
    $$PWD/frmconfig.h \
    $$PWD/videocontrolmain.h \
    $$PWD/videoshowwidget.h \
    $$PWD/myvideowidget.h

FORMS    += \
    $$PWD/frmmessagebox.ui \
    $$PWD/frmmain.ui \
    $$PWD/frminputbox.ui \
    $$PWD/frmconfig.ui \
    $$PWD/frmnvr.ui \
    $$PWD/frmipc.ui \
    $$PWD/frmpollconfig.ui \
    $$PWD/videoshowwidget.ui

INCLUDEPATH 	+= $$PWD

#MOC_DIR         = temp/moc
#RCC_DIR         = temp/rcc
#UI_DIR          = temp/ui
#OBJECTS_DIR     = temp/obj
#DESTDIR         = bin

win32:RC_FILE=$$PWD/main.rc

RESOURCES += \
    $$PWD/rc.qrc
