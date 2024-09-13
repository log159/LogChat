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
    wlsList.push_back(ui->listWidget_drawing);
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

    initValueExplainMap(path);
    initParameterItemsMap(path);
    initDrawableItemsMap(path);
//    initParameterCoverMap(path);
//    initDrawCovermap(path);
//    initHarmCoverMap(path);



    //控件偏移
    {

        QMap<QString,QVector<int>>::iterator it=m_ParameterItemsMap.begin();
        for(;it!=m_ParameterItemsMap.end();++it){

            //控件添加
            QListWidgetItem* item = new QListWidgetItem();
            Live2DPartItemsWidget* widget=new Live2DPartItemsWidget;
            ModelPartItem modelPartItem;
            modelPartItem.setName(it.key());
            modelPartItem.setDefaultValue(it.value().at(0)*100);
            modelPartItem.setMinValue(it.value().at(1)*100);
            modelPartItem.setMaxValue(it.value().at(2)*100);

//            qDebug()<<modelPartItem.getName();
            widget->init(modelPartItem);
            widget->resize(ui->listWidget_parameter->size().width(),widget->height());
            ui->listWidget_parameter->addItem(item);
            item->setSizeHint(widget->size());
            ui->listWidget_parameter->setItemWidget(item,widget);
            ui->listWidget_parameter->scrollToBottom();
            if(m_ValueExplainMap[it.key()]!=""){
                widget->setExplain(m_ValueExplainMap[it.key()]);
            }
            if(m_ParameterCoverMap.contains(it.key())){
                widget->setValue(m_ParameterCoverMap[it.key()]);
            }

            SendPassByPart sendPass=&Live2DPartItemsWidget::sendPass;
            connect(widget,sendPass,[=](ModelPartItem passItem){
                qDebug()<<"chagngelive2dwidget: "<<passItem.getName();

            });

            connect(widget,&Live2DPartItemsWidget::sendHandle,[=](QString handleStr){
                emit sendhandle(handleStr);
            });

        }
        ui->listWidget_parameter->scrollToTop();
    }

    //控件渲染
    {

        QMap<QString,bool>::iterator it=m_DrawableItemsMap.begin();
        for(;it!=m_DrawableItemsMap.end();++it){

            //控件添加
            QListWidgetItem* item = new QListWidgetItem();
            Live2DDrawItemsWidget* widget=new Live2DDrawItemsWidget;
            ModelPartItem modelPartItem;
            modelPartItem.setName(it.key());
            modelPartItem.setDefaultValue(int(it.value()));
            modelPartItem.setMinValue(0);
            modelPartItem.setMaxValue(1);

            widget->init(modelPartItem);
            widget->resize(ui->listWidget_drawing->size().width(),widget->height());
            ui->listWidget_drawing->addItem(item);
            item->setSizeHint(widget->size());
            ui->listWidget_drawing->setItemWidget(item,widget);
            ui->listWidget_drawing->scrollToBottom();

            if(m_DrawableCoverMap.contains(it.key())){
                widget->setValue(m_DrawableCoverMap[it.key()]);
            }

            SendPassByDraw sendPass=&Live2DDrawItemsWidget::sendPass;
            connect(widget,sendPass,[=](ModelPartItem passItem){
                qDebug()<<"chagngelive2dwidget: "<<passItem.getName();

            });

            connect(widget,&Live2DDrawItemsWidget::sendHandle,[=](QString handleStr){
                emit sendhandle(handleStr);
            });

        }
        ui->listWidget_drawing->scrollToTop();

    }

    //控件谐波

    {
//        ui->listWidget_harmonic->set
        QMap<QString,QVector<int>>::iterator it=m_ParameterItemsMap.begin();
            for(;it!=m_ParameterItemsMap.end();++it){

    //            //控件添加
                QListWidgetItem* item = new QListWidgetItem();
                Live2DAnimationItemsWidget* widget=new Live2DAnimationItemsWidget;

                widget->resize(ui->listWidget_harmonic->size().width(),widget->height());
                ui->listWidget_harmonic->addItem(item);
                item->setSizeHint(widget->size());
                ui->listWidget_harmonic->setItemWidget(item,widget);
                ui->listWidget_harmonic->scrollToBottom();

                widget->setName(it.key());

                if(m_ValueExplainMap[it.key()]!=""){
                    widget->setExplain(m_ValueExplainMap[it.key()]);
                }
                QVector<int>v=m_HarmCoverMap[it.key()];
                if(v.size()>=3){
                    widget->setRule(v[0]);
                    widget->setSpeed(v[1]);
                    widget->setUseful(v[2]!=0?true:false);

                }

    //            SendPassByPart sendPass=&Live2DPartItemsWidget::sendPass;
    //            connect(widget,sendPass,[=](ModelPartItem passItem){
    //                qDebug()<<"chagngelive2dwidget: "<<passItem.getName();

    //            });

    //            connect(widget,&Live2DPartItemsWidget::sendHandle,[=](QString handleStr){
    //                emit sendhandle(handleStr);
    //            });

    //        }
            ui->listWidget_harmonic->scrollToTop();
        }
    }


     connect(ui->pushButton_save_parameter,&QPushButton::clicked,[=](){
         QString file_path = path+"/PARAMETERCHANGELIST.txt";

         // 创建文件并写入内容
         QFile file(file_path);
         QString out_str="";
         if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
             QTextStream out(&file);

             for(int i=0;i<ui->listWidget_parameter->count();++i){
                 QListWidgetItem* listWidgetItem=ui->listWidget_parameter->item(i);
                 Live2DPartItemsWidget* live2DPartItemsWidget= (static_cast<Live2DPartItemsWidget*>(ui->listWidget_parameter->itemWidget(listWidgetItem)));
                 bool is_default=live2DPartItemsWidget->isDefault();
                 QString item_name=live2DPartItemsWidget->getName();
                 int item_value=live2DPartItemsWidget->getValue();

                 if(is_default==false){
                     out_str+=QString("[%1]:[%2];\n").arg(item_name).arg(QString::number(item_value));
                 }

             }
             out<<out_str;
             file.close();
         }
     });

     connect(ui->pushButton_reset_parameter,&QPushButton::clicked,[=](){

         for(int i=0;i<ui->listWidget_parameter->count();++i){
             QListWidgetItem* listWidgetItem=ui->listWidget_parameter->item(i);
             (static_cast<Live2DPartItemsWidget*>(ui->listWidget_parameter->itemWidget(listWidgetItem)))->resetValue();

         }

         emit sendhandle("InitItems:default;");
     });


     connect(ui->pushButton_save_drawing,&QPushButton::clicked,[=](){


         QString file_path = path+"/DRAWINGCHANGELIST.txt";

         // 创建文件并写入内容
         QFile file(file_path);
         QString out_str="";
         if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
             QTextStream out(&file);

             for(int i=0;i<ui->listWidget_drawing->count();++i){
                 QListWidgetItem* listWidgetItem=ui->listWidget_drawing->item(i);
                 Live2DDrawItemsWidget* live2DDrawItemsWidget= (static_cast<Live2DDrawItemsWidget*>(ui->listWidget_drawing->itemWidget(listWidgetItem)));
                 bool is_default=live2DDrawItemsWidget->isDefault();
                 QString item_name=live2DDrawItemsWidget->getName();
                 int item_value=live2DDrawItemsWidget->getValue();

                 if(is_default==false){
                     out_str+=QString("[%1]:[%2];\n").arg(item_name).arg(QString::number(item_value));
                 }

             }
             out<<out_str;
             file.close();
         }

     });

     connect(ui->pushButton_reset_drawing,&QPushButton::clicked,[=](){

         for(int i=0;i<ui->listWidget_drawing->count();++i){
             QListWidgetItem* listWidgetItem=ui->listWidget_drawing->item(i);
             (static_cast<Live2DDrawItemsWidget*>(ui->listWidget_drawing->itemWidget(listWidgetItem)))->resetValue();

         }

         emit sendhandle("InitItems:active;");
     });


}

void ChangeLive2DWidget::initParameterCoverMap(const QString &path)
{
    QString file_path(path+"/"+ConfigFileName);
    QString read_str = ConfigFileIO::getOtherConfig(file_path,"INITLIST",ItemM[PARAMETERCHANGELIST]);
    QStringList lines = read_str.split('\n', QString::SkipEmptyParts);
    for (const QString& line : lines) {
        QString read_line = line;
        int index = read_line.indexOf(":");
        if (index == -1||read_line.indexOf("]")==-1||read_line.indexOf("[")==-1)
            break;
        QString itemId=read_line.mid(1, index-2);
        QString itemvalue = read_line.mid(index + 2, read_line.size() - index - 4);
        m_ParameterCoverMap[itemId]=itemvalue.toInt();
    }
}

void ChangeLive2DWidget::initDrawableCovermap(const QString &path)
{
    if(path.size()<=3){
        return;
    }
    QFile file(path+"/DRAWINGCHANGELIST.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"Part Item File Open Fail!";
        return;
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");

    while (in.atEnd()==false){
        QString read_str = in.readLine();

        int index = read_str.indexOf(":");
        if (index == -1||read_str.indexOf("]")==-1||read_str.indexOf("[")==-1)
        {
            break;
        }

        QString itemId=read_str.mid(1, index-2);
        QString itemvalue = read_str.mid(index + 2, read_str.size() - index - 4);
        m_DrawableCoverMap[itemId]=itemvalue.toInt()>0?true:false;

    }
    file.close();
}

void ChangeLive2DWidget::initHarmCoverMap(const QString &path)
{
    QFile file(path+"/HARMONICCHANGELIST.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"Part Item File Open Fail!";
        return;
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString read_str = in.readAll();
    file.close();


    m_HarmCoverMap.clear();

    QStringList lines = read_str.split('\n', QString::SkipEmptyParts);
    QMap<QString, QString> keyValueMap;

    for (const QString& line : lines) {

            // 使用正则表达式提取Name和三个浮点数
               QRegExp regex("\\[([^\\]]+)\\]:\\[(-?\\d+),(-?\\d+),(-?\\d+)\\];");
               int pos = regex.indexIn(line);
               if (pos != -1) {
                   QString name = regex.cap(1);
                   int num1 = regex.cap(2).toInt();
                   int num2 = regex.cap(3).toInt();
                   int num3 = regex.cap(4).toInt();
                   QVector<int> v={0,0,0};
                   v[0]=num1;v[1]=num2;v[2]=num3;
                   m_HarmCoverMap[name]=v;
               } else {
                   qDebug() << "String does not match the pattern.";
               }

    }

    return;
}



void ChangeLive2DWidget::initParameterItemsMap(const QString &path)
{
    m_ParameterItemsMap.clear();
    QString file_path=path+"/"+ConfigFileName;
    QMap<QString,QString> read_map = ConfigFileIO::getOtherBaseAllConfig(file_path,ItemM[PARAMETERLIST]);
    if(read_map.isEmpty())
        return;

    QRegExp re("(-?\\d+),(-?\\d+),(-?\\d+)");
    for (QMap<QString,QString>::iterator it=read_map.begin();it!=read_map.end();++it) {
        if (re.indexIn(it.value()) != -1) {
            int num1 = re.cap(1).toInt();
            int num2 = re.cap(2).toInt();
            int num3 = re.cap(3).toInt();
            QVector<int> v={0,0,0};
            v[0]=num1;v[1]=num2;v[2]=num3;
            m_ParameterItemsMap[it.key()]=v;
        }
    }
    return;

}

void ChangeLive2DWidget::initDrawableItemsMap(const QString &path)
{
    m_DrawableItemsMap.clear();
    QString file_path=path+"/"+ConfigFileName;
    QMap<QString,QString> read_map = ConfigFileIO::getOtherBaseAllConfig(file_path,ItemM[DRAWABLELIST]);
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


void ChangeLive2DWidget::initValueExplainMap(const QString &path)
{
    QDir directory(path); // 替换为你的目录路径
    QStringList filter;
    filter << "*.cdi3.json"; // 筛选条件，只保留以 .cdi3.json 结尾的文件
    directory.setNameFilters(filter);

    QStringList files = directory.entryList(QDir::Files | QDir::Readable);
    if(files.size()<=0){
        qDebug()<<"无.cdi3.json文件";
        return;
    }

    QFile file(path+"/"+files[0]);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<__FUNCTION__<<"File Open Fail!";
        return;
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString read_str = in.readAll();
    file.close();
    QString json_str=read_str;
    QString idStr="\"Id\":";
    QString nameStr="\"Name\":";
    json_str=json_str.replace("\n", "");
    json_str=json_str.replace("\t","");
    json_str=json_str.replace(" ","");
    int index=0;
    while(index!=-1) {
        index=json_str.indexOf(idStr,index);
        if(index==-1){break;}
        index=index+idStr.size()+1;
        int endIndex=index;
        endIndex=json_str.indexOf("\"",index);
        QString idText=json_str.mid(index,endIndex-index);
        index=json_str.indexOf(nameStr,index);
        if(index==-1)break;
        index=index+nameStr.size()+1;
        endIndex=index;
        endIndex=json_str.indexOf("\"",index);
        QString nameText=json_str.mid(index,endIndex-index);
        m_ValueExplainMap[idText]=nameText;
    }
}

