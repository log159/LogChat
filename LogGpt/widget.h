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
#include <QTimer>
#include <QDesktopWidget>
#include <QSharedPointer>
#include <QMenuBar>
#include <QPainter>
#include <QPaintEvent>

#include "configwindow.h"
#include "pushandreceivewidget.h"
#include "setselectwidget.h"
#include "setdialogwidget.h"
#include "setconfigdialogwidget.h"
#include "galdialog.h"
#include "setlive2ddialogwidget.h"
#include "setselectpushbutton.h"
#include "aboutsoftwaredialogwidget.h"
#include "setcompounddialogwidget.h"
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

    PushAndReceiveWidget* m_PushAndReceiveWidget    =nullptr;
    SetSelectWidget*      m_SetSelectWidget         =nullptr;
    NetLive2D*            m_NetLive2D               =nullptr;
public:
    QSharedPointer<GalDialog> new_GalDialog; //新窗口
public:
    explicit Widget(QWidget *parent = nullptr);
    void updateOtherWidgetSize();
    ~Widget();
private:
    void init();
    void initConnect();
    void resizeEvent(QResizeEvent*event);

    void paintEvent(QPaintEvent*event);

    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);

signals:
    void mouseChange(Qt::CursorShape);

private slots:


    void slot_receive_data_from_gal_to_widget(QString data); //接收Gal窗口传递过来的数据的槽
    void slot_receive_data_from_llm_to_widget(QString data); //接收llm传递过来的数据的槽

    void slot_show_widget_from_gal(); //接收Gal窗口显示窗口的指令
    void slot_play_voice_from_gal(); //接收Gal窗口播放语言的指令



private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
