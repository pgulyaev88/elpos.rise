#-------------------------------------------------
#
# Project created by QtCreator 2016-08-29T12:42:18
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rise
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

DISTFILES += \
    SQL/base.sql \
    rise_ru_RU.ts

TRANSLATIONS += rise_ru_RU.ts
