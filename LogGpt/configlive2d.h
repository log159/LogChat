#ifndef CONFIGLIVE2D_H
#define CONFIGLIVE2D_H

#include <QRect>
#include <QGuiApplication>
#include <QScreen>

#include "windows.h"
#include "singletonbase.h"

class ConfigLive2d:public SingletonBase
{
private:

    static HWND  _Live2DWindow;
    static float _ModelX;
    static float _ModelY;
    static float _MouseX;
    static float _MouseY;
public:
    static void init();
public:
    static float getModelX();
    static float getModelY();
    static float getMouseX();
    static float getMouseY();

    static void setModelX(float ModelX);
    static void setModelY(float ModelY);
    static void setMouseX(float MouseX);
    static void setMouseY(float MouseY);

    static HWND getLive2DWindow();
    static void setLive2DWindow(const HWND &Live2DWindow);
};

#endif // CONFIGLIVE2D_H
