#ifndef LIVE2DPARTITEMSWIDGET_H
#define LIVE2DPARTITEMSWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QSlider>
#include <QString>

#include "modelpartitem.h"

namespace Ui {
class Live2DPartItemsWidget;
}

class Live2DPartItemsWidget : public QWidget
{
    Q_OBJECT
    typedef void (QSlider::*SliderChange)(int);
private:
    const int _Width      =400;
    const int _Height     =50;
private:

    ModelPartItem m_ModelPartItem;
public:
    explicit Live2DPartItemsWidget(QWidget *parent = nullptr);
    void init(const ModelPartItem& modItem);
    ~Live2DPartItemsWidget();

    inline const ModelPartItem& getModelItem()const{return m_ModelPartItem;}
    inline void setModelItem(const ModelPartItem& modItem){m_ModelPartItem=modItem;}
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
    void sendPass(ModelPartItem);
    void sendHandle(QString);

private:
    Ui::Live2DPartItemsWidget *ui;
};

#endif // LIVE2DPARTITEMSWIDGET_H
