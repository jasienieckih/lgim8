#-------------------------------------------------
#
# Project created by QtCreator 2015-03-03T00:14:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = piksele
TEMPLATE = app


SOURCES += main.cpp\
        mywindow.cpp \
    point.cpp \
    triangle.cpp \
    triangleptr.cpp

HEADERS  += mywindow.h \
    point.h \
    triangle.h \
    triangleptr.h

FORMS    += mywindow.ui

QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    res.qrc
