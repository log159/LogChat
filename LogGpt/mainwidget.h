#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QApplication>
#include <QPaintEvent>
#include <QPainter>

#include "setlive2ddialogwidget.h"
#include "windowbutton.h"
#include "widget.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    const int MIN_WIDGET    =723;
    const int MIN_HEIGHT    =515;


    enum MousePoss{LeftUp=0,Up,RightUp,Right,RightDown,Down,LeftDown,Left,Middle};
private:

    static QPoint _NormalSize;
    static QPoint _NormalPos;
    Widget*                 m_FuncWidget;
    MainWidget::MousePoss   m_MpCurPos;

private:
     QMenu *              m_TrayMenu                =nullptr;
     QSystemTrayIcon *    m_Tray                    =nullptr;
     QAction*             m_MinimizeAction          =nullptr;
     QAction*             m_MaximizeAction          =nullptr;
     QAction*             m_RestoreAction           =nullptr;
     QMenu*               m_Live2dMenu              =nullptr;
     QMenu*               m_Live2dStartAction       =nullptr;
     QAction*             m_Live2dShowAction        =nullptr;
     QAction*             m_QuitAction              =nullptr;

    QPoint        m_PointLast;
    QPoint        m_PointDeviation;
    bool          m_MousePassIs      =   false;
    bool          m_ByDoubleIs       =   false;
    WindowButton* m_TopWindowBut     =   nullptr;
    WindowButton* m_MinWindowBut     =   nullptr;
    WindowButton* m_RestoreBut       =   nullptr;
    WindowButton* m_CloseWindowBut   =   nullptr;

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

    void init();
    void initConnect();

private:
    void zoom1();
    void zoom2();
    MainWidget::MousePoss calcmouseposs(QPoint p) ;
    void setCursorType(MainWidget::MousePoss type);
    void changeWindowSize(MainWidget::MousePoss type, QRect &wid,QPoint ptemp,int minWidth, int minHeight);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void resizeEvent(QResizeEvent*e);
    void refreshGeometry(int width);

    void closeEvent(QCloseEvent *event);
    void hideEvent(QHideEvent *event);

    void paintEvent(QPaintEvent*event);
signals:

public slots:
    void icon_activated(QSystemTrayIcon::ActivationReason ireason);
};

#endif // MAINWIDGET_H
