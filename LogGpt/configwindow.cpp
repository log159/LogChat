#include "configwindow.h"

QWidget*        ConfigWindow::WindowPointer      =nullptr;
const QString   ConfigWindow::WindowTitle        ="LogChat";
const int       ConfigWindow::StaticMinWidth     =400;
const int       ConfigWindow::StaticMinHeight    =300;

int ConfigWindow::StaticPosX;
int ConfigWindow::StaticPosY;
int ConfigWindow::StaticWidth;
int ConfigWindow::StaticHeight;
int ConfigWindow::DesktopWidth;
int ConfigWindow::DesktopHeight;
int ConfigWindow::WindowTransparent = 200;

int ConfigWindow::getDesktopWidth()
{
    return ConfigWindow::DesktopWidth;
}

int ConfigWindow::getDesktopHeight()
{
    return ConfigWindow::DesktopHeight;
}


int ConfigWindow::getWindowTransparent()
{
    return WindowTransparent;
}

void ConfigWindow::setWindowTransparent(int a)
{
    WindowTransparent = a;
}

QWidget *ConfigWindow::getWindowPointer()
{
    return WindowPointer;
}

void ConfigWindow::init()
{
    QRect deskRect = QGuiApplication::primaryScreen()->geometry();

    ConfigWindow::DesktopWidth=deskRect.width();
    ConfigWindow::DesktopHeight=deskRect.height();

//    qDebug()<<deskRect.width()<<" "<<deskRect.height();
    ConfigWindow::StaticWidth=600;
    ConfigWindow::StaticHeight=470;
    ConfigWindow::StaticPosX=(deskRect.width()-ConfigWindow::StaticWidth)/2;
    ConfigWindow::StaticPosY=(deskRect.height()-ConfigWindow::StaticHeight)/2;
}

void ConfigWindow::setWindowPointer(QWidget *ptr)
{
    WindowPointer=ptr;
}
void ConfigWindow::setStaticPosX(int x){ConfigWindow::StaticPosX=x;}
void ConfigWindow::setStaticPosY(int y){ConfigWindow::StaticPosY=y;}
void ConfigWindow::setStaticWidth(int w){
    if(w<=ConfigWindow::StaticMinWidth){
        w=ConfigWindow::StaticMinWidth;
        ConfigWindow::StaticWidth=w;
    }
    ConfigWindow::StaticWidth=w;
}
void ConfigWindow::setStaticHeight(int h){
    if(h<=ConfigWindow::StaticMinHeight){
        h=ConfigWindow::StaticMinHeight;
        ConfigWindow::StaticHeight=h;
    }
    ConfigWindow::StaticHeight=h;
}

int ConfigWindow::getStaticPosX(){return ConfigWindow::StaticPosX;}
int ConfigWindow::getStaticPosY(){return ConfigWindow::StaticPosY;}
int ConfigWindow::getStaticWidth(){return ConfigWindow::StaticWidth;}
int ConfigWindow::getStaticHeight(){return ConfigWindow::StaticHeight;}
