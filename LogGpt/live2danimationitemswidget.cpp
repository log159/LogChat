#include "live2danimationitemswidget.h"
#include "ui_live2danimationitemswidget.h"

Live2DAnimationItemsWidget::Live2DAnimationItemsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Live2DAnimationItemsWidget)
{
    ui->setupUi(this);

    init();
}

Live2DAnimationItemsWidget::~Live2DAnimationItemsWidget()
{
    delete ui;
}

void Live2DAnimationItemsWidget::setName(const QString &str)
{
    ui->lineEdit_name->setText(str);
}

void Live2DAnimationItemsWidget::setExplain(const QString &str)
{
    ui->lineEdit_explain->setText(str);
}

void Live2DAnimationItemsWidget::setRule(int index)
{
    ui->comboBox_rule->setCurrentIndex(index);
}

void Live2DAnimationItemsWidget::setUseful(bool bo)
{
    ui->checkBox_use->setChecked(bo);

}

void Live2DAnimationItemsWidget::setSpeed(int val)
{
    ui->lineEdit_speed->setText(QString::number(val));
}

void Live2DAnimationItemsWidget::init()
{
    ui->comboBox_rule->addItem("标准谐波");
    ui->comboBox_rule->addItem("随机谐波");
    ui->comboBox_rule->addItem("随机高斯分布谐波");


    QRegExpValidator* validator=new QRegExpValidator(QRegExp("[0-9]{1,2}|100"));
    ui->lineEdit_speed->setValidator(validator);
    ui->lineEdit_speed->setText(QString::number(0)+" %");

    ui->lineEdit_name->setReadOnly(true);
    ui->lineEdit_explain->setReadOnly(true);




}

void Live2DAnimationItemsWidget::initConnect()
{
//    QObject::connect(ui->lineEdit_speed, &QLineEdit::textChanged, [=](const QString &text){
//        bool ok;
//        int value = text.toInt(&ok);
//        if (ok) {
//            ui->lineEdit_speed->setValue(value);
//        }
//    });


}
