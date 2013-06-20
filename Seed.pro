#-------------------------------------------------
#
# Project created by QtCreator 2013-06-04T23:55:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Seed
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    seed.cpp \
    renderarea.cpp \
    fileparse.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    seed.h \
    renderarea.h \
    fileparse.h \
    dialog.h

FORMS    += mainwindow.ui \
    dialog.ui

RESOURCES += \
    img/img.qrc
