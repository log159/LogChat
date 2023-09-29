#include "useritemswidget.h"
#include "ui_useritemswidget.h"

UserItemsWidget::UserItemsWidget(QWidget *parent) :
    ListItemsWidget(parent),
    ui(new Ui::UserItemsWidget)
{
    ui->setupUi(this);

    this->_Icon_lab->move(this->width()-_Icon_lab->width()-3,3);
    QPixmap img;
    img.load(":/res/UserIcon.png");
    img = img.scaled(this->_Icon_lab->width(),this->_Icon_lab->height(),Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->_Icon_lab->setPixmap(img);
    this->_Icon_lab->show();
}

UserItemsWidget::~UserItemsWidget()
{
    delete ui;
}
