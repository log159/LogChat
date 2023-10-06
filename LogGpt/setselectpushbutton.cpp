#include "setselectpushbutton.h"

SetSelectPushButton::SetSelectPushButton(QWidget *parent) : QPushButton(parent)
{
    init();
}

void SetSelectPushButton::init()
{
    this->setFixedSize(30,80);
    this->setText(">>");
}

void SetSelectPushButton::zoom()
{
    if(m_ZoomId==false)
    {
        zoom1();
    }
    else {
        zoom2();
    }
    m_ZoomId=!m_ZoomId;
}
void SetSelectPushButton::zoom1()
{
    //创建动画对象
    QPropertyAnimation * animation=new QPropertyAnimation(this,"geometry");
    //动画间隔
    animation->setDuration(200);
    //开始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x()+100,this->y(),this->width(),this->height()));
    //设置动画曲线
    animation->setEasingCurve(QEasingCurve::Linear);
    //执行后销毁
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    this->setText("<<");


}

void SetSelectPushButton::zoom2()
{
    //创建动画对象
    QPropertyAnimation * animation=new QPropertyAnimation(this,"geometry");
    //动画间隔
    animation->setDuration(200);
    //开始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x()-100,this->y(),this->width(),this->height()));
    //设置动画曲线
    animation->setEasingCurve(QEasingCurve::Linear);
    //执行
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    this->setText(">>");
}
