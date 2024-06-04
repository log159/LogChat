#include "configlive2d.h"

HWND  ConfigLive2d::_Live2DWindow =nullptr;

float ConfigLive2d::_ModelX     =0.f;
float ConfigLive2d::_ModelY     =0.f;
float ConfigLive2d::_MouseX     =0.f;
float ConfigLive2d::_MouseY     =0.f;

HWND ConfigLive2d::getLive2DWindow()
{
    return _Live2DWindow;
}

void ConfigLive2d::setLive2DWindow(const HWND &Live2DWindow)
{
    _Live2DWindow = Live2DWindow;
}

void ConfigLive2d::init()
{
    QRect deskRect = QGuiApplication::primaryScreen()->geometry();

    _ModelX=deskRect.width()/2;
    _ModelY=deskRect.height()/2;

}

float ConfigLive2d::getModelX()
{
    return _ModelX;
}

void ConfigLive2d::setModelX(float ModelX)
{
    _ModelX = ModelX;
}

float ConfigLive2d::getModelY()
{
    return _ModelY;
}

void ConfigLive2d::setModelY(float ModelY)
{
    _ModelY = ModelY;
}

float ConfigLive2d::getMouseX()
{
    return _MouseX;
}

void ConfigLive2d::setMouseX(float MouseX)
{
    _MouseX = MouseX;
}

float ConfigLive2d::getMouseY()
{
    return _MouseY;
}

void ConfigLive2d::setMouseY(float MouseY)
{
    _MouseY = MouseY;
}
