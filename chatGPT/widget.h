#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QIcon>
#include <QString>

#include "pushandreceivewidget.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

private:
    const QString   _WindowTitle  ="Log_Chat";
    const int       _Width        =450;
    const int       _Height       =600;


    PushAndReceiveWidget* _pushandreceiveWidget;
public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();



private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
