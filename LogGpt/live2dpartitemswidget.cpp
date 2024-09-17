#include "live2dpartitemswidget.h"
#include "ui_live2dpartitemswidget.h"

Live2DPartItemsWidget::Live2DPartItemsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Live2DPartItemsWidget)
{
    ui->setupUi(this);
}

void Live2DPartItemsWidget::init(const ChangeConfigItem& modItem)
{
    this->resize(WIDTH,HEIGHT);
    this->setModelItem(modItem);
    ui->lineEdit_name->setReadOnly(true);
    ui->lineEdit_explain->setReadOnly(true);
    this->setText(modItem.getName());
    ui->horizontalSlider_value->setRange(int(m_ChangeConfigItem.getMinValue()),int(m_ChangeConfigItem.getMaxValue()));
    ui->horizontalSlider_value->setValue(int(m_ChangeConfigItem.getDefaultValue()));
    ui->horizontalSlider_value->setPageStep(0);
    ui->lineEdit_value->setEnabled(false);
    ui->lineEdit_value->setText(Transformation::IntToStringF2(m_ChangeConfigItem.getDefaultValue()));

    initConnect();
}

Live2DPartItemsWidget::~Live2DPartItemsWidget()
{
    delete ui;
}

QString Live2DPartItemsWidget::getName() const
{
    return m_ChangeConfigItem.getName();
}

void Live2DPartItemsWidget::setText(const QString &str)
{
    ui->lineEdit_name->setText(str);
}

void Live2DPartItemsWidget::setExplain(const QString &str)
{
    ui->lineEdit_explain->setText(str);
}

void Live2DPartItemsWidget::setValue(int val)
{
    ui->lineEdit_value->setText(Transformation::IntToStringF2(val));

    ui->horizontalSlider_value->setValue(int(val));
}

int Live2DPartItemsWidget::getValue() const
{
    return ui->horizontalSlider_value->value();
}

void Live2DPartItemsWidget::resetValue()
{
    ui->lineEdit_value->setText(Transformation::IntToStringF2(m_ChangeConfigItem.getDefaultValue()));

    ui->horizontalSlider_value->setValue(int(m_ChangeConfigItem.getDefaultValue()));

}

bool Live2DPartItemsWidget::isDefault()const
{
    return ui->horizontalSlider_value->value()==m_ChangeConfigItem.getDefaultValue();

}

void Live2DPartItemsWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        qDebug() << "Pass Live2D Part Name："<<m_ChangeConfigItem.getName();

        QWidget::mousePressEvent(event);
    }
    else
    {
        QWidget::mousePressEvent(event);
    }
}

void Live2DPartItemsWidget::initConnect()
{
    SliderChange slider=&QSlider::sliderMoved;
    connect(ui->horizontalSlider_value,slider,this,[=](int value){
        ui->lineEdit_value->setText(Transformation::IntToStringF2(value));
        QString handleStr=this->m_HandleStr;
        handleStr=handleStr.arg(m_ChangeConfigItem.getName()).arg(QString::number(value));
        emit sendHandle(handleStr);

    });

    connect(ui->pushButton_reset,&QPushButton::clicked,[=](){
        ui->horizontalSlider_value->setValue(int(m_ChangeConfigItem.getDefaultValue()));
        ui->lineEdit_value->setText(Transformation::IntToStringF2(m_ChangeConfigItem.getDefaultValue()));
        QString handleStr=this->m_HandleStr;
        handleStr=handleStr.arg(m_ChangeConfigItem.getName()).arg(QString::number(m_ChangeConfigItem.getDefaultValue()));
        emit sendHandle(handleStr);
    });
}
