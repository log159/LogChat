#-------------------------------------------------
#
# Project created by QtCreator 2023-10-05T15:51:53
#
#-------------------------------------------------

QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LogGPT
RC_ICONS = gpt.ico
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        baiduapi.cpp \
        botitemswidget.cpp \
        config.cpp \
        configwindow.cpp \
        listitemswidget.cpp \
        main.cpp \
        nettcp.cpp \
        pushandreceivewidget.cpp \
        setconfigdialogwidget.cpp \
        setdialogwidget.cpp \
        setselectpushbutton.cpp \
        setselectwidget.cpp \
        useritemswidget.cpp \
        usertextedit.cpp \
        widget.cpp

HEADERS += \
        baiduapi.h \
        botitemswidget.h \
        config.h \
        configwindow.h \
        listitemswidget.h \
        nettcp.h \
        pushandreceivewidget.h \
        setconfigdialogwidget.h \
        setdialogwidget.h \
        setselectpushbutton.h \
        setselectwidget.h \
        singletonbase.h \
        useritemswidget.h \
        usertextedit.h \
        widget.h

FORMS += \
        botitemswidget.ui \
        listitemswidget.ui \
        pushandreceivewidget.ui \
        setdialogwidget.ui \
        setselectwidget.ui \
        useritemswidget.ui \
        widget.ui


RESOURCES += \
    res.qrc
