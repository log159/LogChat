#ifndef LIVE2DDRAWITEMSWIDGET_H
#define LIVE2DDRAWITEMSWIDGET_H

#include <QWidget>
#include <QSlider>
#include <QMouseEvent>

#include "changeconfigitem.h"

namespace Ui {
class Live2DDrawItemsWidget;
}

class Live2DDrawItemsWidget : public QWidget
{
    Q_OBJECT

    typedef void (QSlider::*SliderChange)(int);
private:
    const int WIDTH    =400;
    const int HEIGHT    =50;
private:

    const QString m_HandleStr="Draw:%1,%2;";
    ChangeConfigItem m_ChangeConfigItem;
public:
    explicit Live2DDrawItemsWidget(QWidget *parent = nullptr);
    void init(const ChangeConfigItem& modItem);
    ~Live2DDrawItemsWidget();

    inline const ChangeConfigItem& getModelItem()const{return m_ChangeConfigItem;}
    inline void setModelItem(const ChangeConfigItem& modItem){m_ChangeConfigItem=modItem;}
    QString getName()const;
    void setText(const QString& str);
    void setValue(bool bo);
    int getValue()const;
    void resetValue();
    bool isDefault()const;

    void mousePressEvent(QMouseEvent *event);
private:
    void initConnect();
signals:
    void sendPass(ChangeConfigItem);
    void sendHandle(QString);

private:
    Ui::Live2DDrawItemsWidget *ui;
};

#endif // LIVE2DDRAWITEMSWIDGET_H
