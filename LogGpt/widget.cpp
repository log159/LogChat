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

    m_PushAndReceiveWidget=new PushAndReceiveWidget(this);
    m_PushAndReceiveWidget->move(0,0);
    m_PushAndReceiveWidget->show();

    m_SetSelectWidget=new SetSelectWidget(this);
    m_SetSelectWidget->move(-m_SetSelectWidget->width(),0);
    m_SetSelectWidget->show();

    //与live2D通信的类
    m_NetLive2D=new NetLive2D(this);
    m_NetLive2D->startListen();


    m_PushAndReceiveWidget->setFocus();


}

void Widget::initConnect()
{
    //窗口事件连接
    connect(m_PushAndReceiveWidget,&PushAndReceiveWidget::setPass,[=](){
        m_SetSelectWidget->zoom();
    });
    SendAudio sendAudio=&PushAndReceiveWidget::sendAudio;
    connect(m_PushAndReceiveWidget,sendAudio,[=](QString audioPath){
        QString handleStr="Audio:"+audioPath+";";
        m_NetLive2D->sendHandle(handleStr);
    });

    connect(m_SetSelectWidget,&SetSelectWidget::setWidgetShow,[=](){
        SetDialogWidget dialog;
        dialog.exec();

    });
    connect(m_SetSelectWidget,&SetSelectWidget::setConfigShow,[=](){
        SetConfigDialogWidget dialog;
        dialog.exec();

    });
    connect(m_SetSelectWidget,&SetSelectWidget::setLive2DShow,[=](){

        SetLive2DDialogWidget dialog;
        SendModelHandle sendModelHandle=&SetLive2DDialogWidget::sendModelHandle;
        connect(&dialog,sendModelHandle,[=](QString modelHadle){
            this->m_NetLive2D->sendHandle(modelHadle);

        });
        dialog.exec();
    });
    /*点击Gal视窗按钮*/
    connect(m_SetSelectWidget,&SetSelectWidget::setGalDialogShow,[=](){

        new_GalDialog.reset(new GalDialog);
        /*发送句柄事件，通知unity，galdialog有更高的优先级*/
        m_NetLive2D->sendHandle("Hwnd:dialog,"+QString::number(static_cast<int>(new_GalDialog.get()->winId()))+";");

        /*移动窗口到对应位置，如果未启用模型默认为屏幕中心*/
        new_GalDialog->move(int(ConfigLive2d::getModelX()-new_GalDialog->width()/2.f),int(ConfigLive2d::getModelY()-new_GalDialog->height()/2.f));
        new_GalDialog->show();
        //Gal视口发送信息传递过来
        connect(new_GalDialog.get(), SIGNAL(signal_send_data_from_gal_to_widget(QString)), this, SLOT(slot_receive_data_from_gal_to_widget(QString)));
        connect(new_GalDialog.get(), SIGNAL(signal_show_widget_from_gal()), this, SLOT(slot_show_widget_from_gal()));
        connect(new_GalDialog.get(), SIGNAL(signal_play_voice_from_gal_to_widget()), this, SLOT(slot_play_voice_from_gal()));
        connect(new_GalDialog.get(),&GalDialog::signal_delete,[=](){
            new_GalDialog.reset(nullptr);
        });
    });
    connect(m_SetSelectWidget,&SetSelectWidget::clearChat,[=](){
        m_PushAndReceiveWidget->clearHistory();
        m_PushAndReceiveWidget->clearUi();
    });

    connect(m_SetSelectWidget,&SetSelectWidget::setAboutShow,[=](){
        AboutSoftwareDialogWidget dialog;
        dialog.exec();
    });
    connect(m_PushAndReceiveWidget,&PushAndReceiveWidget::sendIs,[=](){
        m_SetSelectWidget->setNoPass();
    });
    connect(m_PushAndReceiveWidget,&PushAndReceiveWidget::receiveIs,[=](){
        m_SetSelectWidget->setCanPass();
    });

    connect(m_NetLive2D,&NetLive2D::myMousePass,this,[=](){
        emit m_SetSelectWidget->setGalDialogShow();

    });

    connect(m_SetSelectWidget,&SetSelectWidget::setCompoundShow,[=](){
        SetCompoundDialogWidget* compoundDialogWidget=new SetCompoundDialogWidget;
        compoundDialogWidget->show();

    });

    connect(m_PushAndReceiveWidget, SIGNAL(signals_send_data_from_llm_to_main(QString)), this, SLOT(slot_receive_data_from_llm_to_widget(QString))); //llm返回回复到widget

}

void Widget::updateOtherWidgetSize()
{
    m_SetSelectWidget->setAdapt();

    //为保证显示不出问题，有必要刷新至少两次
    m_PushAndReceiveWidget->setAdapt();
    m_PushAndReceiveWidget->setAdapt();

}

void Widget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    ConfigWindow::setStaticPosX(this->geometry().topLeft().x());
    ConfigWindow::setStaticPosY(this->geometry().topLeft().y());
    ConfigWindow::setStaticWidth(this->width());
    ConfigWindow::setStaticHeight(this->height());

    updateOtherWidgetSize();
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    QBrush brush;
    brush.setColor(QColor(255, 255, 255, 0));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0,0,this->width(),this->height());
}


void Widget::enterEvent(QEvent *)
{
    emit mouseChange(Qt::ArrowCursor);
}

void Widget::leaveEvent(QEvent *)
{

}

/*信息通过主界面传递*/
//接收到Gal界面信息
void Widget::slot_receive_data_from_gal_to_widget(QString data)
{
    qDebug()<<"Widget接受到来自Gal视窗信息————>"<<data; //获取传递过来的数据
    m_PushAndReceiveWidget->slot_receive_data_from_widget_to_llm(data);
}
//接受到llm信息
void Widget::slot_receive_data_from_llm_to_widget(QString data)
{
    qDebug()<<"Widget接受到来自llm信息————>"<<data; //获取传递过来的数据
    if(new_GalDialog.get()==nullptr){return;}

    new_GalDialog.get()->slots_receive_data_from_widget_to_gal(data);
}
//接受到gal要求显示histroy信息
void Widget::slot_show_widget_from_gal()
{
    this->showNormal();

    //刷新子窗口
    this->updateOtherWidgetSize();
}
//接受到gal要求播放语言信息
void Widget::slot_play_voice_from_gal()
{
    qDebug()<<"Widget接受到来自gal播放语言请求";
    m_PushAndReceiveWidget->slot_play_voice_from_widget_to_llm();
}
