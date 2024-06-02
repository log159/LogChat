#ifndef LIVE2DLISTITEMSWIDGET_H
#define LIVE2DLISTITEMSWIDGET_H

#include <QWidget>
#include <QString>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

#include "modelconfigitem.h"

namespace Ui {
class Live2DListItemsWidget;
}

class Live2DListItemsWidget : public QWidget
{
    Q_OBJECT
private:
    const int _Width      =225;
    const int _Height     =75;
private:
    ModelConfigItem m_ModelConfigItem;
public:
    explicit Live2DListItemsWidget(QWidget *parent = nullptr);
    void init(const ModelConfigItem& modItem);
    ~Live2DListItemsWidget();

    inline const ModelConfigItem& getModelItem()const{return m_ModelConfigItem;}
    inline void setModelItem(const ModelConfigItem& modItem){m_ModelConfigItem=modItem;}
    void setText(const QString& str);

    void mousePressEvent(QMouseEvent *event);

signals:
    void sendPass(ModelConfigItem);
private:
    Ui::Live2DListItemsWidget *ui;
};

#endif // LIVE2DLISTITEMSWIDGET_H
