#include "botitemswidget.h"
#include "ui_botitemswidget.h"

BotItemsWidget::BotItemsWidget(QWidget *parent) :
    ListItemsWidget(parent),
    ui(new Ui::BotItemsWidget)
{
    ui->setupUi(this);

    this->_Icon_lab->move(3,3);
    QPixmap img;
    img.load(":/res/ChatIcon.png");
    img = img.scaled(this->_Icon_lab->width(),this->_Icon_lab->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->_Icon_lab->setPixmap(img);
    this->_Icon_lab->show();
}

BotItemsWidget::~BotItemsWidget()
{
    delete ui;
}
