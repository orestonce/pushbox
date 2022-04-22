#-------------------------------------------------
#
# Project created by QtCreator 2021-12-18T13:34:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pushbox-qt
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
    pbcore.cpp \
    dialog.cpp \
    toast.cpp

HEADERS  += mainwindow.h \
    pbcore.h \
    dialog.h \
    toast.h

FORMS    += mainwindow.ui \
    dialog.ui

RESOURCES += \
    sprites.qrc

LIBS += -L$$PWD -lpbcore-impl

DISTFILES += \
    pbcore-impl.a
