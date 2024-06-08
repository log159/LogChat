#include "setpushbutton.h"

SetPushButton::SetPushButton(QWidget *parent) : QPushButton(parent)
{
    init();
}

void SetPushButton::init()
{
    this->setFlat(true);
    setNormalStyle();

}
void SetPushButton::setNormalStyle()
{
    this->setStyleSheet("QPushButton{color:black;background-color:transparent;}");
}

void SetPushButton::setEnterStyle()
{
     this->setStyleSheet("QPushButton{color:#dddddd;background-color:transparent;}");
}

void SetPushButton::enterEvent(QEvent *)
{

    emit sendButtonEnter();
    this->setEnterStyle();

}
void SetPushButton::leaveEvent(QEvent *)
{

    this->setNormalStyle();
    emit sendButtonNormal();
}

