#-------------------------------------------------
#
# Project created by QtCreator 2015-09-22T19:12:49
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += webkitwidgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Installeur_API_V2.1
TEMPLATE = app


SOURCES += main.cpp\
        principal.cpp \
    installation.cpp \
    options.cpp \
    telechargement.cpp \
    chargement.cpp

HEADERS  += principal.h \
    installation.h \
    options.h \
    telechargement.h \
    chargement.h

FORMS    += principal.ui \
    options.ui \
    chargement.ui
