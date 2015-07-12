#-------------------------------------------------
#
# Project created by QtCreator 2015-07-11T21:07:43
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = July11SemaphoreProcessSystemV
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    Process2.cpp \
    Process1.cpp

QMAKE_LIBS_THREAD = -lpthread -lrt
