#include "live2ddrawitemswidget.h"
#include "ui_live2ddrawitemswidget.h"

Live2DDrawItemsWidget::Live2DDrawItemsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Live2DDrawItemsWidget)
{
    ui->setupUi(this);
}

void Live2DDrawItemsWidget::init(const ChangeConfigItem &modItem)
{
    this->resize(WIDTH,HEIGHT);
    this->setModelItem(modItem);
    ui->lineEdit_name->setReadOnly(true);

    this->setText(modItem.getName());

    ui->horizontalSlider_value->setRange(0,1);
    ui->horizontalSlider_value->setValue(1);
    ui->horizontalSlider_value->setPageStep(0); // disable page step
    ui->lineEdit_value->setEnabled(false);


    ui->lineEdit_value->setText(QString::number(1));

    initConnect();
}

Live2DDrawItemsWidget::~Live2DDrawItemsWidget()
{
    delete ui;
}

QString Live2DDrawItemsWidget::getName() const
{
    return m_ChangeConfigItem.getName();
}

void Live2DDrawItemsWidget::setText(const QString &str)
{
    ui->lineEdit_name->setText(str);
}


void Live2DDrawItemsWidget::setValue(bool bo)
{

    ui->lineEdit_value->setText(bo==true?"1":"0");
    ui->horizontalSlider_value->setValue(bo==true?1:0);
}

int Live2DDrawItemsWidget::getValue() const
{
    return ui->horizontalSlider_value->value();
}

void Live2DDrawItemsWidget::resetValue()
{

    ui->lineEdit_value->setText("1");
    ui->horizontalSlider_value->setValue(1);

}

bool Live2DDrawItemsWidget::isDefault()const
{
    return ui->horizontalSlider_value->value()==1;

}

void Live2DDrawItemsWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        qDebug() << "Pass Live2D Draw Name："<<m_ChangeConfigItem.getName();
        QWidget::mousePressEvent(event);
    }
    else{
        QWidget::mousePressEvent(event);
    }

}

void Live2DDrawItemsWidget::initConnect()
{
    SliderChange slider=&QSlider::sliderMoved;
    connect(ui->horizontalSlider_value,slider,this,[=](int value){

        ui->lineEdit_value->setText(QString::number(value));
        QString handleStr=this->m_HandleStr;
        handleStr=handleStr.arg(m_ChangeConfigItem.getName()).arg(QString::number(value));
        emit sendHandle(handleStr);

    });

    connect(ui->pushButton_reset,&QPushButton::clicked,[=](){
        ui->horizontalSlider_value->setValue(1);
        ui->lineEdit_value->setText("1");

        QString handleStr=this->m_HandleStr;
        handleStr=handleStr.arg(m_ChangeConfigItem.getName()).arg(1);
        emit sendHandle(handleStr);
    });

}
