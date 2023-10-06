#include "botitemswidget.h"
#include "ui_botitemswidget.h"

BotItemsWidget::BotItemsWidget(QWidget *parent) :
    ListItemsWidget(parent),
    ui(new Ui::BotItemsWidget)
{
    ui->setupUi(this);
    init();

}

BotItemsWidget::~BotItemsWidget()
{
    delete ui;
}

void BotItemsWidget::init()
{
    this->m_IconLab->move(3,3);
    QPixmap img;
    img.load(":/res/ChatIcon.png");
    img = img.scaled(this->m_IconLab->width(),this->m_IconLab->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->m_IconLab->setPixmap(img);
    this->m_IconLab->show();
}
