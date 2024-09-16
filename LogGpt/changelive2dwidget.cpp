#include "changelive2dwidget.h"
#include "ui_changelive2dwidget.h"

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
    setWindowFlags((windowFlags() & ~Qt::WindowContextHelpButtonHint) | Qt::WindowStaysOnTopHint);

    QVector<QListWidget*> wlsList;
    wlsList.push_back(ui->listWidget_parameter);
    wlsList.push_back(ui->listWidget_drawable);
    wlsList.push_back(ui->listWidget_harmonic);

    for(auto& val:wlsList){
        val->setEditTriggers(QAbstractItemView::NoEditTriggers);         //禁止编辑
        val->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);       //禁用水平滑动条
        val->setSelectionMode(QAbstractItemView::NoSelection);           //禁止选中
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
    if(path.size()<=3){
        return;
    }

    this->m_FilePath=path;
    initValueExplainMap();
    initParameterItemsMap();
    initPartItemsMap();
    initDrawableItemsMap();
    initParameterCoverMap();
    initPartCovermap();
    initDrawableCovermap();
//    initHarmCoverMap(path);



    initUiParameterList();
    initUiPartList();
    initUiDrawableList();

    initUiConnectParameterList();
    initUiConnectPartList();
    initUiConnectDrawableList();


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
    QString file_path=this->m_FilePath+"/"+ConfigFileName;
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
    QString file_path=this->m_FilePath+"/"+ConfigFileName;
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
    QString file_path=this->m_FilePath+"/"+ConfigFileName;
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
            emit sendhandle(handleStr);
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
            emit sendhandle(handleStr);
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
            emit sendhandle(handleStr);
        });

    }
    ui->listWidget_drawable->scrollToTop();
}

void ChangeLive2DWidget::initUiConnectParameterList()
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
        Config::set_OTHER_BASE(this->m_FilePath+"/"+ConfigFileName,::ItemM[::EnItem::PARAMETERCHANGELIST],changeM);
    });

    connect(ui->pushButton_reset_parameter,&QPushButton::clicked,[=](){
        for(int i=0;i<ui->listWidget_parameter->count();++i){
            QListWidgetItem* listWidgetItem=ui->listWidget_parameter->item(i);
            (static_cast<Live2DParamItemsWidget*>(ui->listWidget_parameter->itemWidget(listWidgetItem)))->resetValue();
        }
        emit sendhandle("InitItems:parameters;");
    });
}

void ChangeLive2DWidget::initUiConnectPartList()
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
        Config::set_OTHER_BASE(this->m_FilePath+"/"+ConfigFileName,::ItemM[::EnItem::PARTCHANGELIST],changeM);
    });

    connect(ui->pushButton_reset_part,&QPushButton::clicked,[=](){
        for(int i=0;i<ui->listWidget_part->count();++i){
            QListWidgetItem* listWidgetItem=ui->listWidget_part->item(i);
            (static_cast<Live2DPartItemsWidget*>(ui->listWidget_part->itemWidget(listWidgetItem)))->resetValue();
        }
        emit sendhandle("InitItems:parts;");
    });
}

void ChangeLive2DWidget::initUiConnectDrawableList()
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
        Config::set_OTHER_BASE(this->m_FilePath+"/"+ConfigFileName,::ItemM[::EnItem::DRAWABLECHANGELIST],changeM);
    });

    connect(ui->pushButton_reset_drawable,&QPushButton::clicked,[=](){

        for(int i=0;i<ui->listWidget_drawable->count();++i){
            QListWidgetItem* listWidgetItem=ui->listWidget_drawable->item(i);
            (static_cast<Live2DDrawItemsWidget*>(ui->listWidget_drawable->itemWidget(listWidgetItem)))->resetValue();

        }
        emit sendhandle("InitItems:drawables;");
    });
}



void ChangeLive2DWidget::initParameterItemsMap()
{
    m_ParameterItemsMap.clear();
    QString file_path=this->m_FilePath+"/"+ConfigFileName;
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
    QString file_path=this->m_FilePath+"/"+ConfigFileName;
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
    QString file_path=this->m_FilePath+"/"+ConfigFileName;
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

