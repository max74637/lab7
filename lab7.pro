#-------------------------------------------------
#
# Project created by QtCreator 2017-06-20T12:54:33
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab7
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog1.cpp \
    sundata.cpp \
    dialog2.cpp \
    location.cpp \
    utils.cpp \
    sundataview.cpp

HEADERS  += mainwindow.h \
    dialog1.h \
    sundata.h \
    dialog2.h \
    location.h \
    utils.h \
    sundataview.h

FORMS    += mainwindow.ui \
    dialog1.ui \
    dialog2.ui

LIBS += -lprogbase -lssl
