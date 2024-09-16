#include "live2dparamitemswidget.h"
#include "ui_live2dparamitemswidget.h"


Live2DParamItemsWidget::Live2DParamItemsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Live2DParamItemsWidget)
{
    ui->setupUi(this);
}

void Live2DParamItemsWidget::init(const ChangeConfigItem& modItem)
{
    this->resize(WIDTH,HEIGHT);
    this->setModelItem(modItem);
    ui->lineEdit_name->setReadOnly(true);
    ui->lineEdit_explain->setReadOnly(true);
    this->setText(modItem.getName());
    ui->horizontalSlider_value->setRange(int(m_ChangeConfigItem.getMinValue()),int(m_ChangeConfigItem.getMaxValue()));
    ui->horizontalSlider_value->setValue(int(m_ChangeConfigItem.getDefaultValue()));
    ui->horizontalSlider_value->setPageStep(0); // disable page step
    ui->lineEdit_value->setEnabled(false);

    int vl=qAbs(int(m_ChangeConfigItem.getDefaultValue())/100);
    int vr1=qAbs(int(m_ChangeConfigItem.getDefaultValue())/10%10);
    int vr2=qAbs(int(m_ChangeConfigItem.getDefaultValue())%10);
    QString str="";
    if(m_ChangeConfigItem.getDefaultValue()<0){
        str+="-";
    }
    str+=(QString::number(vl)+"."+QString::number(vr1)+QString::number(vr2));
    ui->lineEdit_value->setText(str);

    initConnect();
}

Live2DParamItemsWidget::~Live2DParamItemsWidget()
{
    delete ui;
}

QString Live2DParamItemsWidget::getName() const
{
    return m_ChangeConfigItem.getName();
}

void Live2DParamItemsWidget::setText(const QString &str)
{
    ui->lineEdit_name->setText(str);
}

void Live2DParamItemsWidget::setExplain(const QString &str)
{
    ui->lineEdit_explain->setText(str);
}

void Live2DParamItemsWidget::setValue(int val)
{
    int vl=qAbs(int(val)/100);
    int vr1=qAbs(int(val)/10%10);
    int vr2=qAbs(int(val)%10);
    QString str="";
    if(val<0){
        str+="-";
    }
    str+=(QString::number(vl)+"."+QString::number(vr1)+QString::number(vr2));
    ui->lineEdit_value->setText(str);
    ui->horizontalSlider_value->setValue(int(val));
}

int Live2DParamItemsWidget::getValue() const
{
    return ui->horizontalSlider_value->value();
}

void Live2DParamItemsWidget::resetValue()
{
    int vl=qAbs(int(m_ChangeConfigItem.getDefaultValue())/100);
    int vr1=qAbs(int(m_ChangeConfigItem.getDefaultValue())/10%10);
    int vr2=qAbs(int(m_ChangeConfigItem.getDefaultValue())%10);
    QString str="";
    if(m_ChangeConfigItem.getDefaultValue()<0){
        str+="-";
    }
    str+=(QString::number(vl)+"."+QString::number(vr1)+QString::number(vr2));
    ui->lineEdit_value->setText(str);
    ui->horizontalSlider_value->setValue(int(m_ChangeConfigItem.getDefaultValue()));

}

bool Live2DParamItemsWidget::isDefault()const
{
    return ui->horizontalSlider_value->value()==m_ChangeConfigItem.getDefaultValue();

}

void Live2DParamItemsWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        qDebug() << "Pass Live2D Param Name："<<m_ChangeConfigItem.getName();

        QWidget::mousePressEvent(event);
    }
    else
    {
        QWidget::mousePressEvent(event);
    }
}

void Live2DParamItemsWidget::initConnect()
{
    SliderChange slider=&QSlider::sliderMoved;
    connect(ui->horizontalSlider_value,slider,this,[=](int value){

        int vl=qAbs(int(value)/100);
        int vr1=qAbs(int(value)/10%10);
        int vr2=qAbs(int(value)%10);
        QString str="";
        if(value<0){str+="-";}
        str+=(QString::number(vl)+"."+QString::number(vr1)+QString::number(vr2));
        ui->lineEdit_value->setText(str);
        QString handleStr=this->m_HandleStr;
        handleStr=handleStr.arg(m_ChangeConfigItem.getName()).arg(QString::number(value));
        emit sendHandle(handleStr);

    });

    connect(ui->pushButton_reset,&QPushButton::clicked,[=](){
        ui->horizontalSlider_value->setValue(int(m_ChangeConfigItem.getDefaultValue()));
        int vl=qAbs(int(m_ChangeConfigItem.getDefaultValue())/100);
        int vr1=qAbs(int(m_ChangeConfigItem.getDefaultValue())/10%10);
        int vr2=qAbs(int(m_ChangeConfigItem.getDefaultValue())%10);
        QString str="";
        if(m_ChangeConfigItem.getDefaultValue()<0){
            str+="-";
        }
        str+=(QString::number(vl)+"."+QString::number(vr1)+QString::number(vr2));
        ui->lineEdit_value->setText(str);

        QString handleStr=this->m_HandleStr;
        handleStr=handleStr.arg(m_ChangeConfigItem.getName()).arg(QString::number(m_ChangeConfigItem.getDefaultValue()));
        emit sendHandle(handleStr);
    });
}
