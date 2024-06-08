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

    static HWND  Live2DWindow;
    static float ModelX;
    static float ModelY;
    static float MouseX;
    static float MouseY;
public:
    static void init();
public:
    static float getModelX();
    static float getModelY();
    static float getMouseX();
    static float getMouseY();

    static void setModelX(float modelX);
    static void setModelY(float modelY);
    static void setMouseX(float mouseX);
    static void setMouseY(float mouseY);

    static HWND getLive2DWindow();
    static void setLive2DWindow(const HWND &live2DWindow);
};

#endif // CONFIGLIVE2D_H
