#-------------------------------------------------
#
# Project created by QtCreator 2017-04-19T09:42:12
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HTYChat
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    form.cpp \
    formfind.cpp \
    formchat.cpp \
    formprofile.cpp \
    editprofile.cpp \
    formreg.cpp \
    itemfind.cpp

HEADERS  += mainwindow.h \
    form.h \
    formfind.h \
    formchat.h \
    formprofile.h \
    editprofile.h \
    formreg.h \
    itemfind.h

FORMS    += mainwindow.ui \
    form.ui \
    formfind.ui \
    formchat.ui \
    formprofile.ui \
    editprofile.ui \
    formreg.ui \
    itemfind.ui

RESOURCES += \
    res.qrc

DISTFILES +=
