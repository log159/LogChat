#include "setconfigdialogwidget.h"
#include "ui_setconfigdialogwidget.h"

SetConfigDialogWidget::SetConfigDialogWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetConfigDialogWidget)
{
    ui->setupUi(this);
    init();
    initConnect();

}

SetConfigDialogWidget::~SetConfigDialogWidget()
{
    delete ui;
}
void SetConfigDialogWidget::init()
{
    this->resize(_Width,_Height);
    this->setWindowTitle("聊天设置");
    this->setWindowIcon(QIcon(":/res/u77.svg"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->horizontalSlider_reserve->setRange(0,100);
    ui->horizontalSlider_reserve->setValue(Config::get_RESERVE_LONG());

    QRegExpValidator* validator=new QRegExpValidator(QRegExp("[0-9]{1,2}|100"));
    ui->lineEdit_reserve->setValidator(validator);
    ui->lineEdit_reserve->setText(QString::number(Config::get_RESERVE_LONG()));

    ui->textEdit_character->setText(Config::get_CHARACTER_CONFIG());

    if(Config::get_ENABLE_RESERVE()){ui->radioButton_reserve->setChecked(true);}
    else {ui->radioButton_reserve->setChecked(false);}

    QFile file(":/main.qss");
    if(file.open(QFile::ReadOnly)){
        QString styleSheet = QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
        file.close();
    }

}

void SetConfigDialogWidget::initConnect()
{
    QObject::connect(ui->radioButton_reserve, &QRadioButton::toggled, [&](){
        qDebug()<<"启用联系上下文";
        if (ui->radioButton_reserve->isChecked()) {
            qDebug()<<"YES";
            Config::set_ENABLE_RESERVE(true);
        } else {
            qDebug()<<"NO";
            Config::set_ENABLE_RESERVE(false);
        }
    });

    QObject::connect(ui->lineEdit_reserve, &QLineEdit::textChanged, [=](const QString &text){
        bool ok;
        int value = text.toInt(&ok);
        if (ok) {
            ui->horizontalSlider_reserve->setValue(value);
        }
    });


    SliderMoved sliderMoved=&QSlider::sliderMoved;
    QObject::connect(ui->horizontalSlider_reserve,sliderMoved,this,[=](int value){
        ui->lineEdit_reserve->setText(QString::number(value));
    });

}
void SetConfigDialogWidget::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    qDebug()<<"聊天配置更新成功！";
    Config::set_CHARACTER_CONFIG(ui->textEdit_character->toPlainText());
    Config::set_RESERVE_LONG(ui->horizontalSlider_reserve->value());


}
