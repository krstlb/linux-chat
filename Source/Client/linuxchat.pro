#-------------------------------------------------
#
# Project created by QtCreator 2016-03-07T10:38:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = linuxchat
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    networking.cpp \
    connectdialog.cpp

HEADERS  += mainwindow.h \
    networking.h \
    connectdialog.h

FORMS    += mainwindow.ui \
    connectdialog.ui

DISTFILES +=

RESOURCES += \
    qdarkstyle/style.qrc
