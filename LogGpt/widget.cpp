#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    init();
    initConnect();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::init()
{
    this->setWindowTitle(_WindowTitle);
    this->setWindowIcon(QIcon(":/res/u77.svg"));
    this->resize(ConfigWindow::getStaticWidth(),ConfigWindow::getStaticHeight());
    this->move(ConfigWindow::getStaticPosX(),ConfigWindow::getStaticPosY());

    m_PushAndReceiveWidget=new PushAndReceiveWidget(this);
    m_PushAndReceiveWidget->move(0,0);
    m_PushAndReceiveWidget->show();

    m_SetSelectWidget=new SetSelectWidget(this);
    m_SetSelectWidget->move(-m_SetSelectWidget->width(),0);
    m_SetSelectWidget->show();

    m_SetSelectPushButton=new SetSelectPushButton(this);
    m_SetSelectPushButton->move(0,this->height()-80);
    m_SetSelectPushButton->show();
    connect(m_SetSelectPushButton,&SetSelectPushButton::clicked,[=](){
        m_SetSelectPushButton->zoom();
        m_SetSelectWidget->zoom();
    });

    m_PushAndReceiveWidget->setFocus();
}

void Widget::initConnect()
{
    connect(m_SetSelectWidget,&SetSelectWidget::setWidgetShow,[=](){
        SetDialogWidget dialog;
        dialog.exec();
        m_PushAndReceiveWidget->clearHistory();

    });
    connect(m_SetSelectWidget,&SetSelectWidget::setConfigShow,[=](){
        SetConfigDialogWidget dialog;
        dialog.exec();
        m_PushAndReceiveWidget->clearHistory();

    });
    connect(m_SetSelectWidget,&SetSelectWidget::clearChat,[=](){
        m_PushAndReceiveWidget->clearHistory();
    });

    connect(m_PushAndReceiveWidget,&PushAndReceiveWidget::sendIs,[=](){
        m_SetSelectWidget->setNoPass();
    });
    connect(m_PushAndReceiveWidget,&PushAndReceiveWidget::receiveIs,[=](){
        m_SetSelectWidget->setCanPass();
    });
}

void Widget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    ConfigWindow::setStaticPosX(this->geometry().topLeft().x());
    ConfigWindow::setStaticPosY(this->geometry().topLeft().y());
    ConfigWindow::setStaticWidth(this->width());
    ConfigWindow::setStaticHeight(this->height());

//    qDebug()<<rect.width()<<"  "<<rect.height();
    m_PushAndReceiveWidget->setAdapt();
    m_SetSelectWidget->setAdapt();
    m_SetSelectPushButton->move(m_SetSelectPushButton->x(),int(ConfigWindow::getStaticHeight()*0.867)-m_SetSelectPushButton->height());
}




