#include "configlive2d.h"

HWND  ConfigLive2d::Live2DWindow =nullptr;

float ConfigLive2d::ModelX     =0.f;
float ConfigLive2d::ModelY     =0.f;
float ConfigLive2d::MouseX     =0.f;
float ConfigLive2d::MouseY     =0.f;

HWND ConfigLive2d::getLive2DWindow()
{
    return Live2DWindow;
}

void ConfigLive2d::setLive2DWindow(const HWND &live2DWindow)
{
    Live2DWindow = live2DWindow;
}

void ConfigLive2d::init()
{
    QRect deskRect = QGuiApplication::primaryScreen()->geometry();

    ModelX=deskRect.width()/2;
    ModelY=deskRect.height()/2;

}

float ConfigLive2d::getModelX()
{
    return ModelX;
}

void ConfigLive2d::setModelX(float modelX)
{
    ModelX = modelX;
}

float ConfigLive2d::getModelY()
{
    return ModelY;
}

void ConfigLive2d::setModelY(float modelY)
{
    ModelY = modelY;
}

float ConfigLive2d::getMouseX()
{
    return MouseX;
}

void ConfigLive2d::setMouseX(float mouseX)
{
    MouseX = mouseX;
}

float ConfigLive2d::getMouseY()
{
    return MouseY;
}

void ConfigLive2d::setMouseY(float mouseY)
{
    MouseY = mouseY;
}
