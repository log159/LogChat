#include "setlive2ddialogwidget.h"
#include "ui_setlive2ddialogwidget.h"


QProcess*   SetLive2DDialogWidget::     m_Live2dProcess =nullptr;
bool        SetLive2DDialogWidget::     live2DIsOpen    =false;
int         SetLive2DDialogWidget::     m_Live2dOpenId  =-1;

SetLive2DDialogWidget::SetLive2DDialogWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetLive2DDialogWidget)
{
    ui->setupUi(this);

    init();
    initConnect();
}

SetLive2DDialogWidget::~SetLive2DDialogWidget()
{
    qDebug()<<"SetLive2DDialogWidget 析构";
    delete ui;
}

void SetLive2DDialogWidget::closeProcess()
{
    if(m_Live2dProcess==nullptr)return;
    SetLive2DDialogWidget::live2DIsOpen=false;
    SetLive2DDialogWidget::m_Live2dOpenId=-1;
    NetLive2D::getInstance()->stopListen();
//    //尝试优雅的退出
    if (m_Live2dProcess->state() == QProcess::Running) {
        m_Live2dProcess->terminate();
        m_Live2dProcess->waitForFinished(1000);
        //杀死进程
        if (m_Live2dProcess->state() == QProcess::Running) {
            m_Live2dProcess->kill();
            delete m_Live2dProcess;
            m_Live2dProcess=nullptr;
        }
    }
}

void SetLive2DDialogWidget::init()
{
    this->resize(WIDTH,HEIGHT);
    this->setWindowTitle("Live2D");
    this->setWindowIcon(QIcon(":/res/u77.svg"));
    setWindowFlags((windowFlags() & ~Qt::WindowContextHelpButtonHint));


     ui->listWidget_model->setEditTriggers(QAbstractItemView::NoEditTriggers);         //禁止编辑
     ui->listWidget_model->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);   //平滑效果
     ui->listWidget_model->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);       //禁用水平滑动条


     for(int i=0;i<Config::get_LIVE2DMODELCONFIG_V().size();++i){
         addListItem(Config::get_LIVE2DMODELCONFIG_V().at(i));
     }

     ui->tabWidget_control->setCurrentIndex(0);

     //配置
     ui->radioButton_look_enable_yes->setChecked(LIVE2DENABLEINIT_M["look_enable"]);
     switch (LIVE2DPARAMINIT_M["win_topapha"]) {
        case 0:ui->radioButton_wintop->setChecked(true);break;
        case 1:ui->radioButton_winapha->setChecked(true);break;
        case 2:ui->radioButton_wintopapha->setChecked(true);break;
        case 3:ui->radioButton_winnotopnoapha->setChecked(true);break;
     }

     //几何
     ui->horizontalSlider_zoom_model_size->setRange(10,10000);      //0.1-100
     ui->horizontalSlider_zoom_model_X->setRange(-200000,200000);   //-2000-2000
     ui->horizontalSlider_zoom_model_Y->setRange(-200000,200000);   //-2000-2000

     ui->horizontalSlider_zoom_model_RX->setRange(-72000,72000);          //-720-720
     ui->horizontalSlider_zoom_model_RY->setRange(-72000,72000);          //-720-720
     ui->horizontalSlider_zoom_model_RZ->setRange(-72000,72000);          //-720-720

     //信息
     ui->horizontalSlider_zoom_mouse_speed->setRange(0,200);        //0-2
     ui->horizontalSlider_zoom_eye_time->setRange(100,1000);        //1-10
     ui->horizontalSlider_zoom_eye_deviation->setRange(50,500);     //0.5-5
     ui->horizontalSlider_zoom_eye_speed->setRange(100,2000);       //1-20
     ui->horizontalSlider_zoom_audio_add->setRange(100,1000);       //1-10
     ui->horizontalSlider_zoom_audio_smooth->setRange(0,100);       //0-1


     ui->horizontalSlider_zoom_model_size->setValue(LIVE2DPARAMINIT_M["model_size"]);
     ui->horizontalSlider_zoom_model_X->setValue(LIVE2DPARAMINIT_M["model_x"]);
     ui->horizontalSlider_zoom_model_Y->setValue(LIVE2DPARAMINIT_M["model_y"]);
     ui->horizontalSlider_zoom_model_RX->setValue(LIVE2DPARAMINIT_M["model_rx"]);
     ui->horizontalSlider_zoom_model_RY->setValue(LIVE2DPARAMINIT_M["model_ry"]);
     ui->horizontalSlider_zoom_model_RZ->setValue(LIVE2DPARAMINIT_M["model_rz"]);

     ui->horizontalSlider_zoom_mouse_speed->setValue(LIVE2DPARAMINIT_M["mouse_speed"]);
     ui->horizontalSlider_zoom_eye_time->setValue(LIVE2DPARAMINIT_M["eye_time"]);
     ui->horizontalSlider_zoom_eye_deviation->setValue(LIVE2DPARAMINIT_M["eye_deviation"]);
     ui->horizontalSlider_zoom_eye_speed->setValue(LIVE2DPARAMINIT_M["eye_speed"]);
     ui->horizontalSlider_zoom_audio_add->setValue(LIVE2DPARAMINIT_M["audio_add"]);
     ui->horizontalSlider_zoom_audio_smooth->setValue(LIVE2DPARAMINIT_M["audio_smooth"]);

     ui->lineEdit_zoom_model_size->setEnabled(false);
     ui->lineEdit_zoom_model_X->setEnabled(false);
     ui->lineEdit_zoom_model_Y->setEnabled(false);
     ui->lineEdit_zoom_model_RX->setEnabled(false);
     ui->lineEdit_zoom_model_RY->setEnabled(false);
     ui->lineEdit_zoom_model_RZ->setEnabled(false);
     ui->lineEdit_zoom_mouse_speed->setEnabled(false);
     ui->lineEdit_zoom_eye_time->setEnabled(false);
     ui->lineEdit_zoom_eye_deviation->setEnabled(false);
     ui->lineEdit_zoom_eye_speed->setEnabled(false);
     ui->lineEdit_zoom_audio_add->setEnabled(false);
     ui->lineEdit_zoom_audio_smooth->setEnabled(false);


     initLineEdit();

     if(SetLive2DDialogWidget::live2DIsOpen){
         if(SetLive2DDialogWidget::m_Live2dOpenId>=0){
             updateForUi();
             updateModelChange();
         }
     }
     QFile file(":/main.qss");
     if(file.open(QFile::ReadOnly)){
         QString styleSheet = QLatin1String(file.readAll());
         this->setStyleSheet(styleSheet);
         file.close();
     }
}

void SetLive2DDialogWidget::initConnect()
{

    SliderChange slider=&QSlider::sliderMoved;

    //启动模型
    connect(ui->pushButton_start,&QPushButton::clicked,this,[=](){
        if(NetLive2D::getIsConnect()==false){live2DIsOpen=false;}
        if(ui->listWidget_model->count()<=0){
            QMessageBox::warning(this,"Error occurred","没有可用模型！");return ;
        }
        if(m_Live2dPassId==-1){
            QMessageBox::warning(this,"Error occurred","请选择模型！");return ;
        }
        if(Config::get_LIVE2DMODELCONFIG_V()[m_Live2dPassId].getFilePath().size()<QString("model3.json").size()){
            QMessageBox::warning(this,"Error occurred","模型路径有误！");return ;
        }
        m_Live2dOpenId=m_Live2dPassId;
        updateModelChange();
        if(live2DIsOpen==true){
            Config::set_UNITY_STARTMODELPATH(ConfigConstWay::get_TRUE_WAY(Config::get_LIVE2DMODELCONFIG_V()[SetLive2DDialogWidget::m_Live2dOpenId].getFilePath()));
            sendModelHandle("Init:null;");
            //同步刷新Ui
            updateForUi();


            return;
        }
        SetLive2DDialogWidget::live2DIsOpen=true;
        if(m_Live2dProcess==nullptr)
            m_Live2dProcess=new QProcess(ConfigWindow::getWindowPointer());
        qDebug()<<"live2d base window pointer : "<<ConfigWindow::getWindowPointer();
        m_Live2dProcess->setWorkingDirectory(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::UNITY_DEMO_WORK_WAY));
//        m_Live2dProcess->startDetached(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::UNITY_DEMO_WAY),QStringList(),ConfigConstWay::get_TRUE_WAY(ConfigConstWay::UNITY_DEMO_WORK_WAY));
        m_Live2dProcess->start(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::UNITY_DEMO_WAY));
        //检查外部进程是否成功启动
        if (!m_Live2dProcess->waitForStarted()) {
            qDebug() << "Failed to start the process";
            return;
        }
        else {
            //创建通信用套接字
            NetLive2D::getInstance()->startListen();
            //同步刷新Ui
            updateForUi();


        }
    });

    //退出模型
    connect(ui->pushButton_quit,&QPushButton::clicked,this,[=](){
        closeProcess();
        updateModelChange();
    });

    //添加模型
    connect(ui->pushButton_add,&QPushButton::clicked,this,[=](){
        QString jsonPath = QFileDialog::getOpenFileName(nullptr, "Open File", "", "All Files (*model3.json)");
        if(jsonPath.size()<QString(".model3.json").size()){return ;}
        int lastIndex =  jsonPath.lastIndexOf('/');
        QString sourceDir=jsonPath.left(lastIndex);
        QString timeHashStr=TimeInformation::getDateTimeHashString();
        QString destinationDir =ConfigConstWay::get_TRUE_WAY(ConfigConstWay::UNITY_MODELS_WAY)+"/"+timeHashStr;
        //创建目标目录
        QDir make_dir;
        if (make_dir.mkpath(destinationDir)) {qDebug() << "目录创建成功：";}
        else { qDebug() << "目录创建失败：";return ;}
        ConfigFileIO::copyDirectory(sourceDir,destinationDir);
        qDebug()<<"Live2d 全部文件拷贝完成";

        QVector<ModelConfigItem> modV=Config::get_LIVE2DMODELCONFIG_V();
        ModelConfigItem modelConfigItem;

        //model赋值
        modelConfigItem.setModelId(ui->listWidget_model->count());
        QString model_name=jsonPath.mid(lastIndex+1);
        model_name.chop(QString(".model3.json").size());
        modelConfigItem.setModelName(model_name);
        modelConfigItem.setFilePath(ConfigConstWay::UNITY_MODELS_WAY+"/"+timeHashStr+"/"+jsonPath.mid(lastIndex+1));

        modV.push_back(modelConfigItem);
        Config::set_LIVE2DMODELCONFIG_V(modV);
        this->addListItem(modelConfigItem);

    });

    //删除模型
    connect(ui->pushButton_delete,&QPushButton::clicked,this,[=](){
        int id=ui->listWidget_model->currentRow();
        m_Live2dPassId=-1;
        if(id<0){return ;}
        ui->listWidget_model->clearSelection();
        qDebug()<<QString::number(id)<<" 号模型被删除，Name is "<<Config::get_LIVE2DMODELCONFIG_V()[id].getModelName();

        QVector<ModelConfigItem> modV=Config::get_LIVE2DMODELCONFIG_V();
        if(id>=modV.size()){return ;}
        modV.remove(id);
        //编号对齐
        for(int i=0;i<modV.size();++i){
            modV[i].setModelId(i);
        }
        Config::set_LIVE2DMODELCONFIG_V(modV);
        ui->listWidget_model->clear();

        for(int i=0;i<Config::get_LIVE2DMODELCONFIG_V().size();++i){
            addListItem(Config::get_LIVE2DMODELCONFIG_V().at(i));
        }

    });

    //修改模型
    connect(ui->pushButton_change,&QPushButton::clicked,this,[=](){
        if(SetLive2DDialogWidget::live2DIsOpen==false||SetLive2DDialogWidget::m_Live2dOpenId==-1){
            QMessageBox::warning(this,"Error occurred","请选择模型！");
            return ;
        }
        ChangeLive2DWidget widget;
        QString filePath=ConfigConstWay::get_TRUE_WAY(ui->lineEdit_way->text());
        int index=filePath.size()-1;
        for (;index>=0;--index) {
            if(filePath[index]==QChar('\\')||filePath[index]==QChar('/')){
                break;
            }
        }

        QString directoryPath = filePath.mid(0,index);
        widget.refresh(directoryPath);
        connect(&widget,&ChangeLive2DWidget::sendHandle,[=](QString handleStr){
            emit sendModelHandle(handleStr);
        });

        widget.exec();
    });

    //打开文件位置
    connect(ui->pushButton_way,&QPushButton::clicked,this,[=](){

        QString filePath=ConfigConstWay::get_TRUE_WAY(ui->lineEdit_way->text());
        int index=filePath.size()-1;
        for (;index>=0;--index) {
            if(filePath[index]==QChar('\\')||filePath[index]==QChar('/')){
                break;
            }
        }
        QString directoryPath =filePath.mid(0,index);
        qDebug()<<"open file path"<<directoryPath;
        QUrl directoryUrl = QUrl::fromLocalFile(directoryPath);
        if (QDesktopServices::openUrl(directoryUrl)) {
            qDebug() << "File explorer opened successfully.";
        } else {
            qDebug() << "Failed to open file explorer.";
        }
    });

    //看向鼠标
    connect(ui->radioButton_look_enable_yes, &QRadioButton::clicked, [&](){sendConfigHandle("IsLookMouse",100);});
    connect(ui->radioButton_look_enable_no, &QRadioButton::clicked, [&](){sendConfigHandle("IsLookMouse",0);});
    //窗口置顶
    connect(ui->radioButton_wintop, &QRadioButton::clicked, [&](){sendWindowHandle("wintop");});
    connect(ui->radioButton_winapha, &QRadioButton::clicked, [&](){sendWindowHandle("winapha");});
    connect(ui->radioButton_wintopapha, &QRadioButton::clicked, [&](){sendWindowHandle("wintopapha");});
    connect(ui->radioButton_winnotopnoapha, &QRadioButton::clicked, [&](){sendWindowHandle("winnotopnoapha");});
    //模型缩放比例
    connect(ui->horizontalSlider_zoom_model_size,slider,this,[=](int value){sendConfigHandle("ScaleProportion",value);setLineEditText(ui->lineEdit_zoom_model_size,value);});
    //X坐标
    connect(ui->horizontalSlider_zoom_model_X,slider,this,[=](int value){sendConfigHandle("X",value);setLineEditText(ui->lineEdit_zoom_model_X,value);});
    //Y坐标
    connect(ui->horizontalSlider_zoom_model_Y,slider,this,[=](int value){sendConfigHandle("Y",value);setLineEditText(ui->lineEdit_zoom_model_Y,value);});
    //RX坐标
    connect(ui->horizontalSlider_zoom_model_RX,slider,this,[=](int value){sendConfigHandle("RX",value);setLineEditText(ui->lineEdit_zoom_model_RX,value);});
    //RY坐标
    connect(ui->horizontalSlider_zoom_model_RY,slider,this,[=](int value){sendConfigHandle("RY",value);setLineEditText(ui->lineEdit_zoom_model_RY,value);});
    //RZ坐标
    connect(ui->horizontalSlider_zoom_model_RZ,slider,this,[=](int value){sendConfigHandle("RZ",value);setLineEditText(ui->lineEdit_zoom_model_RZ,value);});

    //看向鼠标速度
    connect(ui->horizontalSlider_zoom_mouse_speed,slider,this,[=](int value){sendConfigHandle("Damping",value);setLineEditText(ui->lineEdit_zoom_mouse_speed,value);});
    //平均眨眼周期
    connect(ui->horizontalSlider_zoom_eye_time,slider,this,[=](int value){sendConfigHandle("Mean",value);setLineEditText(ui->lineEdit_zoom_eye_time,value);});
    //眨眼偏差时间
    connect(ui->horizontalSlider_zoom_eye_deviation,slider,this,[=](int value){sendConfigHandle("MaximumDeviation",value);setLineEditText(ui->lineEdit_zoom_eye_deviation,value);});
    //眨眼速度快慢
    connect(ui->horizontalSlider_zoom_eye_speed,slider,this,[=](int value){sendConfigHandle("Timescale",value);setLineEditText(ui->lineEdit_zoom_eye_speed,value);});
    //音频增益效果
    connect(ui->horizontalSlider_zoom_audio_add,slider,this,[=](int value){sendConfigHandle("Gain",value);setLineEditText(ui->lineEdit_zoom_audio_add,value);});
    //音频平滑效果
    connect(ui->horizontalSlider_zoom_audio_smooth,slider,this,[=](int value){sendConfigHandle("Smoothing",value);setLineEditText(ui->lineEdit_zoom_audio_smooth,value);});


    //重置

    connect(ui->pushButton_zoom_model_size,&QPushButton::clicked,[&](){
        ui->horizontalSlider_zoom_model_size->setValue(LIVE2DPARAMINIT_M["model_size"]);
        sendConfigHandle("ScaleProportion",ui->horizontalSlider_zoom_model_size->value());
        initLineEdit();
    });
    connect(ui->pushButton_zoom_model_X,&QPushButton::clicked,[&](){ui->horizontalSlider_zoom_model_X->setValue(
        LIVE2DPARAMINIT_M["model_x"]);
        sendConfigHandle("X",ui->horizontalSlider_zoom_model_X->value());
        initLineEdit();
    });
    connect(ui->pushButton_zoom_model_Y,&QPushButton::clicked,[&](){
        ui->horizontalSlider_zoom_model_Y->setValue(LIVE2DPARAMINIT_M["model_y"]);
        sendConfigHandle("Y",ui->horizontalSlider_zoom_model_Y->value());
        initLineEdit();
    });
    connect(ui->pushButton_zoom_model_RX,&QPushButton::clicked,[&](){
        ui->horizontalSlider_zoom_model_RX->setValue(LIVE2DPARAMINIT_M["model_rx"]);
        sendConfigHandle("RX",ui->horizontalSlider_zoom_model_RX->value());
        initLineEdit();
    });
    connect(ui->pushButton_zoom_model_RY,&QPushButton::clicked,[&](){
        ui->horizontalSlider_zoom_model_RY->setValue(LIVE2DPARAMINIT_M["model_ry"]);
        sendConfigHandle("RY",ui->horizontalSlider_zoom_model_RY->value());
        initLineEdit();
    });
    connect(ui->pushButton_zoom_model_RZ,&QPushButton::clicked,[&](){
        ui->horizontalSlider_zoom_model_RZ->setValue(LIVE2DPARAMINIT_M["model_rz"]);
        sendConfigHandle("RZ",ui->horizontalSlider_zoom_model_RZ->value());
        initLineEdit();
    });

    connect(ui->pushButton_zoom_mouse_speed,&QPushButton::clicked,[&](){
        ui->horizontalSlider_zoom_mouse_speed->setValue(LIVE2DPARAMINIT_M["mouse_speed"]);
        sendConfigHandle("Damping",ui->horizontalSlider_zoom_mouse_speed->value());
        initLineEdit();
    });
    connect(ui->pushButton_zoom_eye_time,&QPushButton::clicked,[&](){
        ui->horizontalSlider_zoom_eye_time->setValue(LIVE2DPARAMINIT_M["eye_time"]);
        sendConfigHandle("Mean",ui->horizontalSlider_zoom_eye_time->value());
        initLineEdit();
    });
    connect(ui->pushButton_zoom_eye_deviation,&QPushButton::clicked,[&](){
        ui->horizontalSlider_zoom_eye_deviation->setValue(LIVE2DPARAMINIT_M["eye_deviation"]);
        sendConfigHandle("MaximumDeviation",ui->horizontalSlider_zoom_eye_deviation->value());
        initLineEdit();
    });

    connect(ui->pushButton_zoom_eye_speed,&QPushButton::clicked,[&](){
        ui->horizontalSlider_zoom_eye_speed->setValue(LIVE2DPARAMINIT_M["eye_speed"]);
        sendConfigHandle("Timescale",ui->horizontalSlider_zoom_eye_speed->value());
        initLineEdit();
    });
    connect(ui->pushButton_zoom_audio_add,&QPushButton::clicked,[&](){
        ui->horizontalSlider_zoom_audio_add->setValue(LIVE2DPARAMINIT_M["audio_add"]);
        sendConfigHandle("Gain",ui->horizontalSlider_zoom_audio_add->value());
        initLineEdit();
    });
    connect(ui->pushButton_zoom_audio_smooth,&QPushButton::clicked,[&](){
        ui->horizontalSlider_zoom_audio_smooth->setValue(LIVE2DPARAMINIT_M["audio_smooth"]);
        sendConfigHandle("Smoothing",ui->horizontalSlider_zoom_audio_smooth->value());
        initLineEdit();
    });

    //保存配置
    connect(ui->pushButton_save,&QPushButton::clicked,[=](){
        if(SetLive2DDialogWidget::m_Live2dOpenId==-1){
            return;
        }

        //model初始化
        ModelConfigItem modelConfigItem=Config::get_LIVE2DMODELCONFIG_V().at(SetLive2DDialogWidget::m_Live2dOpenId);
        modelConfigItem.setModelId(SetLive2DDialogWidget::m_Live2dOpenId);
        modelConfigItem.setModelName(ui->lineEdit_name->text());
        modelConfigItem.setFilePath(ui->lineEdit_way->text());
        modelConfigItem.setLookEnable(bool(ui->radioButton_look_enable_yes->isChecked()?1:0));
        int topapha=LIVE2DPARAMINIT_M["win_topapha"];
        if(ui->radioButton_wintop->isChecked())topapha=0;
        else if(ui->radioButton_winapha->isChecked())topapha=1;
        else if(ui->radioButton_wintopapha->isChecked())topapha=2;
        else if(ui->radioButton_winnotopnoapha->isChecked())topapha=3;
        else {};
        modelConfigItem.setTopApha(topapha);
        modelConfigItem.setModelSize(ui->horizontalSlider_zoom_model_size->value());
        modelConfigItem.setModelX(ui->horizontalSlider_zoom_model_X->value());
        modelConfigItem.setModelY(ui->horizontalSlider_zoom_model_Y->value());
        modelConfigItem.setMouseSpeed(ui->horizontalSlider_zoom_mouse_speed->value());
        modelConfigItem.setEyeTime(ui->horizontalSlider_zoom_eye_time->value());
        modelConfigItem.setEyeDeviation(ui->horizontalSlider_zoom_eye_deviation->value());
        modelConfigItem.setEyeSpeed(ui->horizontalSlider_zoom_eye_speed->value());
        modelConfigItem.setAudioAdd(ui->horizontalSlider_zoom_audio_add->value());
        modelConfigItem.setAudioSmooth(ui->horizontalSlider_zoom_audio_smooth->value());
        modelConfigItem.setModelDescription(ui->textEdit_explain->toPlainText());

        QVector<ModelConfigItem> modV=Config::get_LIVE2DMODELCONFIG_V();
        for (int i=0;i<modV.size();++i) {
            if(modV.at(i).getModelId()==SetLive2DDialogWidget::m_Live2dOpenId){
                modV[i]=modelConfigItem;
                break;
            }

        }
        Config::set_LIVE2DMODELCONFIG_V(modV);

        //更新ui
        qDebug()<<"更新ui id = "<<SetLive2DDialogWidget::m_Live2dOpenId;
        QListWidgetItem* listWidgetItem=ui->listWidget_model->item(SetLive2DDialogWidget::m_Live2dOpenId);
        (static_cast<Live2DListItemsWidget*>(ui->listWidget_model->itemWidget(listWidgetItem)))->setText(modelConfigItem.getModelName());

        //最后同步到对应文件夹下的ini
        QString filePath=ConfigConstWay::get_TRUE_WAY(ui->lineEdit_way->text());
        int index=filePath.size()-1;
        for (;index>=0;--index) {
            if(filePath[index]==QChar('\\')||filePath[index]==QChar('/')){
                break;
            }
        }
        QString configModelUserFilePath =filePath.mid(0,index)+"/"+::ConfigModelUserFileName;

        QMap<QString,QString>changeUserM;
        changeUserM["look_enable"]=(modelConfigItem.getLookEnable()==true?"1":"0");
        changeUserM["win_topapha"]=QString::number(modelConfigItem.getTopApha());
        changeUserM["model_size"]=QString::number(modelConfigItem.getModelSize());
        changeUserM["model_x"]=QString::number(modelConfigItem.getModelX());
        changeUserM["model_y"]=QString::number(modelConfigItem.getModelY());
        changeUserM["mouse_speed"]=QString::number(modelConfigItem.getMouseSpeed());
        changeUserM["eye_time"]=QString::number(modelConfigItem.getEyeTime());
        changeUserM["eye_deviation"]=QString::number(modelConfigItem.getEyeDeviation());
        changeUserM["eye_speed"]=QString::number(modelConfigItem.getEyeSpeed());
        changeUserM["audio_add"]=QString::number(modelConfigItem.getAudioAdd());
        changeUserM["audio_smooth"]=QString::number(modelConfigItem.getAudioSmooth());
        //保存到配置
        Config::set_OTHER_BASE(configModelUserFilePath,::ItemM[::EnItem::USER],changeUserM);
    });


}

void SetLive2DDialogWidget::addListItem(const ModelConfigItem &modItem)
{

    QListWidgetItem* item = new QListWidgetItem();
    Live2DListItemsWidget* widget=new Live2DListItemsWidget;
    widget->init(modItem);
    widget->resize(ui->listWidget_model->size().width(),widget->height());
    ui->listWidget_model->addItem(item);
    item->setSizeHint(widget->size());
    ui->listWidget_model->setItemWidget(item,widget);
    ui->listWidget_model->scrollToBottom();
    SendPass sendPass=&Live2DListItemsWidget::sendPass;
    connect(widget,sendPass,[=](ModelConfigItem passItem){
        qDebug()<<passItem.getModelId();
        qDebug()<<Config::get_LIVE2DMODELCONFIG_V().size();
        if(passItem.getModelId()>=Config::get_LIVE2DMODELCONFIG_V().size()){return ;}

        m_Live2dPassId=passItem.getModelId();
        Config::set_UNITY_STARTMODELPATH(ConfigConstWay::get_TRUE_WAY(Config::get_LIVE2DMODELCONFIG_V()[passItem.getModelId()].getFilePath()));
        ui->listWidget_model->setCurrentItem(item);
        qDebug()<<"pass model id : "<<passItem.getModelId();

    });
}


void SetLive2DDialogWidget::sendConfigHandle(const QString &str, int val)
{
    if(NetLive2D::getIsConnect()==false){return;}
    double value=double(val)/double(100);
    QString handleStr= QString("Config:%1,%2;").arg(str).arg(QString::number(value));
    emit sendModelHandle(handleStr);

}

void SetLive2DDialogWidget::sendWindowHandle(const QString &str)
{
    if(NetLive2D::getIsConnect()==false){return;}
    QString handleStr= QString("Window:%1;").arg(str);
    emit sendModelHandle(handleStr);
}


void SetLive2DDialogWidget::initLineEdit()
{
     ui->lineEdit_zoom_model_size->setText(Transformation::IntToStringF2(ui->horizontalSlider_zoom_model_size->value()));
     ui->lineEdit_zoom_model_X->setText(Transformation::IntToStringF2(ui->horizontalSlider_zoom_model_X->value()));
     ui->lineEdit_zoom_model_Y->setText(Transformation::IntToStringF2(ui->horizontalSlider_zoom_model_Y->value()));
     ui->lineEdit_zoom_model_RX->setText(Transformation::IntToStringF2(ui->horizontalSlider_zoom_model_RX->value()));
     ui->lineEdit_zoom_model_RY->setText(Transformation::IntToStringF2(ui->horizontalSlider_zoom_model_RY->value()));
     ui->lineEdit_zoom_model_RZ->setText(Transformation::IntToStringF2(ui->horizontalSlider_zoom_model_RZ->value()));

     ui->lineEdit_zoom_mouse_speed->setText(Transformation::IntToStringF2(ui->horizontalSlider_zoom_mouse_speed->value()));
     ui->lineEdit_zoom_eye_time->setText(Transformation::IntToStringF2(ui->horizontalSlider_zoom_eye_time->value()));
     ui->lineEdit_zoom_eye_deviation->setText( Transformation::IntToStringF2(ui->horizontalSlider_zoom_eye_deviation->value()));
     ui->lineEdit_zoom_eye_speed->setText(Transformation::IntToStringF2(ui->horizontalSlider_zoom_eye_speed->value()));
     ui->lineEdit_zoom_audio_add->setText( Transformation::IntToStringF2(ui->horizontalSlider_zoom_audio_add->value()));
     ui->lineEdit_zoom_audio_smooth->setText(Transformation::IntToStringF2(ui->horizontalSlider_zoom_audio_smooth->value()));
}



void SetLive2DDialogWidget::updateForUi()
{
    if(SetLive2DDialogWidget::m_Live2dOpenId==-1){return;}
    ModelConfigItem passItem=Config::get_LIVE2DMODELCONFIG_V().at(SetLive2DDialogWidget::m_Live2dOpenId);

    ui->lineEdit_name->setText(passItem.getModelName());
    ui->lineEdit_way->setText(passItem.getFilePath());

    if(passItem.getLookEnable())ui->radioButton_look_enable_yes->setChecked(true);
    else ui->radioButton_look_enable_no->setChecked(true);
    switch (passItem.getTopApha()) {
       case 0:ui->radioButton_wintop->setChecked(true);break;
       case 1:ui->radioButton_winapha->setChecked(true);break;
       case 2:ui->radioButton_wintopapha->setChecked(true);break;
       case 3:ui->radioButton_winnotopnoapha->setChecked(true);break;
    }

    ui->horizontalSlider_zoom_model_size->setValue(passItem.getModelSize());
    ui->horizontalSlider_zoom_model_X->setValue(passItem.getModelX());
    ui->horizontalSlider_zoom_model_Y->setValue(passItem.getModelY());

    ui->horizontalSlider_zoom_mouse_speed->setValue(passItem.getMouseSpeed());
    ui->horizontalSlider_zoom_eye_time->setValue(passItem.getEyeTime());
    ui->horizontalSlider_zoom_eye_deviation->setValue(passItem.getEyeDeviation());
    ui->horizontalSlider_zoom_eye_speed->setValue(passItem.getEyeSpeed());
    ui->horizontalSlider_zoom_audio_add->setValue(passItem.getAudioAdd());
    ui->horizontalSlider_zoom_audio_smooth->setValue(passItem.getAudioSmooth());

    ui->textEdit_explain->setText(passItem.getModelDescription());


    this->initLineEdit();

}

//void SetLive2DDialogWidget::updateForUnity()
//{

//    if(SetLive2DDialogWidget::m_Live2dOpenId==-1){return;}
//    if(NetLive2D::getIsConnect()==false){return;}

//    QTimer::singleShot(5,this,[=](){
//        if(ui->radioButton_look_enable_yes->isChecked())sendConfigHandle("IsLookMouse",100);
//        else sendConfigHandle("IsLookMouse",0);
//    });

//    QTimer::singleShot(10,this,[=](){
//        if(ui->radioButton_wintop->isChecked())sendWindowHandle("wintop");
//        else if(ui->radioButton_winapha->isChecked())sendWindowHandle("winapha");
//        else if(ui->radioButton_wintopapha->isChecked())sendWindowHandle("wintopapha");
//        else if(ui->radioButton_winnotopnoapha->isChecked())sendWindowHandle("winnotopnoapha");
//        else {};
//    });

//    QTimer::singleShot(15,this,[=](){sendConfigHandle("ScaleProportion",ui->horizontalSlider_zoom_model_size->value());});
//    QTimer::singleShot(20,this,[=](){sendConfigHandle("X",ui->horizontalSlider_zoom_model_X->value());});
//    QTimer::singleShot(25,this,[=](){sendConfigHandle("Y",ui->horizontalSlider_zoom_model_Y->value());});
//    QTimer::singleShot(30,this,[=](){sendConfigHandle("Damping",ui->horizontalSlider_zoom_mouse_speed->value());});
//    QTimer::singleShot(35,this,[=](){sendConfigHandle("Mean",ui->horizontalSlider_zoom_eye_time->value());});
//    QTimer::singleShot(40,this,[=](){sendConfigHandle("MaximumDeviation",ui->horizontalSlider_zoom_eye_deviation->value());});
//    QTimer::singleShot(45,this,[=](){sendConfigHandle("Timescale",ui->horizontalSlider_zoom_eye_speed->value());});
//    QTimer::singleShot(50,this,[=](){sendConfigHandle("Gain",ui->horizontalSlider_zoom_audio_add->value());});
//    QTimer::singleShot(55,this,[=](){sendConfigHandle("Smoothing",ui->horizontalSlider_zoom_audio_smooth->value());});





//}

void SetLive2DDialogWidget::setLineEditText(QLineEdit *lineEdit, int value)
{
    lineEdit->setText(Transformation::IntToStringF2(value));
}

void SetLive2DDialogWidget::updateModelChange()
{
    for(int i=0;i<ui->listWidget_model->count();++i){
        QListWidgetItem* listWidgetItem=ui->listWidget_model->item(i);
        Live2DListItemsWidget* live2DListItemsWidget = static_cast<Live2DListItemsWidget*>(ui->listWidget_model->itemWidget(listWidgetItem));
        if(i==m_Live2dOpenId)live2DListItemsWidget->setChangeIs();
        else live2DListItemsWidget->setChangeNo();
    }

}
