#-------------------------------------------------
#
# Project created by QtCreator 2023-10-05T15:51:53
#
#-------------------------------------------------

QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LogChat
RC_ICONS = logo.ico
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
        aboutsoftwaredialogwidget.cpp \
        baiduapi.cpp \
        botitemswidget.cpp \
        changelive2dwidget.cpp \
        chatgptapi.cpp \
        config.cpp \
        configwindow.cpp \
        listitemswidget.cpp \
        live2ddrawitemswidget.cpp \
        live2dlistitemswidget.cpp \
        live2dpartdrawingitemswidget.cpp \
        live2dpartitemswidget.cpp \
        llmbase.cpp \
        llmfactory.cpp \
        main.cpp \
        modelconfigitem.cpp \
        modelpartitem.cpp \
        netlive2d.cpp \
        pushandreceivewidget.cpp \
        setconfigdialogwidget.cpp \
        setdialogwidget.cpp \
        setlive2ddialogwidget.cpp \
        setpushbutton.cpp \
        setselectpushbutton.cpp \
        setselectwidget.cpp \
        useritemswidget.cpp \
        usertextedit.cpp \
        vitsapi.cpp \
        widget.cpp \
        xfxhapi.cpp

HEADERS += \
        aboutsoftwaredialogwidget.h \
        baiduapi.h \
        botitemswidget.h \
        changelive2dwidget.h \
        chatgptapi.h \
        config.h \
        configwindow.h \
        listitemswidget.h \
        live2ddrawitemswidget.h \
        live2dlistitemswidget.h \
        live2dpartdrawingitemswidget.h \
        live2dpartitemswidget.h \
        llmbase.h \
        llmfactory.h \
        modelconfigitem.h \
        modelpartitem.h \
        netlive2d.h \
        pushandreceivewidget.h \
        setconfigdialogwidget.h \
        setdialogwidget.h \
        setlive2ddialogwidget.h \
        setpushbutton.h \
        setselectpushbutton.h \
        setselectwidget.h \
        singletonbase.h \
        useritemswidget.h \
        usertextedit.h \
        vitsapi.h \
        widget.h \
        xfxhapi.h

FORMS += \
        aboutsoftwaredialogwidget.ui \
        botitemswidget.ui \
        changelive2dwidget.ui \
        listitemswidget.ui \
        live2ddrawitemswidget.ui \
        live2dlistitemswidget.ui \
        live2dpartdrawingitemswidget.ui \
        live2dpartitemswidget.ui \
        pushandreceivewidget.ui \
        setconfigdialogwidget.ui \
        setdialogwidget.ui \
        setlive2ddialogwidget.ui \
        setselectwidget.ui \
        useritemswidget.ui \
        widget.ui


RESOURCES += \
    res.qrc
