#-------------------------------------------------
#
# Project created by QtCreator 2016-04-17T12:15:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ArmRuleForBeginners
TEMPLATE = app


SOURCES += main.cpp\
        armruleforbeginners.cpp

HEADERS  += armruleforbeginners.h

FORMS    += armruleforbeginners.ui




unix:!macx: LIBS += -L$$PWD/lib/ -lArmRuleLib

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
