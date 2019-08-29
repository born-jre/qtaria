#-------------------------------------------------
#
# Project created by QtCreator 2017-10-18T22:31:26
#
#-------------------------------------------------
#CONFIG += static
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets websockets

TARGET = qtaria
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    addnewdialog.cpp \
    ariawarapper.cpp \
    objectholder.cpp \
    handlers/curlhandlers.cpp

HEADERS  += mainwindow.h \
    addnewdialog.h \
    ariawarapper.h \
    objectholder.h \
    types.h \
    handlers/handlers.h \
    handlers/curlhandlers.h

FORMS    += mainwindow.ui \
    addnewdialog.ui

RESOURCES += \
    icon-pack.qrc
LIBS += -L/usr/lib -laria2
QMAKE_CXXFLAGS += -std=c++1y

unix:!macx: LIBS += -L$$PWD/lib/ -laria2
LIBS += -lcurl

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
