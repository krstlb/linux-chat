#-------------------------------------------------
#
# Project created by QtCreator 2016-03-07T10:38:55
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = linuxchat
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    networking.cpp \
    dialog.cpp \
    receiveworker.cpp \
    sendworker.cpp

HEADERS  += mainwindow.h \
    networking.h \
    dialog.h \
    global.h \
    receiveworker.h \
    sendworker.h

FORMS    += mainwindow.ui \
    dialog.ui

DISTFILES +=

RESOURCES += \
    qdarkstyle/style.qrc
