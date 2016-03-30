#-------------------------------------------------
#
# Project created by QtCreator 2016-03-29T20:18:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = arm-rule
TEMPLATE = app


SOURCES += main.cpp\
        armrule.cpp

HEADERS  += armrule.h \
    ufrn_al5d.h

FORMS    += armrule.ui

LIBS += -L"$$_PRO_FILE_PWD_/lib/" -lufrn_lynx
