#-------------------------------------------------
#
# Project created by QtCreator 2015-12-23T19:53:33
#
#-------------------------------------------------

QT          += core
QT          += gui
greaterThan(QT_MAJOR_VERSION, 4):   QT  += widgets

TARGET      = Grapher2D
TEMPLATE    = lib

CONFIG      += dll

win32:  DESTDIR = $$PWD/win
unix:   DESTDIR = $$PWD/unix

SOURCES += grapher2d.cpp

HEADERS += grapher2d.h

unix {
    target.path = /usr/lib
    INSTALLS    += target
}
