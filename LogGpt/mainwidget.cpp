#include "mainwidget.h"


QPoint MainWidget::_NormalSize;
QPoint MainWidget::_NormalPos;
#define min(a,b) ((a)<(b)? (a) :(b))
#define max(a,b) ((a)>(b)? (a) :(b))

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    init();
    initConnect();
}

MainWidget::~MainWidget()
{
    qDebug()<<"MainWidget析构";
    SetLive2DDialogWidget::closeProcess();
}

void MainWidget::init()
{
    ConfigWindow::setWindowPointer(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowTitle(ConfigWindow::WindowTitle);
    this->setWindowIcon(QIcon(":/res/u77.svg"));
    this->setMouseTracking(true);
    m_FuncWidget=new Widget(this);

    this->setMinimumWidth(MIN_WIDGET);
    this->setMinimumHeight(MIN_HEIGHT);

    m_TopWindowBut     =new WindowButton(this);
    m_MinWindowBut     =new WindowButton(this);
    m_RestoreBut       =new WindowButton(this);
    m_CloseWindowBut   =new WindowButton(this);

    m_TopWindowBut->setStyleSheet("QPushButton { background-color: rgba(0, 0, 0, 0); border: none; }");
    m_MinWindowBut->setStyleSheet("QPushButton { background-color: rgba(0, 0, 0, 0); border: none; }");
    m_RestoreBut->setStyleSheet("QPushButton { background-color: rgba(0, 0, 0, 0); border: none; }");
    m_CloseWindowBut->setStyleSheet("QPushButton { background-color: rgba(0, 0, 0, 0); border: none; }");

    m_TopWindowBut->setSelfIcon(":/res/u10.svg");
    m_MinWindowBut->setSelfIcon(":/res/u13.svg");
    m_RestoreBut->setSelfIcon(":/res/u77.svg");
    m_CloseWindowBut->setSelfIcon(":/res/u76.svg");

    this->refreshGeometry(this->width());

    //最小化到托盘
    m_Tray= new QSystemTrayIcon(this);                //初始化托盘对象tray
    m_Tray->setIcon(QIcon(QPixmap(":/res/u77.svg"))); //设定托盘图标，引号内是自定义的png图片路径
    m_Tray->setToolTip(ConfigWindow::WindowTitle);   //提示文字
    m_Tray->show();                                   //让托盘图标显示在系统托盘上

    //创建菜单项动作
    m_MinimizeAction = new QAction("最小化窗口", this);
    m_MaximizeAction = new QAction("最大化窗口", this);
    m_RestoreAction = new QAction("恢复窗口显示", this);
    m_Live2dMenu = new QMenu("Live2d",this);
    m_QuitAction = new QAction("退出应用", this);

    m_Live2dStartAction =new QMenu("启用Live2d");
    m_Live2dShowAction = new QAction("隐藏窗口");

    m_Live2dMenu->addMenu(m_Live2dStartAction);
    m_Live2dMenu->addAction(m_Live2dShowAction);

    //创建托盘菜单
    m_TrayMenu = new QMenu(this);
    m_TrayMenu->addAction(m_MinimizeAction);
    m_TrayMenu->addAction(m_MaximizeAction);
    m_TrayMenu->addAction(m_RestoreAction);
    m_TrayMenu->addMenu(m_Live2dMenu);
    m_TrayMenu->addSeparator();
    m_TrayMenu->addAction(m_QuitAction);
    m_Tray->setContextMenu(m_TrayMenu);
}

void MainWidget::initConnect()
{
    connect(m_FuncWidget,&Widget::mouseChange,[=](Qt::CursorShape poss){
            setCursor(poss);
            m_MpCurPos=MainWidget::MousePoss::Middle;

    });

    connect(m_TopWindowBut,&WindowButton::entered,[=](){setCursor(Qt::ArrowCursor);});
    connect(m_MinWindowBut,&WindowButton::entered,[=](){setCursor(Qt::ArrowCursor);});
    connect(m_RestoreBut,&WindowButton::entered,[=](){setCursor(Qt::ArrowCursor);});
    connect(m_CloseWindowBut,&WindowButton::entered,[=](){setCursor(Qt::ArrowCursor);});
    connect(m_TopWindowBut,&WindowButton::left,[=](){setCursor(Qt::ArrowCursor);});
    connect(m_MinWindowBut,&WindowButton::left,[=](){setCursor(Qt::ArrowCursor);});
    connect(m_RestoreBut,&WindowButton::left,[=](){setCursor(Qt::ArrowCursor);});
    connect(m_CloseWindowBut,&WindowButton::left,[=](){setCursor(Qt::ArrowCursor);});

    connect(m_TopWindowBut,&WindowButton::clicked,[=](){
        static bool winFrontOrNormal=true;
        if(winFrontOrNormal){
            qDebug()<<"最前";
            //设置窗口置顶
            ::SetWindowPos(HWND(this->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
        }
        else {
            //设置窗口一般状态
            ::SetWindowPos(HWND(this->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
        }
        winFrontOrNormal=!winFrontOrNormal;
    });

    connect(m_MinWindowBut,&WindowButton::clicked,[=](){
        this->hide();

    });

    connect(m_RestoreBut,&WindowButton::clicked,[=](){
        static bool winMaxOrNormal=true;
        //全屏
        if(winMaxOrNormal){
            _NormalPos.setX(this->x());
            _NormalPos.setY(this->y());
            _NormalSize.setX(this->width());
            _NormalSize.setY(this->height());
            this->move(0,0);
            zoom1();
        }
        //恢复
        else {
            this->move(_NormalPos.x(),_NormalPos.y());
            zoom2();

        }
        winMaxOrNormal=!winMaxOrNormal;
    });

    connect(m_CloseWindowBut,&WindowButton::clicked,[=](){
        this->~MainWidget();
        exit(0);
    });




    //最小化到托盘的菜单事件连接
    connect(m_MinimizeAction, SIGNAL(triggered()), this, SLOT(hide()));
    connect(m_MaximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));
    connect(m_RestoreAction,&QAction::triggered,this,[=](){
        //设置窗口置顶
        ::SetWindowPos(HWND(this->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
        //设置窗口置顶取消
        ::SetWindowPos(HWND(this->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

        m_FuncWidget->updateOtherWidgetSize();

    });

//    connect(m_Live2dStartAction,&QAction::triggered,this,[=](){



//    });

    connect(m_Live2dShowAction,&QAction::triggered,this,[=](){
        HWND hwnd = ConfigLive2d::getLive2DWindow();
        if (!::IsWindowVisible(hwnd)) {
            // 显示窗口
            ::ShowWindow(hwnd, SW_SHOW);
            m_Live2dShowAction->setText("隐藏Live2d");
            qDebug()<<"显示Live2d hwnd:"<<hwnd;
        } else {
            // 隐藏窗口
            ::ShowWindow(hwnd, SW_HIDE);
            m_Live2dShowAction->setText("显示Live2d");
            qDebug()<<"隐藏Live2d hwnd:"<<hwnd;
        }
    });

    connect(m_QuitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    connect(m_Tray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(icon_activated(QSystemTrayIcon::ActivationReason)));


}

void MainWidget::refreshGeometry(int width)
{
    this->resize(width,this->height());

    m_TopWindowBut->move(this->width()-WindowButton::BUTTON_SIZE*4-29,6);
    m_MinWindowBut->move(this->width()-WindowButton::BUTTON_SIZE*3-23,6);
    m_RestoreBut->move(this->width()-WindowButton::BUTTON_SIZE*2-17,6);
    m_CloseWindowBut->move(this->width()-WindowButton::BUTTON_SIZE-11,6);

}



//计算鼠标位置
MainWidget::MousePoss MainWidget::calcmouseposs(QPoint p)
{
    const int MOUSE_MARGIN=10;
    MainWidget::MousePoss mp;
    if(p.x()<MOUSE_MARGIN && p.y() < MOUSE_MARGIN)
        mp=MainWidget::MousePoss::LeftUp;   //左上
    else if(p.x()>MOUSE_MARGIN && p.y()< MOUSE_MARGIN && p.x()<this->width()-MOUSE_MARGIN)
        mp = MainWidget::MousePoss::Up;   //上
    else if(p.x() > this->width()-MOUSE_MARGIN && p.y() < MOUSE_MARGIN)
        mp = MainWidget::MousePoss::RightUp;   //右上
    else if(p.x() > this->width()-MOUSE_MARGIN && p.y() > MOUSE_MARGIN && p.y()<this->height()-MOUSE_MARGIN)
        mp = MainWidget::MousePoss::Right;   //右
    else if(p.x() > this->width()-MOUSE_MARGIN && p.y() > this->height()-MOUSE_MARGIN)
        mp = MainWidget::MousePoss::RightDown;   //右下
    else if(p.x()>MOUSE_MARGIN && p.x() < this->width()-MOUSE_MARGIN && p.y() > this->height()-MOUSE_MARGIN)
        mp = MainWidget::MousePoss::Down;   //下
    else if(p.x() < MOUSE_MARGIN && p.y() > this->height()-MOUSE_MARGIN)
        mp = MainWidget::MousePoss::LeftDown;   //左下
    else if(p.x() < MOUSE_MARGIN && p.y() < this->height()-MOUSE_MARGIN && p.y()>MOUSE_MARGIN)
        mp = MainWidget::MousePoss::Left;   //左
    else
        mp=MainWidget::MousePoss::Middle;   //中间
    return mp;
}
//修改鼠标样式
void MainWidget::setCursorType(MainWidget::MousePoss type)
{
     Qt::CursorShape cursor;
    switch(type)
    {
    case MainWidget::MousePoss::LeftUp:
    case MainWidget::MousePoss::RightDown:
        cursor=Qt::SizeFDiagCursor;
        break;
    case MainWidget::MousePoss::Up:
    case MainWidget::MousePoss::Down:
        cursor=Qt::SizeVerCursor;
        break;
    case MainWidget::MousePoss::RightUp:
    case MainWidget::MousePoss::LeftDown:
        cursor=Qt::SizeBDiagCursor;
        break;
    case MainWidget::MousePoss::Right:
    case MainWidget::MousePoss::Left:
        cursor=Qt::SizeHorCursor;
        break;
    default:
        cursor=Qt::ArrowCursor;
        break;
    }
    setCursor(cursor);
}
//改变窗口的大小
void MainWidget::changeWindowSize(MainWidget::MousePoss type, QRect &wid,QPoint ptemp,int minWidth, int minHeight)
{
    switch(type)//改变窗口的大小
    {
        case MainWidget::MousePoss::LeftUp:
        {
            QPoint pos = wid.topLeft();

            if(wid.width() > minWidth || ptemp.x() < 0)
                pos.rx() = pos.rx() + ptemp.x();
            if(wid.height() > minHeight || ptemp.y() < 0)
                pos.ry() = pos.ry() + ptemp.y();

            wid.setTopLeft(pos);
            break;//左上角
        }
        case MainWidget::MousePoss::RightUp:
        {
            QPoint pos = wid.topRight();

            if(wid.width() > minWidth || ptemp.x() > 0)
                pos.rx() = pos.rx() + ptemp.x();
            if(wid.height() > minHeight || ptemp.y() < 0)
                pos.ry() = pos.ry() + ptemp.y();

            wid.setTopRight(pos);
            break;//右上角
        }
        case MainWidget::MousePoss::LeftDown:
        {
            QPoint pos = wid.bottomLeft();

            if(wid.width() > minWidth || ptemp.x() < 0)
                pos.rx() = pos.rx() + ptemp.x();
            if(wid.height() > minHeight || ptemp.y() > 0)
                pos.ry() = pos.ry() + ptemp.y();

            wid.setBottomLeft(pos);
            break;//左下角
        }
        case MainWidget::MousePoss::RightDown:
        {
            QPoint pos = wid.bottomRight();

            if(wid.width() > minWidth || ptemp.x() > 0)
                pos.rx() = pos.rx() + ptemp.x();
            if(wid.height() > minHeight || ptemp.y() > 0)
                pos.ry() = pos.ry() + ptemp.y();

            wid.setBottomRight(pos);
            break;//右下角
        }
        case MainWidget::MousePoss::Up:
        {
            int topY = wid.top();
            if(wid.height() > minHeight || ptemp.y() < 0)
                topY = topY + ptemp.y();

            wid.setTop(topY);
            break;//上
        }
        case MainWidget::MousePoss::Left:
        {
            int leftX = wid.left();

            if(wid.width() > minWidth || ptemp.x() < 0)
                leftX = leftX + ptemp.x();

            wid.setLeft(leftX);
            break;//左
        }
        case MainWidget::MousePoss::Right:
        {
            int rightX = wid.right();

            if(wid.width() > minWidth || ptemp.x() > 0)
                rightX = rightX + ptemp.x();

            wid.setRight(rightX);
            break;//右
        }
        case MainWidget::MousePoss::Down:
        {
            int botY = wid.bottom();
            if(wid.height() > minHeight || ptemp.y() > 0)
                botY = botY + ptemp.y();

            wid.setBottom(botY);
            break;//下
        }
    default:
        break;
    }
}

//三个鼠标事件的重写
void MainWidget::mousePressEvent(QMouseEvent *e)
{

    if(e->button()== Qt::LeftButton)	//鼠标左键按下
    {
        m_PointLast = e->globalPos();
        e->ignore();
    }

    m_PointDeviation=e->globalPos()-this->pos();


    if(6<m_PointDeviation.x() && m_PointDeviation.x()<this->width()-6){
        if(6<m_PointDeviation.y() && m_PointDeviation.y()<this->height()-6){
            m_MousePassIs=true;
        }
    }

//    QPoint point = this->mapToGlobal(this->pos());

//    m_MousePoorPoint = e->globalPos()-point;

//    m_ByDoubleIs=false;
//    if(e->button() == Qt::LeftButton){
//        static QTime lastClickTime;
//        int interval = lastClickTime.elapsed();
//        lastClickTime.start();
//        if(interval < QApplication::doubleClickInterval()/3){
//            static bool thisFirst=true;

//            if(thisFirst==true){
//                thisFirst=false;
//            }
//            else {
////                emit sendHandle(1);
//                m_ByDoubleIs=true;
//            }

//        }

//    }

}
//鼠标移动
void MainWidget::mouseMoveEvent(QMouseEvent *e)
{
    MainWidget::MousePoss curPos=calcmouseposs(e->pos());
    if(!e->buttons())
    {
        setCursorType(curPos);
        m_MpCurPos=curPos;
    }

    if(e->buttons()==Qt::LeftButton)	//坐标左键按下并移动
    {
        QPoint ptemp=e->globalPos();
        ptemp=ptemp-m_PointLast;  //鼠标移动的偏移量
        QRect wid=geometry();
        int minWidth = this->minimumWidth();
        int minHeight = this->minimumHeight();
        changeWindowSize(m_MpCurPos,wid,ptemp,minWidth,minHeight);
        //更新大小
        setGeometry(wid);

        m_PointLast = e->globalPos();
    }
    e->ignore();


    if(m_MousePassIs==true)
        this->move(e->globalPos()-m_PointDeviation);

}
//鼠标释放
void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    m_MousePassIs=false;
    QApplication::restoreOverrideCursor();//恢复鼠标指针性状
    e->ignore();
}

void MainWidget::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)
    m_FuncWidget->resize(this->width()-10,this->height()-45);
    m_FuncWidget->move(5,40);

    refreshGeometry(this->width());

}



void MainWidget::zoom1()
{

    QPropertyAnimation * animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(30);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),ConfigWindow::getDesktopWidth(),ConfigWindow::getDesktopHeight()));
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->start(QAbstractAnimation::DeleteWhenStopped);



}

void MainWidget::zoom2()
{
    QPropertyAnimation * animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(30);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),_NormalSize.x(),_NormalSize.y()));
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

}


void MainWidget::closeEvent(QCloseEvent *event)
{
    if(m_Tray->isVisible())
    {
        hide(); //隐藏窗口
        event->ignore(); //忽略事件
    }
}
void MainWidget::hideEvent(QHideEvent *event)
{
    if(m_Tray->isVisible())
    {
        hide(); //隐藏窗口
        event->ignore(); //忽略事件
    }
}

void MainWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    QBrush brush;
    brush.setColor(QColor(255, 255, 255, ConfigWindow::getWindowTransparent()));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0,0,this->width(),this->height());

}
void MainWidget::icon_activated(QSystemTrayIcon::ActivationReason ireason)
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
    ::SetWindowPos(HWND(this->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    m_FuncWidget->updateOtherWidgetSize();
}
