#include "configwindow.h"

int ConfigWindow::_StaticPosX;
int ConfigWindow::_StaticPosY;
int ConfigWindow::_StaticWidth;
int ConfigWindow::_StaticHeight;

void ConfigWindow::init()
{
    QRect deskRect = QGuiApplication::primaryScreen()->geometry();

//    qDebug()<<deskRect.width()<<" "<<deskRect.height();
    _StaticWidth=deskRect.width()/2;
    _StaticHeight=int(_StaticWidth*0.618);
    _StaticPosX=(deskRect.width()-_StaticWidth)/2;
    _StaticPosY=(deskRect.height()-_StaticHeight)/2;
}
void ConfigWindow::setStaticPosX(int x){_StaticPosX=x;}
void ConfigWindow::setStaticPosY(int y){_StaticPosY=y;}
void ConfigWindow::setStaticWidth(int w){_StaticWidth=w;}
void ConfigWindow::setStaticHeight(int h){_StaticHeight=h;}

int ConfigWindow::getStaticPosX(){return _StaticPosX;}
int ConfigWindow::getStaticPosY(){return _StaticPosY;}
int ConfigWindow::getStaticWidth(){return _StaticWidth;}
int ConfigWindow::getStaticHeight(){return _StaticHeight;}
