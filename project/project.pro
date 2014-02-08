#-------------------------------------------------
#
# Project created by QtCreator 2013-05-29T17:26:35
#
#-------------------------------------------------

QT       += core gui
QT += webkit
TARGET = project
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/datapoint.cpp \
    src/cell.cpp \
    src/database.cpp \
    src/square.cpp \
    src/noise.cpp \
    src/user.cpp

HEADERS  += src/mainwindow.h \
    src/datapoint.h \
    src/cell.h \
    src/database.h \
    src/square.h \
    src/noise.h \
    src/user.h

FORMS    += \
    mainwindow.ui

unix|win32: LIBS += -ljson

CONFIG          += console
