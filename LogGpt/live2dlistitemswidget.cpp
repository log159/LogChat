#include "live2dlistitemswidget.h"
#include "ui_live2dlistitemswidget.h"

Live2DListItemsWidget::Live2DListItemsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Live2DListItemsWidget)
{
    ui->setupUi(this);


}

void Live2DListItemsWidget::init(const ModelConfigItem& modItem)
{
    this->resize(_Width,_Height);

    this->setModelItem(modItem);
    this->setText(modItem.getModelName());

    QFile file(":/main.qss");
    if(file.open(QFile::ReadOnly)){
        QString styleSheet = QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
        file.close();
    }
}

Live2DListItemsWidget::~Live2DListItemsWidget()
{
    delete ui;
}

void Live2DListItemsWidget::setText(const QString &str)
{
    ui->label->setText(str);
}

void Live2DListItemsWidget::setChangeIs()
{
    ui->pushButton->setStyleSheet("background-color:#cccccc");
}

void Live2DListItemsWidget::setChangeNo()
{
    ui->pushButton->setStyleSheet("background-color:white");
}

void Live2DListItemsWidget::mousePressEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton)
    {
        qDebug() << "Pass Live2D ListItem Name："<<m_ModelConfigItem.getModelName();
        sendPass(m_ModelConfigItem);
    }
    else
    {
        QWidget::mousePressEvent(event);
    }

}

