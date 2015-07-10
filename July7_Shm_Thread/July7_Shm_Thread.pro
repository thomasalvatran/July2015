#-------------------------------------------------
#
# Project created by QtCreator 2015-07-09T22:29:44
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = July7_Shm_Thread
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

QMAKE_LIBS_THREAD = -lpthread -lrt
