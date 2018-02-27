#-------------------------------------------------
#
# Project created by QtCreator 2015-09-22T19:12:49
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Installeur_API_V2
TEMPLATE = app


SOURCES += main.cpp\
        principal.cpp \
    installation.cpp \
    options.cpp

HEADERS  += principal.h \
    installation.h \
    options.h

FORMS    += principal.ui \
    options.ui
