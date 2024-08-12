#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QApplication>

#include <QRect>
#include <QDebug>
#include <QScreen>
#include <QString>

#include "singletonbase.h"

class ConfigWindow:public SingletonBase{

public:
    static QWidget*         _WindowPointer;
    static const QString    _WindowTitle;
    static const int        _StaticMinWidth;
    static const int        _StaticMinHeight;

private:
    static int _StaticPosX;
    static int _StaticPosY;
    static int _StaticWidth;
    static int _StaticHeight;
    static int _DesktopWidth;
    static int _DesktopHeight;
    static int _WindowTransparent;
public:

    static void init();
    static void setStaticPosX(int x);
    static void setStaticPosY(int y);
    static void setStaticWidth(int w);
    static void setStaticHeight(int h);
    static void setWindowTransparent(int a);

    static int getStaticPosX();
    static int getStaticPosY();
    static int getStaticWidth();
    static int getStaticHeight();
    static int getDesktopWidth();
    static int getDesktopHeight();
    static int getWindowTransparent();

};
#endif // CONFIGWINDOW_H
