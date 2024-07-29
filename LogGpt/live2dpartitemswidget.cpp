#include "live2dpartitemswidget.h"
#include "ui_live2dpartitemswidget.h"

Live2DPartItemsWidget::Live2DPartItemsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Live2DPartItemsWidget)
{
    ui->setupUi(this);
}

void Live2DPartItemsWidget::init(const ModelPartItem& modItem)
{
    this->resize(WIDTH,HEIGHT);
    this->setModelItem(modItem);
    ui->lineEdit_name->setReadOnly(true);
    ui->lineEdit_explain->setReadOnly(true);


    this->setText(modItem.getName());

    ui->horizontalSlider_value->setRange(int(m_ModelPartItem.getMinValue()),int(m_ModelPartItem.getMaxValue()));
    ui->horizontalSlider_value->setValue(int(m_ModelPartItem.getDefaultValue()));
    ui->horizontalSlider_value->setPageStep(0); // disable page step
    ui->lineEdit_value->setEnabled(false);


    int vl=qAbs(int(m_ModelPartItem.getDefaultValue())/100);
    int vr1=qAbs(int(m_ModelPartItem.getDefaultValue())/10%10);
    int vr2=qAbs(int(m_ModelPartItem.getDefaultValue())%10);
    QString str="";
    if(m_ModelPartItem.getDefaultValue()<0){
        str+="-";
    }
    str+=(QString::number(vl)+"."+QString::number(vr1)+QString::number(vr2));
    ui->lineEdit_value->setText(str);

    initConnect();
}

Live2DPartItemsWidget::~Live2DPartItemsWidget()
{
    delete ui;
}

QString Live2DPartItemsWidget::getName() const
{
    return m_ModelPartItem.getName();
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

int Live2DPartItemsWidget::getValue() const
{
    return ui->horizontalSlider_value->value();
}

void Live2DPartItemsWidget::resetValue()
{
    int vl=qAbs(int(m_ModelPartItem.getDefaultValue())/100);
    int vr1=qAbs(int(m_ModelPartItem.getDefaultValue())/10%10);
    int vr2=qAbs(int(m_ModelPartItem.getDefaultValue())%10);
    QString str="";
    if(m_ModelPartItem.getDefaultValue()<0){
        str+="-";
    }
    str+=(QString::number(vl)+"."+QString::number(vr1)+QString::number(vr2));
    ui->lineEdit_value->setText(str);
    ui->horizontalSlider_value->setValue(int(m_ModelPartItem.getDefaultValue()));

}

bool Live2DPartItemsWidget::isDefault()const
{
    return ui->horizontalSlider_value->value()==m_ModelPartItem.getDefaultValue();

}

void Live2DPartItemsWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        qDebug() << "Pass Live2D partItem Name："<<m_ModelPartItem.getName();

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

        int vl=qAbs(int(value)/100);
        int vr1=qAbs(int(value)/10%10);
        int vr2=qAbs(int(value)%10);
        QString str="";
        if(value<0){str+="-";}
        str+=(QString::number(vl)+"."+QString::number(vr1)+QString::number(vr2));
        ui->lineEdit_value->setText(str);
        QString handleStr="Item:%1,%2;";
        handleStr=handleStr.arg(m_ModelPartItem.getName()).arg(QString::number(value));
        emit sendHandle(handleStr);

    });

    connect(ui->pushButton_reset,&QPushButton::clicked,[=](){
        ui->horizontalSlider_value->setValue(int(m_ModelPartItem.getDefaultValue()));
        int vl=qAbs(int(m_ModelPartItem.getDefaultValue())/100);
        int vr1=qAbs(int(m_ModelPartItem.getDefaultValue())/10%10);
        int vr2=qAbs(int(m_ModelPartItem.getDefaultValue())%10);
        QString str="";
        if(m_ModelPartItem.getDefaultValue()<0){
            str+="-";
        }
        str+=(QString::number(vl)+"."+QString::number(vr1)+QString::number(vr2));
        ui->lineEdit_value->setText(str);

        QString handleStr="Item:%1,%2;";
        handleStr=handleStr.arg(m_ModelPartItem.getName()).arg(QString::number(m_ModelPartItem.getDefaultValue()));
        emit sendHandle(handleStr);
    });
}
