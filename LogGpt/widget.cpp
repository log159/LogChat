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
    connect(m_SetSelectWidget,&SetSelectWidget::clearChat,[=](){
        m_PushAndReceiveWidget->clearHistory();
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


    //最小化到托盘的菜单事件连接
    connect(m_MinimizeAction, SIGNAL(triggered()), this, SLOT(hide()));
    connect(m_MaximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));
    connect(m_RestoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));
    connect(m_RestoreAction,&QAction::triggered,this,[=](){
        //设置窗口置顶
        ::SetWindowPos(HWND(this->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
        ::SetWindowPos(HWND(this->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

    });
    connect(m_QuitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    connect(m_RestoreAction, &QAction::triggered, this, [=](){
        this->m_PushAndReceiveWidget->setAdapt();
    });

    connect(m_Tray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(icon_activated(QSystemTrayIcon::ActivationReason)));
}

void Widget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    ConfigWindow::setStaticPosX(this->geometry().topLeft().x());
    ConfigWindow::setStaticPosY(this->geometry().topLeft().y());
    ConfigWindow::setStaticWidth(this->width());
    ConfigWindow::setStaticHeight(this->height());

//    qDebug()<<this->width()<<"  "<<this->height();
    m_PushAndReceiveWidget->setAdapt();
    m_SetSelectWidget->setFixedSize(m_SetSelectWidget->width(),ConfigWindow::getStaticHeight()-50);
    m_SetSelectWidget->setAdapt();
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
