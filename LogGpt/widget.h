#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QIcon>
#include <QString>
#include <QMouseEvent>
#include <QDebug>

#include "pushandreceivewidget.h"
#include "setselectwidget.h"
#include "setdialogwidget.h"
#include "setconfigdialogwidget.h"
#include "setselectpushbutton.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

private:
    const QString   _WindowTitle  ="Log_Chat";
    const int       _Width        =840;
    const int       _Height       =600;

    PushAndReceiveWidget* m_PushAndReceiveWidget    =nullptr;
    SetSelectWidget*      m_SetSelectWidget         =nullptr;
    SetSelectPushButton*  m_SetSelectPushButton     =nullptr;

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    void init();
    void initConnect();


private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
