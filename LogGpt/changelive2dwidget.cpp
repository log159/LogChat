#include "changelive2dwidget.h"
#include "ui_changelive2dwidget.h"


#define CONNECT_CURRENT(C,T,L)\
connect(C,T,[=](int index){\
QString newItemText=C->itemText(index);\
bool exists = false;\
for (int i = 0; i < L->count(); ++i){\
QListWidgetItem *item = L->item(i);\
if (item->text() == newItemText) {exists = true;break;}}\
if (!exists)L->addItem(newItemText);});

#define CONNECT_REMOVE(P,L)\
connect(P,&QPushButton::clicked,[=](){\
QListWidgetItem* selectedItem = L->currentItem();\
if (selectedItem != nullptr)\
{delete L->takeItem(L->row(selectedItem));}});

#define CONNECT_SAVE(L,T,E)\
for(int i = 0; i < L->count(); ++i){\
QListWidgetItem *item = L->item(i);\
if(item != nullptr)\
T[item->text()]|=static_cast<size_t>(E);}


ChangeLive2DWidget::ChangeLive2DWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeLive2DWidget)
{
    ui->setupUi(this);

    init();
}

ChangeLive2DWidget::~ChangeLive2DWidget()
{
    delete ui;
}
void ChangeLive2DWidget::init()
{
    this->resize(WIDTH,HEIGHT);
    this->setWindowTitle("模型修改");
    this->setWindowIcon(QIcon(":/res/u77.svg"));
    setWindowFlags((windowFlags() & ~Qt::WindowContextHelpButtonHint));

    QVector<QListWidget*> wlsList;
    wlsList.push_back(ui->listWidget_parameter);
    wlsList.push_back(ui->listWidget_part);
    wlsList.push_back(ui->listWidget_drawable);
    wlsList.push_back(ui->listWidget_expression);
    wlsList.push_back(ui->listWidget_motion);
    wlsList.push_back(ui->listWidget_harmonic);

    for(auto& val:wlsList){
        val->setEditTriggers(QAbstractItemView::NoEditTriggers);         //禁止编辑
        val->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);       //禁用水平滑动条
        val->setFocusPolicy(Qt::NoFocus);                                //禁止获取焦点
        val->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);   //平滑效果
        val->setAttribute(Qt::WA_TranslucentBackground);
    }


    QFile file(":/main.qss");
    if(file.open(QFile::ReadOnly)){
        QString styleSheet = QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
        file.close();
    }

}
void ChangeLive2DWidget::refresh(const QString &path)
{
    this->m_FilePath=path;

    initValueExplainMap();
    initParameterItemsMap();
    initPartItemsMap();
    initDrawableItemsMap();
    initExpressionItemsMap();
    InitMotionItemsMap();
    initParameterCoverMap();
    initPartCovermap();
    initDrawableCovermap();

//    initHarmCoverMap(path);


    initUiParameterList();
    initUiPartList();
    initUiDrawableList();
    initUiExpressionList();
    initUiMotionList();
    initUiShiftList();

    initUiConnectParameterButton();
    initUiConnectPartButton();
    initUiConnectDrawableButton();
    initUiConnectExpressionButton();
    initUiConnectMotionButton();
    initUiConnectShift();





//    //控件谐波
//    {
////        ui->listWidget_harmonic->set
//        QMap<QString,QVector<int>>::iterator it=m_ParameterItemsMap.begin();
//            for(;it!=m_ParameterItemsMap.end();++it){

//    //            //控件添加
//                QListWidgetItem* item = new QListWidgetItem();
//                Live2DAnimationItemsWidget* widget=new Live2DAnimationItemsWidget;

//                widget->resize(ui->listWidget_harmonic->size().width(),widget->height());
//                ui->listWidget_harmonic->addItem(item);
//                item->setSizeHint(widget->size());
//                ui->listWidget_harmonic->setItemWidget(item,widget);
//                ui->listWidget_harmonic->scrollToBottom();

//                widget->setName(it.key());

//                if(m_ValueExplainMap[it.key()]!=""){
//                    widget->setExplain(m_ValueExplainMap[it.key()]);
//                }
//                QVector<int>v=m_HarmCoverMap[it.key()];
//                if(v.size()>=3){
//                    widget->setRule(v[0]);
//                    widget->setSpeed(v[1]);
//                    widget->setUseful(v[2]!=0?true:false);

//                }

//    //            SendPassByPart sendPass=&Live2DPartItemsWidget::sendPass;
//    //            connect(widget,sendPass,[=](ModelPartItem passItem){
//    //                qDebug()<<"chagngelive2dwidget: "<<passItem.getName();

//    //            });

//    //            connect(widget,&Live2DPartItemsWidget::sendHandle,[=](QString handleStr){
//    //                emit sendhandle(handleStr);
//    //            });

//    //        }
//            ui->listWidget_harmonic->scrollToTop();
//        }
//    }
}

void ChangeLive2DWidget::initParameterCoverMap()
{
    m_ParameterCoverMap.clear();
    QString file_path=this->m_FilePath+"/"+::ConfigModelUserFileName;
    QMap<QString,QString> read_map = Config::get_OTHER_BASE(file_path,ItemM[::PARAMETERCHANGELIST]);
    if(read_map.isEmpty())
        return;
    QRegExp re("(-?\\d+)");
    for (QMap<QString,QString>::iterator it=read_map.begin();it!=read_map.end();++it) {
        if (re.indexIn(it.value()) != -1) {
            int num = re.cap(1).toInt();
            m_ParameterCoverMap[it.key()]=num;
        }
    }

}

void ChangeLive2DWidget::initPartCovermap()
{
    m_PartCoverMap.clear();
    QString file_path=this->m_FilePath+"/"+::ConfigModelUserFileName;
    QMap<QString,QString> read_map = Config::get_OTHER_BASE(file_path,ItemM[::PARTCHANGELIST]);
    if(read_map.isEmpty())
        return;
    QRegExp re("(-?\\d+)");
    for (QMap<QString,QString>::iterator it=read_map.begin();it!=read_map.end();++it) {
        if (re.indexIn(it.value()) != -1) {
            int num = re.cap(1).toInt();
            m_PartCoverMap[it.key()]=num;
        }
    }
}

void ChangeLive2DWidget::initDrawableCovermap()
{
    m_DrawableCoverMap.clear();
    QString file_path=this->m_FilePath+"/"+::ConfigModelUserFileName;
    QMap<QString,QString> read_map = Config::get_OTHER_BASE(file_path,ItemM[::DRAWABLECHANGELIST]);
    if(read_map.isEmpty())
        return;
    QRegExp re("(-?\\d+)");
    for (QMap<QString,QString>::iterator it=read_map.begin();it!=read_map.end();++it) {
        if (re.indexIn(it.value()) != -1) {
            int num = re.cap(1).toInt();
            m_DrawableCoverMap[it.key()]=num>0?true:false;
        }
    }
}

void ChangeLive2DWidget::initHarmCoverMap()
{
//    QFile file(path+"/HARMONICCHANGELIST.txt");
//    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
//        qDebug()<<"Part Item File Open Fail!";
//        return;
//    }
//    QTextStream in(&file);
//    in.setCodec("UTF-8");
//    QString read_str = in.readAll();
//    file.close();


//    m_HarmCoverMap.clear();

//    QStringList lines = read_str.split('\n', QString::SkipEmptyParts);
//    QMap<QString, QString> keyValueMap;

//    for (const QString& line : lines) {

//            // 使用正则表达式提取Name和三个浮点数
//               QRegExp regex("\\[([^\\]]+)\\]:\\[(-?\\d+),(-?\\d+),(-?\\d+)\\];");
//               int pos = regex.indexIn(line);
//               if (pos != -1) {
//                   QString name = regex.cap(1);
//                   int num1 = regex.cap(2).toInt();
//                   int num2 = regex.cap(3).toInt();
//                   int num3 = regex.cap(4).toInt();
//                   QVector<int> v={0,0,0};
//                   v[0]=num1;v[1]=num2;v[2]=num3;
//                   m_HarmCoverMap[name]=v;
//               } else {
//                   qDebug() << "String does not match the pattern.";
//               }

//    }

    //    return;
}

void ChangeLive2DWidget::initUiParameterList()
{
    QMap<QString,QVector<int>>::iterator it=m_ParameterItemsMap.begin();
    for(;it!=m_ParameterItemsMap.end();++it){
        //控件添加
        QListWidgetItem* item = new QListWidgetItem();
        Live2DParamItemsWidget* widget=new Live2DParamItemsWidget;
        ChangeConfigItem changeConfigItem;
        changeConfigItem.setName(it.key());
        changeConfigItem.setDefaultValue(it.value().at(0));
        changeConfigItem.setMinValue(it.value().at(1));
        changeConfigItem.setMaxValue(it.value().at(2));
        widget->init(changeConfigItem);
        widget->resize(ui->listWidget_parameter->size().width(),widget->height());
        ui->listWidget_parameter->addItem(item);
        item->setSizeHint(widget->size());
        ui->listWidget_parameter->setItemWidget(item,widget);
        ui->listWidget_parameter->scrollToBottom();
        if(m_ValueExplainMap[it.key()]!=""){
            widget->setExplain(m_ValueExplainMap[it.key()]);
        }
        QString key=it.key();
        if(m_ParameterCoverMap.contains(key))
            widget->setValue(m_ParameterCoverMap[key]);
        SendPassByParam sendPass=&Live2DParamItemsWidget::sendPass;
        connect(widget,sendPass,[=](ChangeConfigItem passItem){
            qDebug()<<"chagngelive2dwidget: "<<passItem.getName();
        });
        connect(widget,&Live2DParamItemsWidget::sendHandle,[=](QString handleStr){
            emit sendHandle(handleStr);
        });
    }
    ui->listWidget_parameter->scrollToTop();
}

void ChangeLive2DWidget::initUiPartList()
{
    QMap<QString,QVector<int>>::iterator it=m_PartItemsMap.begin();
    for(;it!=m_PartItemsMap.end();++it){
        //控件添加
        QListWidgetItem* item = new QListWidgetItem();
        Live2DPartItemsWidget* widget=new Live2DPartItemsWidget;
        ChangeConfigItem changeConfigItem;
        changeConfigItem.setName(it.key());
        changeConfigItem.setDefaultValue(it.value().at(0));
        changeConfigItem.setMinValue(it.value().at(1));
        changeConfigItem.setMaxValue(it.value().at(2));
        widget->init(changeConfigItem);
        widget->resize(ui->listWidget_part->size().width(),widget->height());
        ui->listWidget_part->addItem(item);
        item->setSizeHint(widget->size());
        ui->listWidget_part->setItemWidget(item,widget);
        ui->listWidget_part->scrollToBottom();
        if(m_ValueExplainMap[it.key()]!=""){
            widget->setExplain(m_ValueExplainMap[it.key()]);
        }
        QString key=it.key();
        if(m_PartCoverMap.contains(key))
            widget->setValue(m_PartCoverMap[key]);
        SendPassByPart sendPass=&Live2DPartItemsWidget::sendPass;
        connect(widget,sendPass,[=](ChangeConfigItem passItem){
            qDebug()<<"chagngelive2dwidget: "<<passItem.getName();
        });
        connect(widget,&Live2DPartItemsWidget::sendHandle,[=](QString handleStr){
            emit sendHandle(handleStr);
        });
    }
    ui->listWidget_part->scrollToTop();
}

void ChangeLive2DWidget::initUiDrawableList()
{
    QMap<QString,bool>::iterator it=m_DrawableItemsMap.begin();
    for(;it!=m_DrawableItemsMap.end();++it){

        //控件添加
        QListWidgetItem* item = new QListWidgetItem();
        Live2DDrawItemsWidget* widget=new Live2DDrawItemsWidget;
        ChangeConfigItem changeConfigItem;
        changeConfigItem.setName(it.key());
        changeConfigItem.setDefaultValue(int(it.value()));
        changeConfigItem.setMinValue(0);
        changeConfigItem.setMaxValue(1);
        widget->init(changeConfigItem);
        widget->resize(ui->listWidget_drawable->size().width(),widget->height());
        ui->listWidget_drawable->addItem(item);
        item->setSizeHint(widget->size());
        ui->listWidget_drawable->setItemWidget(item,widget);
        ui->listWidget_drawable->scrollToBottom();
        QString key=it.key();
        if(m_DrawableCoverMap.contains(key)){
            widget->setValue(m_DrawableCoverMap[key]);
        }

        SendPassByDraw sendPass=&Live2DDrawItemsWidget::sendPass;
        connect(widget,sendPass,[=](ChangeConfigItem passItem){
            qDebug()<<"chagngelive2dwidget: "<<passItem.getName();
        });

        connect(widget,&Live2DDrawItemsWidget::sendHandle,[=](QString handleStr){
            emit sendHandle(handleStr);
        });

    }
    ui->listWidget_drawable->scrollToTop();
}

void ChangeLive2DWidget::initUiExpressionList()
{
    QMap<QString,int>::iterator it=m_ExpressionItemsMap.begin();
    for(;it!=m_ExpressionItemsMap.end();++it){

        //控件添加
        QListWidgetItem* item = new QListWidgetItem();
        Live2dExpAndMotItemsWidget* widget=new Live2dExpAndMotItemsWidget;
        widget->init(QPair<QString,int>(it.key(),it.value()));
        widget->setHandleName(Live2dExpAndMotItemsWidget::EN::EXP);
        widget->resize(ui->listWidget_expression->size().width(),widget->height());
        ui->listWidget_expression->addItem(item);
        item->setSizeHint(widget->size());
        ui->listWidget_expression->setItemWidget(item,widget);
        ui->listWidget_expression->scrollToBottom();
        QString key=it.key();

        SendPassByExpMot sendPass=&Live2dExpAndMotItemsWidget::sendPass;
        connect(widget,sendPass,[=](QPair<QString,int> data){
            qDebug()<<"chagngelive2dwidget: "<<data.first;
        });

        connect(widget,&Live2dExpAndMotItemsWidget::sendHandle,[=](QString handleStr){
            emit sendHandle(handleStr);
        });

    }
    ui->listWidget_expression->scrollToTop();
}

void ChangeLive2DWidget::initUiMotionList()
{
    QMap<QString,int>::iterator it=m_MotionItemsMap.begin();
    for(;it!=m_MotionItemsMap.end();++it){

        //控件添加
        QListWidgetItem* item = new QListWidgetItem();
        Live2dExpAndMotItemsWidget* widget=new Live2dExpAndMotItemsWidget;
        widget->init(QPair<QString,int>(it.key(),it.value()));
        widget->setHandleName(Live2dExpAndMotItemsWidget::EN::MOT);
        widget->resize(ui->listWidget_motion->size().width(),widget->height());
        ui->listWidget_motion->addItem(item);
        item->setSizeHint(widget->size());
        ui->listWidget_motion->setItemWidget(item,widget);
        ui->listWidget_motion->scrollToBottom();
        QString key=it.key();

        SendPassByExpMot sendPass=&Live2dExpAndMotItemsWidget::sendPass;
        connect(widget,sendPass,[=](QPair<QString,int> data){
            qDebug()<<"chagngelive2dwidget: "<<data.first;
        });

        connect(widget,&Live2dExpAndMotItemsWidget::sendHandle,[=](QString handleStr){
            emit sendHandle(handleStr);
        });

    }
    ui->listWidget_expression->scrollToTop();
}

void ChangeLive2DWidget::initUiConnectParameterButton()
{
    connect(ui->pushButton_save_parameter,&QPushButton::clicked,[=](){
        QMap<QString,QString>changeM;
        for(int i=0;i<ui->listWidget_parameter->count();++i){
            QListWidgetItem* listWidgetItem=ui->listWidget_parameter->item(i);
            Live2DParamItemsWidget* live2DParamItemsWidget= (static_cast<Live2DParamItemsWidget*>(ui->listWidget_parameter->itemWidget(listWidgetItem)));
            QString item_name=live2DParamItemsWidget->getName();
            int item_value=live2DParamItemsWidget->getValue();
            if(live2DParamItemsWidget->isDefault()==false){
                changeM[item_name]=QString::number(item_value);
            }
        }
        Config::set_OTHER_BASE(this->m_FilePath+"/"+::ConfigModelUserFileName,::ItemM[::EnItem::PARAMETERCHANGELIST],changeM);
    });

    connect(ui->pushButton_reset_parameter,&QPushButton::clicked,[=](){
        for(int i=0;i<ui->listWidget_parameter->count();++i){
            QListWidgetItem* listWidgetItem=ui->listWidget_parameter->item(i);
            (static_cast<Live2DParamItemsWidget*>(ui->listWidget_parameter->itemWidget(listWidgetItem)))->resetValue();
        }
        emit sendHandle("InitItems:parameters;");
    });
}

void ChangeLive2DWidget::initUiConnectPartButton()
{
    connect(ui->pushButton_save_part,&QPushButton::clicked,[=](){
        QMap<QString,QString>changeM;
        for(int i=0;i<ui->listWidget_part->count();++i){
            QListWidgetItem* listWidgetItem=ui->listWidget_part->item(i);
            Live2DPartItemsWidget* live2DPartItemsWidget= (static_cast<Live2DPartItemsWidget*>(ui->listWidget_part->itemWidget(listWidgetItem)));
            QString item_name=live2DPartItemsWidget->getName();
            int item_value=live2DPartItemsWidget->getValue();
            if(live2DPartItemsWidget->isDefault()==false){
                changeM[item_name]=QString::number(item_value);
            }
        }
        Config::set_OTHER_BASE(this->m_FilePath+"/"+::ConfigModelUserFileName,::ItemM[::EnItem::PARTCHANGELIST],changeM);
    });

    connect(ui->pushButton_reset_part,&QPushButton::clicked,[=](){
        for(int i=0;i<ui->listWidget_part->count();++i){
            QListWidgetItem* listWidgetItem=ui->listWidget_part->item(i);
            (static_cast<Live2DPartItemsWidget*>(ui->listWidget_part->itemWidget(listWidgetItem)))->resetValue();
        }
        emit sendHandle("InitItems:parts;");
    });
}

void ChangeLive2DWidget::initUiConnectDrawableButton()
{
    connect(ui->pushButton_save_drawable,&QPushButton::clicked,[=](){
        QMap<QString,QString>changeM;
        for(int i=0;i<ui->listWidget_drawable->count();++i){
            QListWidgetItem* listWidgetItem=ui->listWidget_drawable->item(i);
            Live2DDrawItemsWidget* live2DDrawItemsWidget= (static_cast<Live2DDrawItemsWidget*>(ui->listWidget_drawable->itemWidget(listWidgetItem)));
            QString item_name=live2DDrawItemsWidget->getName();
            int item_value=live2DDrawItemsWidget->getValue();
            if(live2DDrawItemsWidget->isDefault()==false){
                changeM[item_name]=QString::number(item_value);
            }
        }
        Config::set_OTHER_BASE(this->m_FilePath+"/"+::ConfigModelUserFileName,::ItemM[::EnItem::DRAWABLECHANGELIST],changeM);
    });

    connect(ui->pushButton_reset_drawable,&QPushButton::clicked,[=](){

        for(int i=0;i<ui->listWidget_drawable->count();++i){
            QListWidgetItem* listWidgetItem=ui->listWidget_drawable->item(i);
            (static_cast<Live2DDrawItemsWidget*>(ui->listWidget_drawable->itemWidget(listWidgetItem)))->resetValue();

        }
        emit sendHandle("InitItems:drawables;");
    });
}

void ChangeLive2DWidget::initUiConnectExpressionButton()
{
    connect(ui->pushButton_expression_reset,&QPushButton::clicked,[=](){
        emit sendHandle("InitItems:parameters;");
    });
}

void ChangeLive2DWidget::initUiConnectMotionButton()
{
    connect(ui->pushButton_motion_reset,&QPushButton::clicked,[=](){
        emit sendHandle("InitItems:parameters;");
    });
}

void ChangeLive2DWidget::initUiConnectShift()
{
    Activated activated=&QComboBox::activated;
    CONNECT_CURRENT(ui->comboBox_exp_start,activated,ui->listWidget_exp_start);
    CONNECT_CURRENT(ui->comboBox_exp_wait,activated,ui->listWidget_exp_wait);
    CONNECT_CURRENT(ui->comboBox_exp_react,activated,ui->listWidget_exp_react);
    CONNECT_CURRENT(ui->comboBox_mot_start,activated,ui->listWidget_mot_start);
    CONNECT_CURRENT(ui->comboBox_mot_wait,activated,ui->listWidget_mot_wait);
    CONNECT_CURRENT(ui->comboBox_mot_react,activated,ui->listWidget_mot_react);

    CONNECT_REMOVE(ui->pushButton_exp_start_remove,ui->listWidget_exp_start);
    CONNECT_REMOVE(ui->pushButton_exp_wait_remove,ui->listWidget_exp_wait);
    CONNECT_REMOVE(ui->pushButton_exp_react_remove,ui->listWidget_exp_react);
    CONNECT_REMOVE(ui->pushButton_mot_start_remove,ui->listWidget_mot_start);
    CONNECT_REMOVE(ui->pushButton_mot_wait_remove,ui->listWidget_mot_wait);
    CONNECT_REMOVE(ui->pushButton_mot_react_remove,ui->listWidget_mot_react);

    connect(ui->pushButton_saveshift,&QPushButton::clicked,[=](){
        QMap<QString,int>expM;
        QMap<QString,int>motM;
        QMap<QString,QString>expDataM;
        QMap<QString,QString>motDataM;
        CONNECT_SAVE(ui->listWidget_exp_start,expM,ShiftEn::START);
        CONNECT_SAVE(ui->listWidget_exp_wait,expM,ShiftEn::WAIT);
        CONNECT_SAVE(ui->listWidget_exp_react,expM,ShiftEn::REACT);
        CONNECT_SAVE(ui->listWidget_mot_start,motM,ShiftEn::START);
        CONNECT_SAVE(ui->listWidget_mot_wait,motM,ShiftEn::WAIT);
        CONNECT_SAVE(ui->listWidget_mot_react,motM,ShiftEn::REACT);

        for(auto it=expM.begin();it!=expM.end();++it)
            expDataM[it.key()]=QString::number(it.value());
        for(auto it=motM.begin();it!=motM.end();++it)
            motDataM[it.key()]=QString::number(it.value());
        QString configModelUserFilePath=this->m_FilePath+"/"+::ConfigModelUserFileName;
        Config::set_OTHER_BASE(configModelUserFilePath,::ItemM[::EnItem::EXPRESSIONSHIFT],expDataM);
        Config::set_OTHER_BASE(configModelUserFilePath,::ItemM[::EnItem::MOTIONSHIFT],motDataM);
    });
}

void ChangeLive2DWidget::initUiShiftList()
{
    for(QMap<QString,int>::iterator it=m_ExpressionItemsMap.begin();it!=m_ExpressionItemsMap.end();++it){
        ui->comboBox_exp_start->addItem(it.key());
        ui->comboBox_exp_react->addItem(it.key());
        ui->comboBox_exp_wait->addItem(it.key());
    }
    for(QMap<QString,int>::iterator it=m_MotionItemsMap.begin();it!=m_MotionItemsMap.end();++it){
        ui->comboBox_mot_start->addItem(it.key());
        ui->comboBox_mot_react->addItem(it.key());
        ui->comboBox_mot_wait->addItem(it.key());
    }
    QString configModelUserFilePath=this->m_FilePath+"/"+::ConfigModelUserFileName;
    QMap<QString,QString>expDataM=Config::get_OTHER_BASE(configModelUserFilePath,::ItemM[::EnItem::EXPRESSIONSHIFT]);
    QMap<QString,QString>motDataM=Config::get_OTHER_BASE(configModelUserFilePath,::ItemM[::EnItem::MOTIONSHIFT]);

    for (auto it=expDataM.begin();it!=expDataM.end();++it) {
        if(expDataM[it.key()].toInt() & static_cast<int>(ShiftEn::START))
            ui->listWidget_exp_start->addItem(it.key());
        if(expDataM[it.key()].toInt() & static_cast<int>(ShiftEn::REACT))
            ui->listWidget_exp_react->addItem(it.key());
        if(expDataM[it.key()].toInt() & static_cast<int>(ShiftEn::WAIT))
            ui->listWidget_exp_wait->addItem(it.key());
    }
    for (auto it=motDataM.begin();it!=motDataM.end();++it) {
        if(motDataM[it.key()].toInt() & static_cast<int>(ShiftEn::START))
            ui->listWidget_mot_start->addItem(it.key());
        if(motDataM[it.key()].toInt() & static_cast<int>(ShiftEn::REACT))
            ui->listWidget_mot_react->addItem(it.key());
        if(motDataM[it.key()].toInt() & static_cast<int>(ShiftEn::WAIT))
            ui->listWidget_mot_wait->addItem(it.key());
    }
}
void ChangeLive2DWidget::initParameterItemsMap()
{
    m_ParameterItemsMap.clear();
    QString file_path=this->m_FilePath+"/"+::ConfigModelUserFileName;
    QMap<QString,QString> read_map = Config::get_OTHER_BASE(file_path,ItemM[::PARAMETERLIST]);
    if(read_map.isEmpty())
        return;

    QRegularExpression re("(-?\\d*\\.?\\d+),(-?\\d*\\.?\\d+),(-?\\d*\\.?\\d+)");
    for (QMap<QString,QString>::iterator it=read_map.begin(); it!=read_map.end(); ++it) {
        QRegularExpressionMatch match = re.match(it.value());
        if (match.hasMatch()) {
            int num1 = int(match.captured(1).toFloat()*100.f);
            int num2 = int(match.captured(2).toFloat()*100.f);
            int num3 = int(match.captured(3).toFloat()*100.f);
            QVector<int> v = {num1, num2, num3};
            m_ParameterItemsMap[it.key()] = v;
        }
    }
    return;

}

void ChangeLive2DWidget::initPartItemsMap()
{
    m_PartItemsMap.clear();
    QString file_path=this->m_FilePath+"/"+::ConfigModelUserFileName;
    QMap<QString,QString> read_map = Config::get_OTHER_BASE(file_path,ItemM[::PARTLIST]);
    if(read_map.isEmpty())
        return;

    QRegularExpression re("(-?\\d*\\.?\\d+),(-?\\d*\\.?\\d+),(-?\\d*\\.?\\d+)");
    for (QMap<QString,QString>::iterator it=read_map.begin(); it!=read_map.end(); ++it) {
        QRegularExpressionMatch match = re.match(it.value());
        if (match.hasMatch()) {
            int num1 = int(match.captured(1).toFloat()*100.f);
            int num2 = int(match.captured(2).toFloat()*100.f);
            int num3 = int(match.captured(3).toFloat()*100.f);
            QVector<int> v = {num1, num2, num3};
            m_PartItemsMap[it.key()] = v;
        }
    }
    return;
}

void ChangeLive2DWidget::initDrawableItemsMap()
{
    m_DrawableItemsMap.clear();
    QString file_path=this->m_FilePath+"/"+::ConfigModelUserFileName;
    QMap<QString,QString> read_map = Config::get_OTHER_BASE(file_path,ItemM[::DRAWABLELIST]);
    if(read_map.isEmpty())
        return;
    QRegExp re("(-?\\d+)");
    for (QMap<QString,QString>::iterator it=read_map.begin();it!=read_map.end();++it) {
        if (re.indexIn(it.value()) != -1) {
            int num = re.cap(1).toInt();
            m_DrawableItemsMap[it.key()]=num>0?true:false;
        }
    }
    return;
}

void ChangeLive2DWidget::initExpressionItemsMap()
{
    m_ExpressionItemsMap.clear();
    QString file_path=this->m_FilePath+"/"+::ConfigModelUserFileName;
    QMap<QString,QString> read_map = Config::get_OTHER_BASE(file_path,ItemM[::EXPRESSIONLIST]);
    if(read_map.isEmpty())
        return;
    QRegExp re("(-?\\d+)");
    for (QMap<QString,QString>::iterator it=read_map.begin();it!=read_map.end();++it) {
        if (re.indexIn(it.value()) != -1) {
            int num = re.cap(1).toInt();
            m_ExpressionItemsMap[it.key()]=num;
        }
    }
    return;
}

void ChangeLive2DWidget::InitMotionItemsMap()
{
    m_MotionItemsMap.clear();
    QString file_path=this->m_FilePath+"/"+::ConfigModelUserFileName;
    QMap<QString,QString> read_map = Config::get_OTHER_BASE(file_path,ItemM[::MOTIONLIST]);
    if(read_map.isEmpty())
        return;
    QRegExp re("(-?\\d+)");
    for (QMap<QString,QString>::iterator it=read_map.begin();it!=read_map.end();++it) {
        if (re.indexIn(it.value()) != -1) {
            int num = re.cap(1).toInt();
            m_MotionItemsMap[it.key()]=num;
        }
    }
    return;
}


void ChangeLive2DWidget::initValueExplainMap()
{
    QDir directory(this->m_FilePath); // 替换为你的目录路径
    QStringList filter;
    filter << "*.cdi3.json"; // 筛选条件，只保留以 .cdi3.json 结尾的文件
    directory.setNameFilters(filter);

    QStringList files = directory.entryList(QDir::Files | QDir::Readable);
    if(files.size()<=0){
        qDebug()<<"无.cdi3.json文件";
        return;
    }
    QString file_path(this->m_FilePath+"/"+files[0]);
    QMap<QString,QString> expM= parseCdi3Json(ConfigFileIO::getFileAllInformation(file_path));
    QMap<QString,QString>::iterator it=expM.begin();
    for(;it!=expM.end();++it){
        m_ValueExplainMap[it.key()]=it.value();
    };

}
QMap<QString, QString> ChangeLive2DWidget::parseCdi3Json(const QString& jsonStr) {
    QMap<QString, QString> resultMap;

       // 将字符串解析为 QJsonDocument
       QJsonDocument doc = QJsonDocument::fromJson(jsonStr.toUtf8());
       if (doc.isNull() || !doc.isObject()) {
           qDebug() << "Invalid JSON format!";
           return resultMap;
       }
       QJsonObject rootObj = doc.object();
       // 解析 Parameters 数组
       QJsonValue parametersVal = rootObj.value("Parameters");
       if (parametersVal.isArray()) {
           QJsonArray parametersArray = parametersVal.toArray();
           for (int i = 0; i < parametersArray.size(); ++i) {
               QJsonObject obj = parametersArray[i].toObject();
               QString id = obj.value("Id").toString();
               QString name = obj.value("Name").toString();
               resultMap.insert(id, name);
           }
       }
//       // 解析 ParameterGroups 数组
//       QJsonValue parameterGroupsVal = rootObj.value("ParameterGroups");
//       if (parameterGroupsVal.isArray()) {
//           QJsonArray parameterGroupsArray = parameterGroupsVal.toArray();
//           for (int i = 0; i < parameterGroupsArray.size(); ++i) {
//               QJsonObject obj = parameterGroupsArray[i].toObject();
//               QString id = obj.value("Id").toString();
//               QString name = obj.value("Name").toString();
//               resultMap.insert(id, name);
//           }
//       }
       // 解析 Parts 数组
       QJsonValue partsVal = rootObj.value("Parts");
       if (partsVal.isArray()) {
           QJsonArray partsArray = partsVal.toArray();
           for (int i = 0; i < partsArray.size(); ++i) {
               QJsonObject obj = partsArray[i].toObject();
               QString id = obj.value("Id").toString();
               QString name = obj.value("Name").toString();
               resultMap.insert(id, name);
           }
       }
       return resultMap;
}

