#include "live2dlistitemswidget.h"
#include "ui_live2dlistitemswidget.h"

Live2DListItemsWidget::Live2DListItemsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Live2DListItemsWidget)
{
    ui->setupUi(this);
}

void Live2DListItemsWidget::init(const ModelConfigItem& modItem)
{
    this->resize(_Width,_Height);

    this->seModelItem(modItem);
//    QString pathStr=modItem.get;
//    int wayCharPos=0;
//    for(int i=0;i<pathStr.size();++i){
//        if(pathStr.at(i)==QChar('\\')||pathStr.at(i)==QChar('/')){
//            wayCharPos=i;
//        }
//    }
//    for (int i=wayCharPos+1;i<pathStr.size();++i) {
//        if(pathStr.at(i)==QChar('.')){
//            break;
//        }
//        m_ModelName+=pathStr.at(i);
//    }
    ui->label->setText(modItem.getModelName());
}

Live2DListItemsWidget::~Live2DListItemsWidget()
{
    delete ui;
}

void Live2DListItemsWidget::mousePressEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton)
    {
        qDebug() << "Pass Live2D ListItem Name："<<m_ModelConfigItem.getModelName();
        sendPass(m_ModelConfigItem);
    }
    else
    {
        QWidget::mousePressEvent(event);
    }

}

