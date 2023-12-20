#ifndef SETSELECTWIDGET_H
#define SETSELECTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QBrush>
#include <QPushButton>
#include <QDebug>
#include <QAbstractAnimation>
#include <QPropertyAnimation>
#include <QListWidget>
#include <QListWidgetItem>
#include <QVector>
#include <QPainter>
#include <QPaintEvent>
#include <QBrush>

#include "configwindow.h"
#include "setpushbutton.h"

namespace Ui {
class SetSelectWidget;
}

class SetSelectWidget : public QWidget
{
    Q_OBJECT
    typedef void (SetPushButton::*SendButtonHandle)();
private:
    const int _Width            =100;
    const int _ButtonHeight     =60;

    int                         m_ButtonId         =-1;
    bool                        m_ZoomId           =false;
    QVector<SetPushButton*>     m_ButtonVector;
    QListWidget*                m_ListWidget       =nullptr;
    SetPushButton*              m_PushButtonSet    =nullptr;
    SetPushButton*              m_PushButtonConfig =nullptr;
    SetPushButton*              m_PushButtonLive2D =nullptr;
    SetPushButton*              m_PushButtonAbout  =nullptr;
    SetPushButton*              m_PushButtonClear  =nullptr;
public:
    explicit SetSelectWidget(QWidget *parent = nullptr);
    ~SetSelectWidget();

    void setAdapt();

    void zoom();
    void setNoPass();
    void setCanPass();

private:
    void init();
    void initConnect();
    void zoom1();
    void zoom2();

    void paintEvent(QPaintEvent*e);


signals:
    void setWidgetShow();
    void setConfigShow();
    void setLive2DShow();
    void setAboutShow();
    void clearChat();
private:
    Ui::SetSelectWidget *ui;
};

#endif // SETSELECTWIDGET_H
