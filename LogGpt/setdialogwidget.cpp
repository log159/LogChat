#include "setdialogwidget.h"
#include "ui_setdialogwidget.h"

SetDialogWidget::SetDialogWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetDialogWidget)
{
    ui->setupUi(this);
    init();
    initConnect();
}

SetDialogWidget::~SetDialogWidget()
{
    delete ui;
}

void SetDialogWidget::init()
{
    this->resize(_Width,_Height);
    this->setWindowTitle("设置");
    this->setWindowIcon(QIcon(":/res/u77.svg"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    ui->lineEdit_vits->setText(Config::get_URL_PATH());
    ui->lineEdit_gpt_key->setText(Config::get_OPENAI_KEY());
    ui->lineEdit_baidu_key->setText(Config::get_BAIDU_KEY());
    ui->lineEdit_baidu_appid->setText(Config::get_BAIDU_APID());

    if(Config::get_ENABLE_ROLE()){ui->radioButton_config_enable_yes->setChecked(true);}
    else {ui->radioButton_config_enable_no->setChecked(true);}

    if(Config::get_ENABLE_SOUND()){ui->radioButton_sound_enable_yes->setChecked(true);}
    else{ui->radioButton_sound_enable_no->setChecked(true);}

    if(Config::get_ENABLE_BAIDUFANYI()){ui->radioButton_baidu_enable_yes->setChecked(true);}
    else {ui->radioButton_baidu_enable_no->setChecked(true);}

    if(Config::get_ENABLE_LATERLANGUAGE()){ui->radioButton_baidu_show_enable_yes->setChecked(true);}
    else {ui->radioButton_baidu_show_enable_no->setChecked(true);}

}

void SetDialogWidget::initConnect()
{

    QObject::connect(ui->radioButton_config_enable_yes, &QRadioButton::toggled, [&](){
        qDebug()<<"启用角色扮演";
        if (ui->radioButton_config_enable_yes->isChecked()) {
            qDebug()<<"YES";
            Config::set_ENABLE_ROLE(true);
        } else {
            qDebug()<<"NO";
            Config::set_ENABLE_ROLE(false);
        }
    });
    QObject::connect(ui->radioButton_sound_enable_yes, &QRadioButton::toggled, [&](){
        qDebug()<<"启用VITS语音";
        if (ui->radioButton_sound_enable_yes->isChecked()) {
            qDebug()<<"YES";
            Config::set_ENABLE_SOUND(true);
        } else {
            qDebug()<<"NO";
            Config::set_ENABLE_SOUND(false);
        }
    });

    QObject::connect(ui->radioButton_baidu_enable_yes, &QRadioButton::toggled, [&](){
        qDebug()<<"启用百度翻译";
        if (ui->radioButton_baidu_enable_yes->isChecked()) {
            qDebug()<<"YES";
            Config::set_ENABLE_BAIDUFANYI(true);
        } else {
            qDebug()<<"NO";
            Config::set_ENABLE_BAIDUFANYI(false);
        }
    });
    QObject::connect(ui->radioButton_baidu_show_enable_yes, &QRadioButton::toggled, [&](){
        qDebug()<<"启用百度翻译后的结果显示";
        if (ui->radioButton_baidu_show_enable_yes->isChecked()) {
            qDebug()<<"YES";
            Config::set_ENABLE_LATERLANGUAGE(true);
        } else {
            qDebug()<<"NO";
            Config::set_ENABLE_LATERLANGUAGE(false);
        }
    });
}

void SetDialogWidget::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    qDebug()<<"配置更新成功！";
    Config::set_URL_PORT(ui->lineEdit_vits->text());
    Config::set_OPENAI_KEY(ui->lineEdit_gpt_key->text());
    Config::set_BAIDU_KEY(ui->lineEdit_baidu_key->text());
    Config::set_BAIDU_APID(ui->lineEdit_baidu_appid->text());
}
