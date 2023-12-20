#include "setlive2ddialogwidget.h"
#include "ui_setlive2ddialogwidget.h"


QProcess*   SetLive2DDialogWidget::     m_Live2dProcess =nullptr;
bool        SetLive2DDialogWidget::     live2DIsOpen    =false;

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
    delete ui;
}

void SetLive2DDialogWidget::init()
{
    this->resize(_Width,_Height);
    this->setWindowTitle("Live2D");
    this->setWindowIcon(QIcon(":/res/u77.svg"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    //初始化ListWidget
    ui->listWidget_model->setStyleSheet(
                "QScrollBar:vertical {width: 10px;background-color: #F5F5F5;margin: 0px 0px 0px 0px;border-radius: 5px;}"
                "QScrollBar::handle:vertical {background-color: #CCCCCC;min-height: 20px;border-radius: 5px;}"
                "QScrollBar::handle:vertical:hover {background-color: #BBBBBB;border-radius: 5px;}"
                "QScrollBar::add-line:vertical {height: 0px; subcontrol-position: bottom; subcontrol-origin: margin;}"
                "QScrollBar::sub-line:vertical {height: 0 px;subcontrol-position: top; subcontrol-origin: margin;}"
                "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background-color: #F5F5F5;border-radius: 5px;}"
                );
     ui->listWidget_model->setEditTriggers(QAbstractItemView::NoEditTriggers);         //禁止编辑
     ui->listWidget_model->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);       //禁用水平滑动条
     ui->listWidget_model->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);   //平滑效果


     for(int i=0;i<Config::get_LIVE2DMODELCONFIG_V().size();++i){
         addListItem(Config::get_LIVE2DMODELCONFIG_V().at(i));
     }

     ui->tabWidget_control->setCurrentIndex(0);

     ui->horizontalSlider_zoom_model_size->setRange(10,10000);      //0.1-100
     ui->horizontalSlider_zoom_mouse_speed->setRange(0,200);        //0-2
     ui->horizontalSlider_zoom_eye_time->setRange(100,1000);        //1-10
     ui->horizontalSlider_zoom_eye_deviation->setRange(50,500);     //0.5-5
     ui->horizontalSlider_zoom_eye_speed->setRange(100,2000);       //1-20
     ui->horizontalSlider_zoom_audio_add->setRange(100,1000);       //1-10
     ui->horizontalSlider_zoom_audio_smooth->setRange(0,100);       //0-1

     ui->radioButton_look_enable_yes->setChecked(Config::get_LIVE2DENABLEINIT_M()["look_enable"]);
     ui->radioButton_top_enable_yes->setChecked(Config::get_LIVE2DENABLEINIT_M()["top_enable"]);

     ui->horizontalSlider_zoom_model_size->setValue(Config::get_LIVE2DPARAMINIT_M()["model_size"]);
     ui->horizontalSlider_zoom_mouse_speed->setValue(Config::get_LIVE2DPARAMINIT_M()["mouse_speed"]);
     ui->horizontalSlider_zoom_eye_time->setValue(Config::get_LIVE2DPARAMINIT_M()["eye_time"]);
     ui->horizontalSlider_zoom_eye_deviation->setValue(Config::get_LIVE2DPARAMINIT_M()["eye_deviation"]);
     ui->horizontalSlider_zoom_eye_speed->setValue(Config::get_LIVE2DPARAMINIT_M()["eye_speed"]);
     ui->horizontalSlider_zoom_audio_add->setValue(Config::get_LIVE2DPARAMINIT_M()["audio_add"]);
     ui->horizontalSlider_zoom_audio_smooth->setValue(Config::get_LIVE2DPARAMINIT_M()["audio_smooth"]);

     ui->lineEdit_zoom_model_size->setEnabled(false);
     ui->lineEdit_zoom_mouse_speed->setEnabled(false);
     ui->lineEdit_zoom_eye_time->setEnabled(false);
     ui->lineEdit_zoom_eye_deviation->setEnabled(false);
     ui->lineEdit_zoom_eye_speed->setEnabled(false);
     ui->lineEdit_zoom_audio_add->setEnabled(false);
     ui->lineEdit_zoom_audio_smooth->setEnabled(false);


     updateLineEdit();

}

void SetLive2DDialogWidget::initConnect()
{
    //tcp


    SliderChange slider=&QSlider::sliderMoved;

    //启动模型
    connect(ui->pushButton_start,&QPushButton::clicked,this,[=](){


        if(ui->listWidget_model->count()<=0){
            QMessageBox::warning(this,"Error occurred","没有可用模型！");
            return ;
        }
        if(m_Live2dOpenId==-1){
            QMessageBox::warning(this,"Error occurred","请选择模型！");
            return ;
        }
        if(Config::get_LIVE2DMODELCONFIG_V()[m_Live2dOpenId].getFilePath().size()<3){

//            QListWidgetItem* listWidgetItem=ui->listWidget_model->item(0);
//            m_SelectModelPath=(static_cast<Live2DListItemsWidget*>(ui->listWidget_model->itemWidget(listWidgetItem)))->getModelItem().getFilePath();
//            Config::set_UNITY_STARTMODELPATH(m_SelectModelPath);
            QMessageBox::warning(this,"Error occurred","模型路径有误");
            return ;
        }

        if(live2DIsOpen==true){
            Config::set_UNITY_STARTMODELPATH(Config::get_LIVE2DMODELCONFIG_V()[m_Live2dOpenId].getFilePath());
            sendModelHandle("Init:null");
            //同步配置数据
            QTimer::singleShot(2000,this,[=](){
                updateForLive2dNet();

            });

            return;
        }
        SetLive2DDialogWidget::live2DIsOpen=true;
        m_Live2dProcess=new QProcess(ConfigWindow::_WindowPointer);
        m_Live2dProcess->setWorkingDirectory(Config::get_UNITY_DEMO_WORK_WAY());
        m_Live2dProcess->start(Config::get_UNITY_DEMO_WAY());
            //检查外部进程是否成功启动
        if (!m_Live2dProcess->waitForStarted()) {
            qDebug() << "Failed to start the process";
            return;
        }
        else {
            QTimer::singleShot(2000,this,[=](){
                updateForLive2dNet();

            });
            //同步配置数据
        }

    });

    //退出模型
    connect(ui->pushButton_quit,&QPushButton::clicked,this,[=](){

        SetLive2DDialogWidget::live2DIsOpen=false;
        delete m_Live2dProcess;
        m_Live2dProcess=nullptr;
    });

    //添加模型
    connect(ui->pushButton_add,&QPushButton::clicked,this,[=](){
        QString data = QFileDialog::getOpenFileName(nullptr, "Open File", "", "All Files (*model3.json)");
        if(data.size()<3){return ;}
        QVector<QString> v=Config::get_LIVE2DMODEL_V();
        v.push_back(data);
        Config::set_LIVE2DMODEL_V(v);
//        addListItem(data);
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        qDebug()<<"AAAAAAAAAAAAAa";
    });

    //删除模型
    connect(ui->pushButton_delete,&QPushButton::clicked,this,[=](){
        int id=ui->listWidget_model->currentRow();
        if(id<0){return ;}
        qDebug()<<QString::number(id)<<" 号模型被删除，Name is "<<Config::get_LIVE2DMODEL_V()[id];
        QVector<QString> v;
        for(int i=0;i<Config::get_LIVE2DMODEL_V().size();++i){
            if(i==id){
                continue;
            }
            v.push_back(Config::get_LIVE2DMODEL_V().at(i));
        }
        Config::set_LIVE2DMODEL_V(v);
        ui->listWidget_model->takeItem(id);


    });

    //修改模型
    connect(ui->pushButton_change,&QPushButton::clicked,this,[=](){
        ChangeLive2DWidget widget;
        widget.exec();
    });

    //Enable
    QObject::connect(ui->radioButton_look_enable_yes, &QRadioButton::toggled, [&](){
        qDebug()<<"启用看向鼠标";
        QString handleStr="";
        if (ui->radioButton_look_enable_yes->isChecked()) {
            handleStr=QString("Config:IsLookMouse,")+QString::number(1)+QString(";");
            qDebug()<<"YES";

        } else {
            handleStr=QString("Config:IsLookMouse,")+QString::number(0)+QString(";");
            qDebug()<<"NO";

        }
        sendModelHandle(handleStr);
    });

    QObject::connect(ui->radioButton_top_enable_yes, &QRadioButton::toggled, [&](){
        qDebug()<<"启用窗口置顶";
        QString handleStr="";
        if (ui->radioButton_top_enable_yes->isChecked()) {
            handleStr=QString("Window:")+QString("top")+QString(";");
            qDebug()<<"YES";

        } else {
            handleStr=QString("Window:")+QString("normal")+QString(";");
            qDebug()<<"NO";
        }
        sendModelHandle(handleStr);
    });

    //Config
    //模型缩放比例
    connect(ui->horizontalSlider_zoom_model_size,slider,this,[=](int value){
        double val=double(value)/double(100);
        QString handleStr=QString("Config:ScaleScaleProportion,")+QString::number(val)+QString(";");
        sendModelHandle(handleStr);
        updateLineEdit();
    });

    //看向鼠标速度
    connect(ui->horizontalSlider_zoom_mouse_speed,slider,this,[=](int value){
        double val=double(value)/double(100);
        QString handleStr=QString("Config:Damping,")+QString::number(val)+QString(";");
        sendModelHandle(handleStr);
        updateLineEdit();
    });

    //平均眨眼周期
    connect(ui->horizontalSlider_zoom_eye_time,slider,this,[=](int value){
        double val=double(value)/double(100);
        QString handleStr=QString("Config:Mean,")+QString::number(val)+QString(";");
        sendModelHandle(handleStr);
        updateLineEdit();
    });

    //眨眼偏差时间
    connect(ui->horizontalSlider_zoom_eye_deviation,slider,this,[=](int value){
        double val=double(value)/double(100);
        QString handleStr=QString("Config:MaximumDeviation,")+QString::number(val)+QString(";");
        sendModelHandle(handleStr);
        updateLineEdit();
    });

    //眨眼速度快慢
    connect(ui->horizontalSlider_zoom_eye_speed,slider,this,[=](int value){
        double val=double(value)/double(100);
        QString handleStr=QString("Config:Timescale,")+QString::number(val)+QString(";");
        sendModelHandle(handleStr);
        updateLineEdit();
    });

    //音频增益效果
    connect(ui->horizontalSlider_zoom_audio_add,slider,this,[=](int value){
        double val=double(value)/double(100);
        QString handleStr=QString("Config:Gain,")+QString::number(val)+QString(";");
        sendModelHandle(handleStr);
        updateLineEdit();
    });

    //音频平滑效果
    connect(ui->horizontalSlider_zoom_audio_smooth,slider,this,[=](int value){
        double val=double(value)/double(100);
        QString handleStr=QString("Config:Smoothing,")+QString::number(val)+QString(";");
        sendModelHandle(handleStr);
        updateLineEdit();
    });

}

void SetLive2DDialogWidget::changeConfig()
{



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
        m_Live2dOpenId=passItem.getModelId();
        Config::set_UNITY_STARTMODELPATH(Config::get_LIVE2DMODELCONFIG_V()[m_Live2dOpenId].getFilePath());
        ui->listWidget_model->setCurrentItem(item);

        qDebug()<<"pass model id : "<<passItem.getModelId();

        ui->lineEdit_name->setText(passItem.getModelName());
        ui->lineEdit_way->setText(passItem.getFilePath());

        if(passItem.getLookEnable())ui->radioButton_look_enable_yes->setChecked(true);
        else ui->radioButton_look_enable_no->setChecked(true);
        if(passItem.getTopEnable())ui->radioButton_top_enable_yes->setChecked(true);
        else ui->radioButton_top_enable_no->setChecked(true);

        ui->horizontalSlider_zoom_model_size->setValue(passItem.getModelSize());
        ui->horizontalSlider_zoom_mouse_speed->setValue(passItem.getMouseSpeed());
        ui->horizontalSlider_zoom_eye_time->setValue(passItem.getEyeTime());
        ui->horizontalSlider_zoom_eye_deviation->setValue(passItem.getEyeDeviation());
        ui->horizontalSlider_zoom_eye_speed->setValue(passItem.getEyeSpeed());
        ui->horizontalSlider_zoom_audio_add->setValue(passItem.getAudioAdd());
        ui->horizontalSlider_zoom_audio_smooth->setValue(passItem.getAudioSmooth());

        ui->textEdit_explain->setText(passItem.getModelDescription());

        updateLineEdit();


    });
}

void SetLive2DDialogWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    updateListWidget();

}

void SetLive2DDialogWidget::updateListWidget()
{
    //可扩展控件Size变化
}

void SetLive2DDialogWidget::updateLineEdit()
{

     ui->lineEdit_zoom_model_size->setText(QString::number(double(ui->horizontalSlider_zoom_model_size->value())/double(100)));
     ui->lineEdit_zoom_mouse_speed->setText(QString::number(double(ui->horizontalSlider_zoom_mouse_speed->value())/double(100)));
     ui->lineEdit_zoom_eye_time->setText(QString::number(double(ui->horizontalSlider_zoom_eye_time->value())/double(100)));
     ui->lineEdit_zoom_eye_deviation->setText(QString::number(double(ui->horizontalSlider_zoom_eye_deviation->value())/double(100)));
     ui->lineEdit_zoom_eye_speed->setText(QString::number(double(ui->horizontalSlider_zoom_eye_speed->value())/double(100)));
     ui->lineEdit_zoom_audio_add->setText(QString::number(double(ui->horizontalSlider_zoom_audio_add->value())/double(100)));
     ui->lineEdit_zoom_audio_smooth->setText(QString::number(double(ui->horizontalSlider_zoom_audio_smooth->value())/double(100)));

}

void SetLive2DDialogWidget::updateForLive2dNet()
{

    sendModelHandle(QString("Config:ScaleScaleProportion,")+QString::number(double(ui->horizontalSlider_zoom_model_size->value())/double(100))+QString(";"));
    sendModelHandle(QString("Config:ScaleScaleProportion,")+QString::number(double(ui->horizontalSlider_zoom_model_size->value())/double(100))+QString(";"));
    sendModelHandle(QString("Config:Damping,")+QString::number(double(ui->horizontalSlider_zoom_mouse_speed->value())/double(100))+QString(";"));
    sendModelHandle(QString("Config:Mean,")+QString::number(double(ui->horizontalSlider_zoom_eye_time->value())/double(100))+QString(";"));
    sendModelHandle(QString("Config:MaximumDeviation,")+QString::number(double(ui->horizontalSlider_zoom_eye_deviation->value())/double(100))+QString(";"));
    sendModelHandle(QString("Config:Timescale,")+QString::number(double(ui->horizontalSlider_zoom_eye_speed->value())/double(100))+QString(";"));
    sendModelHandle(QString("Config:Gain,")+QString::number(double(ui->horizontalSlider_zoom_audio_add->value())/double(100))+QString(";"));
    sendModelHandle(QString("Config:Smoothing,")+QString::number(double(ui->horizontalSlider_zoom_audio_smooth->value())/double(100))+QString(";"));
}
