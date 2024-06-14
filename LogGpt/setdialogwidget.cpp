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
    this->setWindowTitle("基本设置");
    this->setWindowIcon(QIcon(":/res/u77.svg"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    ui->tabWidget->setCurrentIndex(0);

    for(int i=0;i<VITS_MODEL_V.size();++i){
        ui->comboBox_vitsmodel_select->addItem(VITS_MODEL_V.at(i));
    }
    ui->comboBox_vitsmodel_select->setCurrentIndex(Config::get_USER(::EnUser::VITS_MODEL_SELECT).toInt());

    for(int i=0;i<GPTSOVITS_LANGUAGE_V.size();++i){
        ui->comboBox_gptsovits_language->addItem(GPTSOVITS_LANGUAGE_V.at(i));
    }
    ui->comboBox_gptsovits_language->setCurrentIndex(Config::get_USER(::EnUser::GPTSOVITS_LANGUAGE).toInt());

    ui->lineEdit_gptsovits_address->setText(Config::get_USER(::EnUser::GPTSOVITS_URL_ADDRESS));
    ui->lineEdit_gptsovits_port->setText(Config::get_USER(::EnUser::GPTSOVITS_URL_PORT));

    ui->lineEdit_vits_address->setText(Config::get_USER(::EnUser::VITS_URL_ADDRESS));
    ui->lineEdit_vits_port->setText(Config::get_USER(::EnUser::VITS_URL_PORT));
    for(int i=0;i<VITS_ALL_V.size();++i){
        ui->comboBox_vits_select->addItem(VITS_ALL_V.at(i));
    }
    ui->comboBox_vits_select->setCurrentIndex(Config::get_USER(::EnUser::VITS_ID).toInt());
    ui->lineEdit_speaker_id->setText(QString::number(Config::get_USER(::EnUser::SPEAKER_ID).toInt()));
    ui->lineEdit_speaker_emotion->setText(QString::number(Config::get_USER(::EnUser::EMOTION_ID).toInt()));

    if(Config::get_USER(::EnUser::LLM_MODEL_ID).toInt()==0){ui->radioButton_llm_chatgpt->setChecked(true);}
    else if(Config::get_USER(::EnUser::LLM_MODEL_ID).toInt()==1){ui->radioButton_llm_xfxh->setChecked(true);}

    for(int i=0;i<CHATGPT_MODEL_V.size();++i){
        ui->comboBox_llm_chatgpt->addItem(CHATGPT_MODEL_V.at(i));
    }
    for(int i=0;i<XFXH_MODEL_V.size();++i){
        ui->comboBox_llm_xfxh->addItem(XFXH_MODEL_V.at(i));
    }
    ui->comboBox_llm_xfxh->setCurrentIndex(Config::get_USER(::EnUser::XFXH_MODEL_ID).toInt());

    ui->lineEdit_gpt_key->setText(Config::get_IKS(::EnIks::LLM_CHATGPT).key);
    ui->lineEdit_gpt_url->setText(Config::get_URL(::EnUrl::URL_CHATGPT_BASEURL));
    ui->lineEdit_xfxh_appid->setText(Config::get_IKS(::EnIks::LLM_XFXH).id);
    ui->lineEdit_xfxh_apikey->setText(Config::get_IKS(::EnIks::LLM_XFXH).key);
    ui->lineEdit_xfxh_apisecret->setText(Config::get_IKS(::EnIks::LLM_XFXH).secret);
    ui->lineEdit_baidu_appid->setText(Config::get_IKS(::EnIks::MT_BDFY).id);
    ui->lineEdit_baidu_key->setText(Config::get_IKS(::EnIks::MT_BDFY).key);
    ui->lineEdit_baidusound_key->setText(Config::get_IKS(::EnIks::STT_BDYUN).key);
    ui->lineEdit_baidusound_secret->setText(Config::get_IKS(::EnIks::STT_BDYUN).secret);

    if(Config::get_USER(::EnUser::ENABLE_ROLE).toInt()!=0){ui->radioButton_config_enable_yes->setChecked(true);}
    else {ui->radioButton_config_enable_no->setChecked(true);}

    if(Config::get_USER(::EnUser::ENABLE_SOUND).toInt()!=0){ui->radioButton_sound_enable_yes->setChecked(true);}
    else{ui->radioButton_sound_enable_no->setChecked(true);}

    for(int i=0;i<LANGUAGE_V.size();++i){
        ui->comboBox_baidu_from->addItem(LANGUAGE_V.at(i));
        ui->comboBox_baidu_to->addItem(LANGUAGE_V.at(i));
    }
    ui->comboBox_baidu_from->setCurrentIndex(Config::get_USER(::EnUser::BAIDU_FROM_ID).toInt());
    ui->comboBox_baidu_to->setCurrentIndex(Config::get_USER(::EnUser::BAIDU_TO_ID).toInt());

    if(Config::get_USER(::EnUser::ENABLE_BAIDUFANYI).toInt()!=0){ui->radioButton_baidu_enable_yes->setChecked(true);}
    else {ui->radioButton_baidu_enable_no->setChecked(true);}

    if(Config::get_USER(::EnUser::ENABLE_LATERLANGUAGE).toInt()!=0){ui->radioButton_baidu_show_enable_yes->setChecked(true);}
    else {ui->radioButton_baidu_show_enable_no->setChecked(true);}


    QFile file(":/main.qss");
    if(file.open(QFile::ReadOnly)){
        QString styleSheet = QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
        file.close();
    }

}

void SetDialogWidget::initConnect()
{

    CurrentIndexChanged currentIndexChanged_vits_model_select=&QComboBox::currentIndexChanged;
    QObject::connect(ui->comboBox_vitsmodel_select,currentIndexChanged_vits_model_select,this,[=](int index){
        qDebug()<<"设置选择的Vits为:"<<VITS_MODEL_V.at(index);
        Config::set_USER(::EnUser::VITS_MODEL_SELECT,QString::number(index));
    });

    CurrentIndexChanged currentIndexChanged_vits_select=&QComboBox::currentIndexChanged;
    QObject::connect(ui->comboBox_vits_select, currentIndexChanged_vits_select, this,[=](int index){
        qDebug()<<"设置Vits模型为:"<<VITS_ALL_V.at(index);
        Config::set_USER(::EnUser::VITS_ID,QString::number(index));
    });

    CurrentIndexChanged currentIndexChanged_gptsovits_language_select=&QComboBox::currentIndexChanged;
    QObject::connect(ui->comboBox_gptsovits_language,currentIndexChanged_gptsovits_language_select,this,[=](int index){
        qDebug()<<"设置GPT-SoVits语言为:"<<GPTSOVITS_LANGUAGE_V.at(index);
        Config::set_USER(::EnUser::GPTSOVITS_LANGUAGE,QString::number(index));
    });

    QObject::connect(ui->radioButton_llm_chatgpt, &QRadioButton::toggled, [&](){
        qDebug()<<"设置LLM模型为:";
        if (ui->radioButton_llm_chatgpt->isChecked()) {
            qDebug()<<"ChatGPT";
            Config::set_USER(::EnUser::LLM_MODEL_ID,QString::number(0));
        } else {
            qDebug()<<"讯飞星火";
            Config::set_USER(::EnUser::LLM_MODEL_ID,QString::number(1));
        }
    });
    CurrentIndexChanged currentIndexChanged_llm_xfxh=&QComboBox::currentIndexChanged;
    QObject::connect(ui->comboBox_llm_xfxh,currentIndexChanged_llm_xfxh,this,[=](int index){
        qDebug()<<"设置讯飞星火模型为："<<XFXH_MODEL_V.at(index);
        Config::set_USER(::EnUser::XFXH_MODEL_ID,QString::number(index));
    });

    QObject::connect(ui->radioButton_config_enable_yes, &QRadioButton::toggled, [&](){
        qDebug()<<"启用角色扮演";
        if (ui->radioButton_config_enable_yes->isChecked()) {
            qDebug()<<"YES";
            Config::set_USER(::EnUser::ENABLE_ROLE,QString::number(1));
        } else {
            qDebug()<<"NO";
            Config::set_USER(::EnUser::ENABLE_ROLE,QString::number(0));
        }
    });
    QObject::connect(ui->radioButton_sound_enable_yes, &QRadioButton::toggled, [&](){
        qDebug()<<"启用VITS语音";
        if (ui->radioButton_sound_enable_yes->isChecked()) {
            qDebug()<<"YES";
            Config::set_USER(::EnUser::ENABLE_SOUND,QString::number(1));
        } else {
            qDebug()<<"NO";
            Config::set_USER(::EnUser::ENABLE_SOUND,QString::number(0));
        }
    });

    CurrentIndexChanged currentIndexChanged_baidu_from=&QComboBox::currentIndexChanged;
    QObject::connect(ui->comboBox_baidu_from,currentIndexChanged_baidu_from,this,[=](int index){
        qDebug()<<"设置FROM语种为："<<LANGUAGE_V.at(index);
        Config::set_USER(::EnUser::BAIDU_FROM_ID,QString::number(index));
    });

    CurrentIndexChanged currentIndexChanged_baidu_to=&QComboBox::currentIndexChanged;
    QObject::connect(ui->comboBox_baidu_to,currentIndexChanged_baidu_to,this,[=](int index){
        qDebug()<<"设置TO语种为："<<LANGUAGE_V.at(index);
        Config::set_USER(::EnUser::BAIDU_TO_ID,QString::number(index));
    });

    QObject::connect(ui->radioButton_baidu_enable_yes, &QRadioButton::toggled, [&](){
        qDebug()<<"启用百度翻译";
        if (ui->radioButton_baidu_enable_yes->isChecked()) {
            qDebug()<<"YES";
            Config::set_USER(::EnUser::ENABLE_BAIDUFANYI,QString::number(1));
        } else {
            qDebug()<<"NO";
            Config::set_USER(::EnUser::ENABLE_BAIDUFANYI,QString::number(0));
        }
    });
    QObject::connect(ui->radioButton_baidu_show_enable_yes, &QRadioButton::toggled, [&](){
        qDebug()<<"启用百度翻译后的结果显示";
        if (ui->radioButton_baidu_show_enable_yes->isChecked()) {
            qDebug()<<"YES";
            Config::set_USER(::EnUser::ENABLE_LATERLANGUAGE,QString::number(1));
        } else {
            qDebug()<<"NO";
            Config::set_USER(::EnUser::ENABLE_LATERLANGUAGE,QString::number(0));
        }
    });
}

void SetDialogWidget::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    qDebug()<<"基本配置更新成功！";
    Config::set_USER(::EnUser::VITS_URL_ADDRESS,ui->lineEdit_vits_address->text());
    Config::set_USER(::EnUser::VITS_URL_PORT,ui->lineEdit_vits_port->text());

    Config::set_USER(::EnUser::GPTSOVITS_URL_ADDRESS,ui->lineEdit_gptsovits_address->text());
    Config::set_USER(::EnUser::GPTSOVITS_URL_PORT,ui->lineEdit_gptsovits_port->text());

    Config::set_USER(::EnUser::SPEAKER_ID,ui->lineEdit_speaker_id->text());
    Config::set_USER(::EnUser::EMOTION_ID,ui->lineEdit_speaker_emotion->text());

    Config::set_IKS(::EnIks::LLM_CHATGPT,"",ui->lineEdit_gpt_key->text(),"");
    Config::set_IKS(::EnIks::LLM_XFXH,ui->lineEdit_xfxh_appid->text(),ui->lineEdit_xfxh_apikey->text(),ui->lineEdit_xfxh_apisecret->text());
    Config::set_IKS(::EnIks::MT_BDFY,ui->lineEdit_baidu_appid->text(),ui->lineEdit_baidu_key->text(),"");
    Config::set_IKS(::EnIks::STT_BDYUN,"",ui->lineEdit_baidusound_key->text(),ui->lineEdit_baidusound_secret->text());

    Config::set_URL(::EnUrl::URL_CHATGPT_BASEURL,ui->lineEdit_gpt_url->text());

}
