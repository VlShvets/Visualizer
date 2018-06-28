`#-------------------------------------------------
#
# Project created by QtCreator 2015-07-07T13:42:30
#
#-------------------------------------------------

QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD/map

win32: LIBS += -L$$PWD/lib/Grapher2D/win -lGrapher2D
unix: LIBS += -L$$PWD/lib/Grapher2D/unix -lGrapher2D
INCLUDEPATH += $$PWD/lib/Grapher2D

INCLUDEPATH += $$PWD/../include/

unix|win32: LIBS += -L$$PWD/../App/ -lImit
INCLUDEPATH += $$PWD/../Imit

unix|win32: LIBS += -L$$PWD/../App/ -lPoi
INCLUDEPATH += $$PWD/../Poi

INCLUDEPATH += $$PWD/../OperatingEnvironment

unix|win32: LIBS += -L$$PWD/../App/ -lAir
INCLUDEPATH += $$PWD/../Air

unix|win32: LIBS += -L$$PWD/../App/ -lSurface
INCLUDEPATH += $$PWD/../Surface

#unix|win32: LIBS += -L$$PWD/../App/ -lTest
#INCLUDEPATH += $$PWD/../Test

TARGET = Visualizer
TEMPLATE = app

DESTDIR = $$PWD/../App

SOURCES += Visualizer.cpp \
    Painter.cpp \
    Target.cpp \
    main.cpp \
    Tool.cpp \
    GraphHeight.cpp \
    MainThread.cpp \
    MainWindow.cpp \
    AboutEtalon.cpp \
    AboutTrack.cpp

HEADERS += Visualizer.h\
    Painter.h \
    Target.h \
    Tool.h \
    GraphHeight.h \
    MainThread.h \
    MainWindow.h \
    AboutEtalon.h \
    define.h \
    AboutTrack.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES +=

RESOURCES += \
    res.qrc

CONFIG += resources_big
