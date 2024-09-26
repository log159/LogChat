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
    qDebug()<<"SetDialogWidget 析构";
    delete ui;
}

void SetDialogWidget::init()
{
    this->resize(WIDTH,HEIGHT);
    this->setWindowTitle("基本设置");
    this->setWindowIcon(QIcon(":/res/u77.svg"));
    setWindowFlags((windowFlags() & ~Qt::WindowContextHelpButtonHint) | Qt::WindowStaysOnTopHint);

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

    int model_id=Config::get_USER(::EnUser::LLM_MODEL_ID).toInt();
    if(model_id==0){ui->radioButton_llm_chatgpt->setChecked(true);}
    else if(model_id==1){ui->radioButton_llm_xfxh->setChecked(true);}
    else if(model_id==2){ui->radioButton_llm_deepseek->setChecked(true);}

    for(int i=0;i<CHATGPT_MODEL_V.size();++i){
        ui->comboBox_llm_chatgpt->addItem(CHATGPT_MODEL_V.at(i));
    }
    for(int i=0;i<XFXH_MODEL_V.size();++i){
        ui->comboBox_llm_xfxh->addItem(XFXH_MODEL_V.at(i));
    }
    ui->comboBox_llm_chatgpt->setCurrentIndex(Config::get_USER(::EnUser::CHATGPT_MODEL_ID).toInt());
    ui->comboBox_llm_xfxh->setCurrentIndex(Config::get_USER(::EnUser::XFXH_MODEL_ID).toInt());

    ui->lineEdit_gpt_key->setText(Config::get_IKS(::EnIks::LLM_CHATGPT).key);
    ui->lineEdit_gpt_url->setText(Config::get_URL(::EnUrl::URL_CHATGPT_BASEURL));
    ui->lineEdit_xfxh_appid->setText(Config::get_IKS(::EnIks::LLM_XFXH).id);
    ui->lineEdit_xfxh_key->setText(Config::get_IKS(::EnIks::LLM_XFXH).key);
    ui->lineEdit_xfxh_secret->setText(Config::get_IKS(::EnIks::LLM_XFXH).secret);
    ui->lineEdit_deepseek_key->setText(Config::get_IKS(::EnIks::LLM_DEEPSEEK).key);
    ui->lineEdit_deepseek_url->setText(Config::get_URL(::EnUrl::URL_DEEPSEEK_BASEURL));
    ui->lineEdit_baidu_appid->setText(Config::get_IKS(::EnIks::MT_BDFY).id);
    ui->lineEdit_baidu_key->setText(Config::get_IKS(::EnIks::MT_BDFY).key);
    ui->lineEdit_baidusound_key->setText(Config::get_IKS(::EnIks::STT_BDYUN).key);
    ui->lineEdit_baidusound_secret->setText(Config::get_IKS(::EnIks::STT_BDYUN).secret);

    if(Config::get_USER(::EnUser::ENABLE_ROLE).toInt()!=0){ui->radioButton_config_enable_yes->setChecked(true);}
    else {ui->radioButton_config_enable_no->setChecked(true);}

    if(Config::get_USER(::EnUser::ENABLE_SOUND).toInt()!=0){ui->radioButton_sound_enable_yes->setChecked(true);}
    else{ui->radioButton_sound_enable_no->setChecked(true);}

    if(Config::get_USER(::EnUser::ENABLE_VOICE_INPUT).toInt()!=0){ui->radioButton_voice_inout_enable_yes->setChecked(true);}
    else{ui->radioButton_voice_inout_enable_no->setChecked(true);}

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

    ui->lineEdit_live2d_address->setText(Config::get_OTHER(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::CONFIG_UNITY_WAY),"SERVERS","ADDRESS"));
    ui->lineEdit_live2d_port->setText(Config::get_OTHER(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::CONFIG_UNITY_WAY),"SERVERS","PORT"));


    QString voicewaystr=ConfigConstWay::get_TRUE_WAY(ConfigConstWay::OUTPUT_WAV_WAY);
    voicewaystr.chop(QString("/%1.wav").size());
    ui->lineEdit_voiceway->setText(voicewaystr);
    ui->lineEdit_voiceway->setReadOnly(true);

    QString voicesaveway=ConfigConstWay::get_TRUE_WAY(ConfigConstWay::OUTPUT_SAVEWAV_WAY);
    voicesaveway.chop(QString("/%1.wav").size());
    ui->lineEdit_voicesaveway->setText(voicesaveway);
    ui->lineEdit_voicesaveway->setReadOnly(true);

    QString live2dsaveway=ConfigConstWay::get_TRUE_WAY(ConfigConstWay::UNITY_MODELS_WAY);
    ui->lineEdit_live2dsaveway->setText(live2dsaveway);
    ui->lineEdit_live2dsaveway->setReadOnly(true);

    QString vits_selfrule_text=Config::get_URL(EnUrl::URL_VITSSELF_RULEURL);
    ui->lineEdit_vits_selfrule->setText(vits_selfrule_text);

    if(Config::get_USER(::EnUser::ENABLE_SELFVOLUME).toInt()!=0)
        ui->pushButton_audiovolume->setText("自定义的");
    else
        ui->pushButton_audiovolume->setText("跟随系统");

    ui->horizontalSlider_audiovolume->setRange(0,100);
    ui->horizontalSlider_audiovolume->setValue(Config::get_USER(::EnUser::AUDIOVOLUME).toInt());

    ui->lineEdit_audiovolume->setReadOnly(true);
    ui->lineEdit_audiovolume->setText(QString::number(ui->horizontalSlider_audiovolume->value()));

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
        }
    });
    QObject::connect(ui->radioButton_llm_xfxh, &QRadioButton::toggled, [&](){
        if(ui->radioButton_llm_xfxh->isChecked()) {
            qDebug()<<"讯飞星火";
            Config::set_USER(::EnUser::LLM_MODEL_ID,QString::number(1));
        }
    });

    QObject::connect(ui->radioButton_llm_deepseek, &QRadioButton::toggled, [&](){
        if(ui->radioButton_llm_deepseek->isChecked()) {
            qDebug()<<"DeepSeek";
            Config::set_USER(::EnUser::LLM_MODEL_ID,QString::number(2));
        }
    });
    CurrentIndexChanged currentIndexChanged_llm_chatgpt=&QComboBox::currentIndexChanged;
    QObject::connect(ui->comboBox_llm_chatgpt,currentIndexChanged_llm_chatgpt,this,[=](int index){
        qDebug()<<"设置ChatGPT模型为："<<CHATGPT_MODEL_V.at(index);
        Config::set_USER(::EnUser::CHATGPT_MODEL_ID,QString::number(index));
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

    QObject::connect(ui->radioButton_voice_inout_enable_yes, &QRadioButton::toggled, [&](){
        qDebug()<<"启用语音输入";
        if (ui->radioButton_voice_inout_enable_yes->isChecked()) {
            qDebug()<<"YES";
            Config::set_USER(::EnUser::ENABLE_VOICE_INPUT,QString::number(1));
        } else {
            qDebug()<<"NO";
            Config::set_USER(::EnUser::ENABLE_VOICE_INPUT,QString::number(0));
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
    connect(ui->pushButton_voicefind,&QPushButton::clicked,[=](){
        QUrl directoryUrl = QUrl::fromLocalFile(ui->lineEdit_voiceway->text());
        if (QDesktopServices::openUrl(directoryUrl)) {
            qDebug() << "File explorer opened successfully.";
        } else {
            qDebug() << "Failed to open file explorer.";
        }
    });
    connect(ui->pushButton_voiceclear,&QPushButton::clicked,[=](){
        QString dirPath=ui->lineEdit_voiceway->text();
        QDir dir(dirPath);
        if (!dir.exists()) {
            qDebug() << "Directory does not exist!";
        }
        QStringList files = dir.entryList(QDir::Files);
        for (const QString &file : files) {
            QFile::remove(dirPath + "/" + file);
            if (QFile::exists(dirPath + "/" + file)) {
                qDebug() << "Failed to delete file:" << file;
            }
        }
        QMessageBox::warning(this,"True","已清除缓存");
    });


    connect(ui->pushButton_voicesavefind,&QPushButton::clicked,[=](){
        QUrl directoryUrl = QUrl::fromLocalFile(ui->lineEdit_voicesaveway->text());
        if (QDesktopServices::openUrl(directoryUrl)) {
            qDebug() << "File explorer opened successfully.";
        } else {
            qDebug() << "Failed to open file explorer.";
        }
    });
    connect(ui->pushButton_voicesaveclear,&QPushButton::clicked,[=](){
        QString dirPath=ui->lineEdit_voicesaveway->text();
        QDir dir(dirPath);
        if (!dir.exists()) {
            qDebug() << "Directory does not exist!";
        }
        QStringList files = dir.entryList(QDir::Files);
        for (const QString &file : files) {
            QFile::remove(dirPath + "/" + file);
            if (QFile::exists(dirPath + "/" + file)) {
                qDebug() << "Failed to delete file:" << file;
            }
        }
        QMessageBox::warning(this,"True","已清除缓存");
    });
    connect(ui->pushButton_live2dsavefind,&QPushButton::clicked,[=](){
        QUrl directoryUrl = QUrl::fromLocalFile(ui->lineEdit_live2dsaveway->text());
        if (QDesktopServices::openUrl(directoryUrl)) {
            qDebug() << "File explorer opened successfully.";
        } else {
            qDebug() << "Failed to open file explorer.";
        }
    });


    connect(ui->pushButton_getspeakers,&QPushButton::clicked,[=](){
        NetworkManager* networkManager  =new NetworkManager(this);
        connect(networkManager,&NetworkManager::sendSpeakers,[=](QVector<QString> sv){
            ui->comboBox_vitsspeakers->clear();
            for (auto& val:sv) {
                ui->comboBox_vitsspeakers->addItem(val);
            }
        });
        networkManager->fetchUrl(QUrl(QString("http://%1:%2/voice/speakers").arg(ui->lineEdit_vits_address->text()).arg(ui->lineEdit_vits_port->text())));
    });

    SliderMoved sliderMovedAudiovolume=&QSlider::sliderMoved;
    QObject::connect(ui->horizontalSlider_audiovolume,sliderMovedAudiovolume,this,[=](int value){
        Config::set_USER(::EnUser::AUDIOVOLUME,QString::number(value));
        qDebug()<<"Audio音量: "<<QString::number(value);
        ui->lineEdit_audiovolume->setText(QString::number(value));

    });

    QObject::connect(ui->pushButton_audiovolume,&QPushButton::clicked,[=](){
        int en = Config::get_USER(::EnUser::ENABLE_SELFVOLUME).toInt();
        if(en!=0){
            ui->pushButton_audiovolume->setText("跟随系统");
            Config::set_USER(::EnUser::ENABLE_SELFVOLUME,QString::number(0));
        }
        else {
            ui->pushButton_audiovolume->setText("自定义的");
            Config::set_USER(::EnUser::ENABLE_SELFVOLUME,QString::number(1));
        }
        qDebug()<<ui->pushButton_audiovolume->text();
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

    Config::set_URL(::EnUrl::URL_VITSSELF_RULEURL,ui->lineEdit_vits_selfrule->text());

    Config::set_IKS(::EnIks::LLM_CHATGPT,"",ui->lineEdit_gpt_key->text(),"");
    Config::set_IKS(::EnIks::LLM_XFXH,ui->lineEdit_xfxh_appid->text(),ui->lineEdit_xfxh_key->text(),ui->lineEdit_xfxh_secret->text());
    Config::set_IKS(::EnIks::LLM_DEEPSEEK,"",ui->lineEdit_deepseek_key->text(),"");
    Config::set_IKS(::EnIks::MT_BDFY,ui->lineEdit_baidu_appid->text(),ui->lineEdit_baidu_key->text(),"");
    Config::set_IKS(::EnIks::STT_BDYUN,"",ui->lineEdit_baidusound_key->text(),ui->lineEdit_baidusound_secret->text());

    Config::set_URL(::EnUrl::URL_CHATGPT_BASEURL,ui->lineEdit_gpt_url->text());
    Config::set_URL(::EnUrl::URL_DEEPSEEK_BASEURL,ui->lineEdit_deepseek_url->text());


    Config::set_OTHER(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::CONFIG_UNITY_WAY),"SERVERS","ADDRESS",ui->lineEdit_live2d_address->text());
    Config::set_OTHER(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::CONFIG_UNITY_WAY),"SERVERS","PORT",ui->lineEdit_live2d_port->text());

}
