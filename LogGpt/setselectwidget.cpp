#include "setselectwidget.h"
#include "ui_setselectwidget.h"

SetSelectWidget::SetSelectWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetSelectWidget)
{
    ui->setupUi(this);
    init();
    initConnect();
}

SetSelectWidget::~SetSelectWidget()
{
    delete ui;
}
void SetSelectWidget::init()
{
    this->setFixedSize(_Width,ConfigWindow::getStaticHeight());

    m_ListWidget=new QListWidget(this);
    m_ListWidget->setStyleSheet(

                "QScrollBar:vertical {width: 10px;background-color: #F5F5F5;margin: 0px 0px 0px 0px;border-radius: 5px;}"
                "QScrollBar::handle:vertical {background-color: #CCCCCC;min-height: 20px;border-radius: 5px;}"
                "QScrollBar::handle:vertical:hover {background-color: #BBBBBB;border-radius: 5px;}"
                "QScrollBar::add-line:vertical {height: 0px; subcontrol-position: bottom; subcontrol-origin: margin;}"
                "QScrollBar::sub-line:vertical {height: 0 px;subcontrol-position: top; subcontrol-origin: margin;}"
                "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background-color: #F5F5F5;border-radius: 5px;}"
                "QListWidget { background-color: transparent; }"
                );

    m_ListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);       //禁止水平滚动条显示
    m_ListWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);   //平滑效果
    m_ListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);       //禁用水平滑动条
    m_ListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);         //禁止编辑
    m_ListWidget->setSelectionMode(QAbstractItemView::NoSelection);           //禁止选中
    m_ListWidget->setFixedSize(this->size());
    m_ListWidget->move(0,0);

    m_PushButtonSet=new SetPushButton();
    m_PushButtonSet->setText("基本设置");
    m_ButtonVector.push_back(m_PushButtonSet);

    m_PushButtonConfig=new SetPushButton();
    m_PushButtonConfig->setText("聊天设置");
    m_ButtonVector.push_back(m_PushButtonConfig);

    m_PushButtonClear=new SetPushButton();
    m_PushButtonClear->setText("清除聊天");
    m_ButtonVector.push_back(m_PushButtonClear);

    m_PushButtonLive2D=new SetPushButton();
    m_PushButtonLive2D->setText("Live2D");
    m_ButtonVector.push_back(m_PushButtonLive2D);

    m_PushButtonAbout=new SetPushButton();
    m_PushButtonAbout->setText("关于");
    m_ButtonVector.push_back(m_PushButtonAbout);

    SendButtonHandle sendButtonNormal=&SetPushButton::sendButtonNormal;
    SendButtonHandle sendButtonEnter=&SetPushButton::sendButtonEnter;
    for(int i=0;i<m_ButtonVector.size();++i)
    {
        m_ButtonVector.at(i)->setFixedSize(this->width()-3,_ButtonHeight);
        QListWidgetItem *item = new QListWidgetItem();
        m_ListWidget->addItem(item);
        item->setSizeHint(m_ButtonVector.at(i)->size());
        m_ListWidget->setItemWidget(item,m_ButtonVector.at(i));

        connect(m_ButtonVector.at(i),sendButtonEnter,this,[=](){
            m_ButtonId=i;
            update();
        });
        connect(m_ButtonVector.at(i),sendButtonNormal,this,[=](){
            m_ButtonId=-1;
            update();
        });

    }

}

void SetSelectWidget::setAdapt()
{
    this->setFixedSize(this->width(),ConfigWindow::getStaticHeight()-50);
    m_ListWidget->setFixedSize(this->size());
}
void SetSelectWidget::initConnect()
{
    connect(m_PushButtonSet,&QPushButton::clicked,[=](){
        qDebug()<<"基本设置界面展示";
        emit setWidgetShow();
    });
    connect(m_PushButtonConfig,&QPushButton::clicked,[=](){
        qDebug()<<"聊天设置界面展示";
        emit setConfigShow();
    });
    connect(m_PushButtonClear,&QPushButton::clicked,[=](){
        qDebug()<<"清除聊天";
        emit clearChat();
    });
    connect(m_PushButtonLive2D,&QPushButton::clicked,[=](){
        qDebug()<<"Live2D设置界面展示";
        emit setLive2DShow();
    });
    connect(m_PushButtonAbout,&QPushButton::clicked,[=](){
        qDebug()<<"关于界面展示";
        emit setAboutShow();
    });
}
void SetSelectWidget::zoom()
{
    if(m_ZoomId==false)
    {
        zoom1();
    }
    else {
        zoom2();
    }
    m_ZoomId=!m_ZoomId;
}
void SetSelectWidget::zoom1()
{
    //创建动画对象
    QPropertyAnimation * animation=new QPropertyAnimation(this,"geometry");
    //动画间隔
    animation->setDuration(200);
    //开始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x()+100,this->y(),this->width(),this->height()));
    //设置动画曲线
    animation->setEasingCurve(QEasingCurve::Linear);
    //执行后销毁
    animation->start(QAbstractAnimation::DeleteWhenStopped);

}

void SetSelectWidget::zoom2()
{
    //创建动画对象
    QPropertyAnimation * animation=new QPropertyAnimation(this,"geometry");
    //动画间隔
    animation->setDuration(200);
    //开始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x()-100,this->y(),this->width(),this->height()));
    //设置动画曲线
    animation->setEasingCurve(QEasingCurve::Linear);
    //执行
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void SetSelectWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)


    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    QBrush brush(Qt::SolidPattern);
    brush.setColor(Qt::white);
    painter.setBrush(brush);
    painter.drawRect(0,0,this->width(),this->height());
    brush.setColor(QColor("#388E3C"));
    if(m_ButtonId<0){
        return;
    }
    painter.setBrush(brush);
    painter.drawRect(0,m_ButtonId*_ButtonHeight,this->width(),_ButtonHeight);
}

void SetSelectWidget::setNoPass()
{
    for(auto& val:m_ButtonVector){
        val->setEnabled(false);
    }
}

void SetSelectWidget::setCanPass()
{
    for(auto& val:m_ButtonVector){
        val->setEnabled(true);
    }
}
