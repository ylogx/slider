#-------------------------------------------------
#
# Project created by QtCreator 2013-04-16T15:23:02
#
#-------------------------------------------------

QT       += core gui

TARGET = demo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    amarokInterface.cpp \
    amarokAdaptor.cpp

HEADERS  += mainwindow.h \
    amarokInterface.h \
    amarokAdaptor.h

FORMS    += mainwindow.ui

QT += dbus
