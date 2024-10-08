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
        audioplayer.cpp \
        baiduapi.cpp \
        botitemswidget.cpp \
        changeconfigitem.cpp \
        changelive2dwidget.cpp \
        chatgptapi.cpp \
        config.cpp \
        configconstway.cpp \
        configfileio.cpp \
        configlive2d.cpp \
        configwindow.cpp \
        deepseekapi.cpp \
        galdialog.cpp \
        global.cpp \
        gptsovitsapi.cpp \
        listitemswidget.cpp \
        live2danimationitemswidget.cpp \
        live2ddrawitemswidget.cpp \
        live2dexpandmotitemswidget.cpp \
        live2dlistitemswidget.cpp \
        live2dparamitemswidget.cpp \
        live2dpartitemswidget.cpp \
        llmbase.cpp \
        llmfactory.cpp \
        main.cpp \
        mainwidget.cpp \
        modelconfigitem.cpp \
        netlive2d.cpp \
        networkmanager.cpp \
        pushandreceivewidget.cpp \
        qaudiocapture.cpp \
        qhttppost.cpp \
        rangeslider.cpp \
        regexpchar.cpp \
        selfvits.cpp \
        setcompounddialogwidget.cpp \
        setconfigdialogwidget.cpp \
        setdialogwidget.cpp \
        setlive2ddialogwidget.cpp \
        setpushbutton.cpp \
        setselectpushbutton.cpp \
        setselectwidget.cpp \
        speechrecognition.cpp \
        timeinformation.cpp \
        transformation.cpp \
        useritemswidget.cpp \
        usertextedit.cpp \
        vitsapi.cpp \
        vitsbase.cpp \
        vitsfactory.cpp \
        widget.cpp \
        windowbutton.cpp \
        xfxhapi.cpp

HEADERS += \
        aboutsoftwaredialogwidget.h \
        audioplayer.h \
        baiduapi.h \
        botitemswidget.h \
        changeconfigitem.h \
        changelive2dwidget.h \
        chatgptapi.h \
        config.h \
        configconstway.h \
        configfileio.h \
        configlive2d.h \
        configwindow.h \
        deepseekapi.h \
        galdialog.h \
        global.h \
        gptsovitsapi.h \
        listitemswidget.h \
        live2danimationitemswidget.h \
        live2ddrawitemswidget.h \
        live2dexpandmotitemswidget.h \
        live2dlistitemswidget.h \
        live2dparamitemswidget.h \
        live2dpartitemswidget.h \
        llmbase.h \
        llmfactory.h \
        mainwidget.h \
        modelconfigitem.h \
        netlive2d.h \
        networkmanager.h \
        pushandreceivewidget.h \
        qaudiocapture.h \
        qhttppost.h \
        rangeslider.h \
        regexpchar.h \
        selfvits.h \
        setcompounddialogwidget.h \
        setconfigdialogwidget.h \
        setdialogwidget.h \
        setlive2ddialogwidget.h \
        setpushbutton.h \
        setselectpushbutton.h \
        setselectwidget.h \
        singletonbase.h \
        speechrecognition.h \
        timeinformation.h \
        transformation.h \
        useritemswidget.h \
        usertextedit.h \
        vitsapi.h \
        vitsbase.h \
        vitsfactory.h \
        widget.h \
        windowbutton.h \
        xfxhapi.h

FORMS += \
        aboutsoftwaredialogwidget.ui \
        botitemswidget.ui \
        changelive2dwidget.ui \
        galdialog.ui \
        listitemswidget.ui \
        live2danimationitemswidget.ui \
        live2ddrawitemswidget.ui \
        live2dexpandmotitemswidget.ui \
        live2dlistitemswidget.ui \
        live2dparamitemswidget.ui \
        live2dpartitemswidget.ui \
        pushandreceivewidget.ui \
        setcompounddialogwidget.ui \
        setconfigdialogwidget.ui \
        setdialogwidget.ui \
        setlive2ddialogwidget.ui \
        setselectwidget.ui \
        useritemswidget.ui \
        widget.ui


RESOURCES += \
    res.qrc
