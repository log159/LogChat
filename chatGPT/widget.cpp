#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle(_WindowTitle);
    this->setWindowIcon(QIcon(":/res/u77.svg"));
    this->setFixedSize(_Width,_Height);
    _pushandreceiveWidget=new PushAndReceiveWidget(this);
    _pushandreceiveWidget->show();

}

Widget::~Widget()
{
    delete ui;
}


