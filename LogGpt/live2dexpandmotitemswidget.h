#ifndef LIVE2DEXPANDMOTITEMSWIDGET_H
#define LIVE2DEXPANDMOTITEMSWIDGET_H

#include <QWidget>
#include <QSlider>
#include <QMouseEvent>
#include <QDebug>
#include <QPair>

namespace Ui {
class Live2dExpAndMotItemsWidget;
}

class Live2dExpAndMotItemsWidget : public QWidget
{
    Q_OBJECT
public:
    const int WIDTH     =100;
    const int HEIGHT    =50;

private:
    const QString m_HandleStr="Exp:%1,%2;";
    QPair<QString,int>    m_Data;
public:
    explicit Live2dExpAndMotItemsWidget(QWidget *parent = nullptr);
    ~Live2dExpAndMotItemsWidget();
    void init(const QPair<QString,int>& data);

    inline const QPair<QString,int>& getData()const{return m_Data;}
    inline void setData(const QPair<QString,int>& data){m_Data=data;}

    void mousePressEvent(QMouseEvent *event);
private:
    void initConnect();
signals:
    void sendPass(QPair<QString,int>);
    void sendHandle(QString);
private:
    Ui::Live2dExpAndMotItemsWidget *ui;
};

#endif // LIVE2DEXPANDMOTITEMSWIDGET_H
