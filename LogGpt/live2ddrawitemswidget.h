#ifndef LIVE2DDRAWITEMSWIDGET_H
#define LIVE2DDRAWITEMSWIDGET_H

#include <QWidget>
#include <QSlider>
#include <QMouseEvent>

#include "modelpartitem.h"

namespace Ui {
class Live2DDrawItemsWidget;
}

class Live2DDrawItemsWidget : public QWidget
{
    Q_OBJECT

    typedef void (QSlider::*SliderChange)(int);
private:
    const int _Width     =400;
    const int _Height    =50;
private:
    ModelPartItem m_ModelPartItem;
public:
    explicit Live2DDrawItemsWidget(QWidget *parent = nullptr);
    void init(const ModelPartItem& modItem);
    ~Live2DDrawItemsWidget();

    inline const ModelPartItem& getModelItem()const{return m_ModelPartItem;}
    inline void setModelItem(const ModelPartItem& modItem){m_ModelPartItem=modItem;}
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
    void sendPass(ModelPartItem);
    void sendHandle(QString);

private:
    Ui::Live2DDrawItemsWidget *ui;
};

#endif // LIVE2DDRAWITEMSWIDGET_H
