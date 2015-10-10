#-------------------------------------------------
#
# Project created by QtCreator 2015-10-09T14:59:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -lqwt -L../src -lclimat
INCLUDEPATH += /usr/include/qwt/ ../src/

TARGET = Climate
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    startview.cpp \
    graphview.cpp \
    savedialog.cpp \
    loaddialog.cpp \
    resultview.cpp \
    newsimulation.cpp

HEADERS  += mainwindow.h \
    startview.h \
    graphview.h \
    savedialog.h \
    loaddialog.h \
    resultview.h \
    newsimulation.h
