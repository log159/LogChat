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

    static const QString    WindowTitle;
    static const int        StaticMinWidth;
    static const int        StaticMinHeight;

private:
    static QWidget* WindowPointer;
    static int      StaticPosX;
    static int      StaticPosY;
    static int      StaticWidth;
    static int      StaticHeight;
    static int      DesktopWidth;
    static int      DesktopHeight;
    static int      WindowTransparent;
public:

    static void init();

    static void setWindowPointer(QWidget* ptr);
    static void setStaticPosX(int x);
    static void setStaticPosY(int y);
    static void setStaticWidth(int w);
    static void setStaticHeight(int h);
    static void setWindowTransparent(int a);

    static QWidget* getWindowPointer();
    static int getStaticPosX();
    static int getStaticPosY();
    static int getStaticWidth();
    static int getStaticHeight();
    static int getDesktopWidth();
    static int getDesktopHeight();
    static int getWindowTransparent();

};
#endif // CONFIGWINDOW_H
