#include "configwindow.h"

QWidget*        ConfigWindow::_WindowPointer      =nullptr;
const QString   ConfigWindow::_WindowTitle        ="LogChat";
const int       ConfigWindow::_StaticMinWidth     =400;
const int       ConfigWindow::_StaticMinHeight    =300;

int ConfigWindow::_StaticPosX;
int ConfigWindow::_StaticPosY;
int ConfigWindow::_StaticWidth;
int ConfigWindow::_StaticHeight;
int ConfigWindow::_DesktopWidth;
int ConfigWindow::_DesktopHeight;
int ConfigWindow::_WindowTransparent = 200;

int ConfigWindow::getDesktopWidth()
{
    return ConfigWindow::_DesktopWidth;
}

int ConfigWindow::getDesktopHeight()
{
    return ConfigWindow::_DesktopHeight;
}


int ConfigWindow::getWindowTransparent()
{
    return _WindowTransparent;
}

void ConfigWindow::setWindowTransparent(int a)
{
    _WindowTransparent = a;
}

void ConfigWindow::init()
{
    QRect deskRect = QGuiApplication::primaryScreen()->geometry();

    ConfigWindow::_DesktopWidth=deskRect.width();
    ConfigWindow::_DesktopHeight=deskRect.height();

//    qDebug()<<deskRect.width()<<" "<<deskRect.height();
    ConfigWindow::_StaticWidth=600;
    ConfigWindow::_StaticHeight=470;
    ConfigWindow::_StaticPosX=(deskRect.width()-ConfigWindow::_StaticWidth)/2;
    ConfigWindow::_StaticPosY=(deskRect.height()-ConfigWindow::_StaticHeight)/2;
}
void ConfigWindow::setStaticPosX(int x){ConfigWindow::_StaticPosX=x;}
void ConfigWindow::setStaticPosY(int y){ConfigWindow::_StaticPosY=y;}
void ConfigWindow::setStaticWidth(int w){
    if(w<=ConfigWindow::_StaticMinWidth){
        w=ConfigWindow::_StaticMinWidth;
        ConfigWindow::_StaticWidth=w;
    }
    ConfigWindow::_StaticWidth=w;
}
void ConfigWindow::setStaticHeight(int h){
    if(h<=ConfigWindow::_StaticMinHeight){
        h=ConfigWindow::_StaticMinHeight;
        ConfigWindow::_StaticHeight=h;
    }
    ConfigWindow::_StaticHeight=h;
}

int ConfigWindow::getStaticPosX(){return ConfigWindow::_StaticPosX;}
int ConfigWindow::getStaticPosY(){return ConfigWindow::_StaticPosY;}
int ConfigWindow::getStaticWidth(){return ConfigWindow::_StaticWidth;}
int ConfigWindow::getStaticHeight(){return ConfigWindow::_StaticHeight;}
