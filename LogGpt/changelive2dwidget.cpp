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

void ChangeLive2DWidget::refresh(const QString &path)
{
    if(path.size()<=3){
        return;
    }

    m_ValueExplainMap.clear();
    m_PartItemsMap.clear();
    m_DrawItemsMap.clear();
    m_ItemsCoverMap.clear();
    m_DrawsCovermap.clear();

    initValueExplainMap(path);
    initPartsItemMap(path);
    initDrawsItemMap(path);
    initPartsCoverMap(path);
    initDrawsCovermap(path);

    {

        QMap<QString,QVector<int>>::iterator it=m_PartItemsMap.begin();
        for(;it!=m_PartItemsMap.end();++it){

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
            if(m_ItemsCoverMap.contains(it.key())){
                widget->setValue(m_ItemsCoverMap[it.key()]);
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

    {

        QMap<QString,bool>::iterator it=m_DrawItemsMap.begin();
        for(;it!=m_DrawItemsMap.end();++it){

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

            if(m_DrawsCovermap.contains(it.key())){
                widget->setValue(m_DrawsCovermap[it.key()]);
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


     connect(ui->pushButton_save_parameter,&QPushButton::clicked,[=](){
         QString file_path = path+"/HARMONICCHANGELIST.txt";

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

void ChangeLive2DWidget::initPartsCoverMap(const QString &path)
{
    if(path.size()<=3){
        return;
    }
    QFile file(path+"/HARMONICCHANGELIST.txt");
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
        m_ItemsCoverMap[itemId]=itemvalue.toInt();

    }
    file.close();
}

void ChangeLive2DWidget::initDrawsCovermap(const QString &path)
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
        m_DrawsCovermap[itemId]=itemvalue.toInt()>0?true:false;

    }
    file.close();
}

void ChangeLive2DWidget::init()
{
    this->resize(_Width,_Height);
    this->setWindowTitle("模型修改");
    this->setWindowIcon(QIcon(":/res/u77.svg"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    ui->listWidget_parameter->setStyleSheet(
                "QScrollBar:vertical {width: 10px;background-color: #F5F5F5;margin: 0px 0px 0px 0px;border-radius: 5px;}"
                "QScrollBar::handle:vertical {background-color: #CCCCCC;min-height: 20px;border-radius: 5px;}"
                "QScrollBar::handle:vertical:hover {background-color: #BBBBBB;border-radius: 5px;}"
                "QScrollBar::add-line:vertical {height: 0px; subcontrol-position: bottom; subcontrol-origin: margin;}"
                "QScrollBar::sub-line:vertical {height: 0 px;subcontrol-position: top; subcontrol-origin: margin;}"
                "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background-color: #F5F5F5;border-radius: 5px;}"
                );
    ui->listWidget_drawing->setStyleSheet(
                "QScrollBar:vertical {width: 10px;background-color: #F5F5F5;margin: 0px 0px 0px 0px;border-radius: 5px;}"
                "QScrollBar::handle:vertical {background-color: #CCCCCC;min-height: 20px;border-radius: 5px;}"
                "QScrollBar::handle:vertical:hover {background-color: #BBBBBB;border-radius: 5px;}"
                "QScrollBar::add-line:vertical {height: 0px; subcontrol-position: bottom; subcontrol-origin: margin;}"
                "QScrollBar::sub-line:vertical {height: 0 px;subcontrol-position: top; subcontrol-origin: margin;}"
                "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background-color: #F5F5F5;border-radius: 5px;}"
                );


    QFile file(":/main.qss");
    if(file.open(QFile::ReadOnly)){
        QString styleSheet = QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
        file.close();
    }

}

void ChangeLive2DWidget::initPartsItemMap(const QString &path)
{
    QFile file(path+"/HARMONICLIST.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"Part Item File Open Fail!";
        return;
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString read_str = in.readAll();
    file.close();


    m_PartItemsMap.clear();

    // 按行拆分文件内容
    QStringList lines = read_str.split('\n', QString::SkipEmptyParts);
    // 创建一个 QMap 以存储键值对
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
                   m_PartItemsMap[name]=v;
               } else {
                   qDebug() << "String does not match the pattern.";
               }

    }

    return;

}

void ChangeLive2DWidget::initDrawsItemMap(const QString &path)
{
    QFile file(path+"/DRAWINGLIST.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"Part Item File Open Fail!";
        return;
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString read_str = in.readAll();
    file.close();

    m_DrawItemsMap.clear();

    // 按行拆分文件内容
    QStringList lines = read_str.split('\n', QString::SkipEmptyParts);
    // 创建一个 QMap 以存储键值对
    QMap<QString, QString> keyValueMap;

    for (const QString& line : lines) {

            // 使用正则表达式提取Name和浮点数
               QRegExp regex("\\[([^\\]]+)\\]:\\[(-?\\d+)\\];");
               int pos = regex.indexIn(line);
               if (pos != -1) {
                   QString name = regex.cap(1);
                   int num = regex.cap(2).toInt();
                   m_DrawItemsMap[name]=num>0?true:false;
               } else {
                   qDebug() << "String does not match the pattern.";
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
        qDebug()<<"Part Item File Open Fail!";
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
        if(index==-1){
            break;
        }
        index=index+nameStr.size()+1;
        endIndex=index;
        endIndex=json_str.indexOf("\"",index);

        QString nameText=json_str.mid(index,endIndex-index);

        m_ValueExplainMap[idText]=nameText;

    }


}

