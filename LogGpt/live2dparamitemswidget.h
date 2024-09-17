#ifndef LIVE2DPARAMITEMSWIDGET_H
#define LIVE2DPARAMITEMSWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QSlider>
#include <QString>

#include "changeconfigitem.h"
namespace Ui {
class Live2DParamItemsWidget;
}

class Live2DParamItemsWidget : public QWidget
{
    Q_OBJECT
    typedef void (QSlider::*SliderChange)(int);
private:
    const int WIDTH      =400;
    const int HEIGHT     =50;
private:

    const QString m_HandleStr="Param:%1,%2;";
    ChangeConfigItem m_ChangeConfigItem;
public:
    explicit Live2DParamItemsWidget(QWidget *parent = nullptr);
    void init(const ChangeConfigItem& modItem);
    ~Live2DParamItemsWidget();

    inline const ChangeConfigItem& getModelItem()const{return m_ChangeConfigItem;}
    inline void setModelItem(const ChangeConfigItem& modItem){m_ChangeConfigItem=modItem;}
    QString getName()const;
    void setText(const QString& str);
    void setExplain(const QString& str);
    void setValue(int val);
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
    Ui::Live2DParamItemsWidget *ui;
};

#endif // LIVE2DPARAMITEMSWIDGET_H
