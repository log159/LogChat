#include "useritemswidget.h"
#include "ui_useritemswidget.h"

UserItemsWidget::UserItemsWidget(QWidget *parent) :
    ListItemsWidget(parent),
    ui(new Ui::UserItemsWidget)
{
    ui->setupUi(this);
    init();

}

UserItemsWidget::~UserItemsWidget()
{
    delete ui;
}

void UserItemsWidget::init()
{
    this->m_IconLab->move(this->width()-m_IconLab->width()-3,3);
    QPixmap img;
    img.load(":/res/UserIcon.png");
    img = img.scaled(this->m_IconLab->width(),this->m_IconLab->height(),Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->m_IconLab->setPixmap(img);
    this->m_IconLab->show();
}
