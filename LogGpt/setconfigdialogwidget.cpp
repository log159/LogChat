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
    qDebug()<<"SetConfigDialogWidget 析构";
    delete ui;
}
void SetConfigDialogWidget::init()
{
    this->resize(WIDTH,HEIGHT);
    this->setWindowTitle("聊天设置");
    this->setWindowIcon(QIcon(":/res/u77.svg"));
    setWindowFlags((windowFlags() & ~Qt::WindowContextHelpButtonHint) | Qt::WindowStaysOnTopHint);
    ui->horizontalSlider_reserve->setRange(0,100);
    ui->horizontalSlider_reserve->setValue(Config::get_USER(::EnUser::RESERVE_LONG).toInt());

    QRegExpValidator* validator=new QRegExpValidator(QRegExp("[0-9]{1,2}|100"));
    ui->lineEdit_reserve->setValidator(validator);
    ui->lineEdit_reserve->setText(QString::number(Config::get_USER(::EnUser::RESERVE_LONG).toInt()));

    ui->textEdit_character->setText(Config::get_USER(::EnUser::CHARACTER_CONFIG));

    if(Config::get_USER(::EnUser::ENABLE_RESERVE).toInt()!=0){ui->radioButton_reserve->setChecked(true);}
    else {ui->radioButton_reserve->setChecked(false);}


    if(Config::get_USER(::EnUser::CHARACTERGENDER).toInt()==0){ui->radioButton_man->setChecked(true);}
    else{ui->radioButton_woman->setChecked(true);}

    ui->lineEdit_username->setText(Config::get_USER(::EnUser::USERNAME));
    ui->lineEdit_charactername->setText(Config::get_USER(::EnUser::CHARACTERNAME));


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
            Config::set_USER(::EnUser::ENABLE_RESERVE,"1");
        } else {
            qDebug()<<"NO";
            Config::set_USER(::EnUser::ENABLE_RESERVE,"0");
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
        Config::set_USER(::EnUser::RESERVE_LONG,QString::number(value));
        qDebug()<<"联系上下文长度更新到："<<value;
        ui->lineEdit_reserve->setText(QString::number(value));
    });


    QObject::connect(ui->radioButton_man,&QRadioButton::toggled,[=](){
        if(ui->radioButton_man->isChecked()){
            qDebug()<<"角色性别:男";
            Config::set_USER(::EnUser::CHARACTERGENDER,"0");
        }
        else {
            qDebug()<<"角色性别:女";
            Config::set_USER(::EnUser::CHARACTERGENDER,"1");
        }
    });

}
void SetConfigDialogWidget::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    qDebug()<<"聊天配置更新成功！";
    Config::set_USER(::EnUser::CHARACTER_CONFIG,ui->textEdit_character->toPlainText());
    Config::set_USER(::EnUser::RESERVE_LONG,QString::number(ui->horizontalSlider_reserve->value()));

    Config::set_USER(::EnUser::USERNAME,ui->lineEdit_username->text());
    Config::set_USER(::EnUser::CHARACTERNAME,ui->lineEdit_charactername->text());

}
