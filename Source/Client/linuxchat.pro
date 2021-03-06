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
    receiveworker.cpp

HEADERS  += mainwindow.h \
    networking.h \
    global.h \
    receiveworker.h

FORMS    += mainwindow.ui \

DISTFILES +=

RESOURCES += \
    qdarkstyle/style.qrc
