#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QIcon>
#include <QPixmap>
#include <QString>
#include <QMouseEvent>
#include <QDebug>
#include <QResizeEvent>
#include <QRect>
#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QDesktopServices>
#include <windows.h>
#include <QApplication>
#include <QDesktopWidget>

#include "configwindow.h"
#include "pushandreceivewidget.h"
#include "setselectwidget.h"
#include "setdialogwidget.h"
#include "setconfigdialogwidget.h"
#include "setlive2ddialogwidget.h"
#include "setselectpushbutton.h"
#include "aboutsoftwaredialogwidget.h"
#include "netlive2d.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    typedef void (PushAndReceiveWidget::*SendAudio)(QString);
    typedef void (SetLive2DDialogWidget::*SendModelHandle)(QString);
private:
     QMenu *              m_TrayMenu                =nullptr;
     QSystemTrayIcon *    m_Tray                    =nullptr;
     QAction*             m_MinimizeAction          =nullptr;
     QAction*             m_MaximizeAction          =nullptr;
     QAction*             m_RestoreAction           =nullptr;
     QAction*             m_QuitAction              =nullptr;

private:

    PushAndReceiveWidget* m_PushAndReceiveWidget    =nullptr;
    SetSelectWidget*      m_SetSelectWidget         =nullptr;
    NetLive2D*            m_NetLive2D               =nullptr;

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    void init();
    void initConnect();
    void resizeEvent(QResizeEvent*event);
    void closeEvent(QCloseEvent *event);
    void hideEvent(QHideEvent *event);
private slots:
    void icon_activated(QSystemTrayIcon::ActivationReason ireason);


private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
