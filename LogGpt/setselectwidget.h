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

#include "configwindow.h"

namespace Ui {
class SetSelectWidget;
}

class SetSelectWidget : public QWidget
{
    Q_OBJECT
private:
    const int _Width      =100;

    bool                  m_ZoomId           =false;
    QVector<QPushButton*> m_ButtonVector;
    QListWidget*          m_ListWidget       =nullptr;
    QPushButton*          m_PushButtonSet    =nullptr;
    QPushButton*          m_PushButtonConfig =nullptr;
    QPushButton*          m_PushButtonClear  =nullptr;
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


signals:
    void setWidgetShow();
    void setConfigShow();
    void clearChat();
private:
    Ui::SetSelectWidget *ui;
};

#endif // SETSELECTWIDGET_H
