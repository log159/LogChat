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

    ConfigWindow::_WindowPointer=this;
    this->setWindowTitle(ConfigWindow::_WindowTitle);
    this->setWindowIcon(QIcon(":/res/u77.svg"));
    this->setMinimumSize(ConfigWindow::_StaticMinWidth,ConfigWindow::_StaticMinHeight);
    this->resize(ConfigWindow::getStaticWidth(),ConfigWindow::getStaticHeight());
    this->move(ConfigWindow::getStaticPosX(),ConfigWindow::getStaticPosY());

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

    //最小化到托盘
    m_Tray= new QSystemTrayIcon(this);                //初始化托盘对象tray
    m_Tray->setIcon(QIcon(QPixmap(":/res/u77.svg"))); //设定托盘图标，引号内是自定义的png图片路径
    m_Tray->setToolTip(ConfigWindow::_WindowTitle);   //提示文字
    m_Tray->show();                                   //让托盘图标显示在系统托盘上

    //创建菜单项动作
    m_MinimizeAction = new QAction("MinWin", this);
    m_MaximizeAction = new QAction("MaxWin", this);
    m_RestoreAction = new QAction("Restore", this);
    m_QuitAction = new QAction("Exit", this);


    //创建托盘菜单
    m_TrayMenu = new QMenu(this);
    m_TrayMenu->addAction(m_MinimizeAction);
    m_TrayMenu->addAction(m_MaximizeAction);
    m_TrayMenu->addAction(m_RestoreAction);
    m_TrayMenu->addSeparator();
    m_TrayMenu->addAction(m_QuitAction);
    m_Tray->setContextMenu(m_TrayMenu);


}

void Widget::initConnect()
{
    //窗口事件连接
    connect(m_PushAndReceiveWidget,&PushAndReceiveWidget::setPass,[=](){
        m_SetSelectWidget->zoom();
    });
    SendAudio sendAudio=&PushAndReceiveWidget::sendAudio;
    connect(m_PushAndReceiveWidget,sendAudio,[=](QString audioPath){
        QString handleStr="Audio:"+audioPath;
        m_NetLive2D->sendHandle(handleStr);
    });

    connect(m_SetSelectWidget,&SetSelectWidget::setWidgetShow,[=](){
        SetDialogWidget dialog;
        dialog.exec();
        Config::set_ALLSETCONFIG();
        m_PushAndReceiveWidget->clearHistory();

    });
    connect(m_SetSelectWidget,&SetSelectWidget::setConfigShow,[=](){
        SetConfigDialogWidget dialog;
        dialog.exec();
        m_PushAndReceiveWidget->clearHistory();

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

        /*移动窗口到对应位置，如果未启用模型默认为屏幕中心*/
        new_GalDialog->move(int(ConfigLive2d::getModelX()-new_GalDialog->width()/2.f),int(ConfigLive2d::getModelY()-new_GalDialog->height()/2.f));
        new_GalDialog->show();
        //Gal视口发送信息传递过来
        connect(new_GalDialog.get(), SIGNAL(signal_send_data_from_gal_to_widget(QString)), this, SLOT(slot_receive_data_from_gal_to_widget(QString)));
        connect(new_GalDialog.get(), SIGNAL(signal_show_widget_from_gal()), this, SLOT(slot_show_widget_from_gal()));
        connect(new_GalDialog.get(), SIGNAL(signal_play_voice_from_gal_to_widget()), this, SLOT(slot_play_voice_from_gal()));
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


    //最小化到托盘的菜单事件连接
    connect(m_MinimizeAction, SIGNAL(triggered()), this, SLOT(hide()));
    connect(m_MaximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));
    connect(m_RestoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));
    connect(m_RestoreAction,&QAction::triggered,this,[=](){
        //设置窗口置顶
        ::SetWindowPos(HWND(this->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
        //设置窗口置顶取消
        ::SetWindowPos(HWND(this->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

        updateOtherWidgetSize();

    });
    connect(m_QuitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    connect(m_Tray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(icon_activated(QSystemTrayIcon::ActivationReason)));

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

void Widget::icon_activated(QSystemTrayIcon::ActivationReason ireason)
{

    switch (ireason)
    {
    case QSystemTrayIcon::Trigger:
        this->showNormal();
        break;
    case QSystemTrayIcon::DoubleClick:
        this->showNormal();
        break;
    case QSystemTrayIcon::MiddleClick:
        break;
    default:
        break;
    }
    ::SetWindowPos(HWND(this->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    // 然后立即调用以下函数使其不保持置顶
    ::SetWindowPos(HWND(this->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    updateOtherWidgetSize();
}


void Widget::closeEvent(QCloseEvent *event)
{
    if(m_Tray->isVisible())
    {
        hide(); //隐藏窗口
        event->ignore(); //忽略事件
    }
}
void Widget::hideEvent(QHideEvent *event)
{
    if(m_Tray->isVisible())
    {
        hide(); //隐藏窗口
        event->ignore(); //忽略事件
    }
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
    new_GalDialog->slots_receive_data_from_widget_to_gal(data);
}
//接受到gal要求显示histroy信息
void Widget::slot_show_widget_from_gal()
{
    this->showNormal();
}
//接受到gal要求播放语言信息
void Widget::slot_play_voice_from_gal()
{
    qDebug()<<"Widget接受到来自gal播放语言请求";
    m_PushAndReceiveWidget->slot_play_voice_from_widget_to_llm();
}
