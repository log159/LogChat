#include "live2dexpandmotitemswidget.h"
#include "ui_live2dexpandmotitemswidget.h"

Live2dExpAndMotItemsWidget::Live2dExpAndMotItemsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Live2dExpAndMotItemsWidget)
{
    ui->setupUi(this);
}

Live2dExpAndMotItemsWidget::~Live2dExpAndMotItemsWidget()
{
    delete ui;
}

void Live2dExpAndMotItemsWidget::init(const QPair<QString, int> &data)
{
    this->resize(WIDTH,HEIGHT);
    this->setData(data);
    ui->lineEdit_name->setText(data.first);
    ui->lineEdit_id->setText(QString::number(data.second));


    ui->lineEdit_name->setReadOnly(true);
    ui->lineEdit_id->setReadOnly(true);

    initConnect();
}

void Live2dExpAndMotItemsWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        qDebug() << "Pass Live2D Expression Name："<<m_Data.first;
        QWidget::mousePressEvent(event);
    }
    else{
        QWidget::mousePressEvent(event);
    }
}

void Live2dExpAndMotItemsWidget::initConnect()
{
    connect(ui->pushButton_lookat,&QPushButton::clicked,[=](){
        QString handleStr=this->m_HandleStr;
        handleStr=handleStr.arg("1").arg(m_Data.second);
        emit sendHandle(handleStr);
    });
}
