#-------------------------------------------------
#
# Project created by QtCreator 2016-04-16T14:29:10
#
#-------------------------------------------------

QT       -= gui

TARGET = ArmRuleLib
TEMPLATE = lib

DEFINES += ARMRULELIB_LIBRARY

SOURCES += armrulelib.cpp

HEADERS += armrulelib.h\
        armrulelib_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

