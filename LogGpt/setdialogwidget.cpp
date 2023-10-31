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

    ui->lineEdit_vits_address->setText(Config::get_URL_ADDRESSS());
    ui->lineEdit_vits_port->setText(Config::get_URL_PATH());
    for(int i=0;i<Config::get_VITS_ALL_V().size();++i){
        ui->comboBox_vits_select->addItem(Config::get_VITS_ALL_V().at(i));
    }
    ui->comboBox_vits_select->setCurrentIndex(Config::get_VITS_ID());
    ui->lineEdit_speaker_id->setText(QString::number(Config::get_SPEAKER_ID()));
    ui->lineEdit_speaker_emotion->setText(QString::number(Config::get_EMOTION_ID()));
    ui->lineEdit_gpt_key->setText(Config::get_OPENAI_KEY());
    ui->lineEdit_baidu_key->setText(Config::get_BAIDU_KEY());
    ui->lineEdit_baidu_appid->setText(Config::get_BAIDU_APID());

    if(Config::get_ENABLE_ROLE()){ui->radioButton_config_enable_yes->setChecked(true);}
    else {ui->radioButton_config_enable_no->setChecked(true);}

    if(Config::get_ENABLE_SOUND()){ui->radioButton_sound_enable_yes->setChecked(true);}
    else{ui->radioButton_sound_enable_no->setChecked(true);}

    for(int i=0;i<Config::get_LANGUAGE_V().size();++i){
        ui->comboBox_baidu_from->addItem(Config::get_LANGUAGE_V().at(i));
        ui->comboBox_baidu_to->addItem(Config::get_LANGUAGE_V().at(i));
    }
    ui->comboBox_baidu_from->setCurrentIndex(Config::get_BAIDU_FROM_ID());
    ui->comboBox_baidu_to->setCurrentIndex(Config::get_BAIDU_TO_ID());

    if(Config::get_ENABLE_BAIDUFANYI()){ui->radioButton_baidu_enable_yes->setChecked(true);}
    else {ui->radioButton_baidu_enable_no->setChecked(true);}

    if(Config::get_ENABLE_LATERLANGUAGE()){ui->radioButton_baidu_show_enable_yes->setChecked(true);}
    else {ui->radioButton_baidu_show_enable_no->setChecked(true);}

}

void SetDialogWidget::initConnect()
{

    CurrentIndexChanged currentIndexChanged_vits_select=&QComboBox::currentIndexChanged;
    QObject::connect(ui->comboBox_vits_select, currentIndexChanged_vits_select, this,[=](int index){
        qDebug()<<"设置模型为："<<Config::get_VITS_ALL_V().at(index);
        Config::set_VITS_ID(index);
    });

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

    CurrentIndexChanged currentIndexChanged_baidu_from=&QComboBox::currentIndexChanged;
    QObject::connect(ui->comboBox_baidu_from,currentIndexChanged_baidu_from,this,[=](int index){
        qDebug()<<"设置FROM语种为："<<Config::get_LANGUAGE_V().at(index);
        Config::set_BAIDU_FROM_ID(index);
    });

    CurrentIndexChanged currentIndexChanged_baidu_to=&QComboBox::currentIndexChanged;
    QObject::connect(ui->comboBox_baidu_to,currentIndexChanged_baidu_to,this,[=](int index){
        qDebug()<<"设置TO语种为："<<Config::get_LANGUAGE_V().at(index);
        Config::set_BAIDU_TO_ID(index);
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
    Config::set_URL_ADDRESS(ui->lineEdit_vits_address->text());
    Config::set_URL_PORT(ui->lineEdit_vits_port->text());
    Config::set_SPEAKER_ID(ui->lineEdit_speaker_id->text().toInt());
    Config::set_EMOTION_ID(ui->lineEdit_speaker_emotion->text().toInt());
    Config::set_OPENAI_KEY(ui->lineEdit_gpt_key->text());
    Config::set_BAIDU_KEY(ui->lineEdit_baidu_key->text());
    Config::set_BAIDU_APID(ui->lineEdit_baidu_appid->text());

}
