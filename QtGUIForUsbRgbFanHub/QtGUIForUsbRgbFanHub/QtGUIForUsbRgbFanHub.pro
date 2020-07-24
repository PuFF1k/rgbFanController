#-------------------------------------------------
#
# Project created by QtCreator 2020-03-28T16:58:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtGUIForUsbRgbFanHub
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    hidapi.h

FORMS    += mainwindow.ui

win32: LIBS += -lhidapi
