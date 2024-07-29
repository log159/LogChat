#include "windowbutton.h"

WindowButton::WindowButton(QWidget *parent) : QPushButton(parent)
{
    init();
}

void WindowButton::setSelfIcon(const QString &path)
{
    QIcon icon(path);
    this->setIcon(icon);
    this->setIconSize(this->size()); // 可选：设置图标的大小

}

void WindowButton::init()
{
    this->setFixedSize(BUTTON_SIZE,BUTTON_SIZE);
}

void WindowButton::enterEvent(QEvent *event)
{
    emit entered();
    QPushButton::enterEvent(event);
}

void WindowButton::leaveEvent(QEvent *event)
{
    emit left();
    QPushButton::leaveEvent(event);
}
