QT += core
QT -= gui

CONFIG += c++11

TARGET = tmr
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

DEFINES += QT_DEPRECATED_WARNINGS

DESTDIR = $$PWD/../scripts
