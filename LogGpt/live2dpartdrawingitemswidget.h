#ifndef LIVE2DPARTDRAWINGITEMSWIDGET_H
#define LIVE2DPARTDRAWINGITEMSWIDGET_H

#include <QWidget>

namespace Ui {
class Live2DPartDrawingItemsWidget;
}

class Live2DPartDrawingItemsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit Live2DPartDrawingItemsWidget(QWidget *parent = nullptr);
    ~Live2DPartDrawingItemsWidget();

private:
    Ui::Live2DPartDrawingItemsWidget *ui;
};

#endif // LIVE2DPARTDRAWINGITEMSWIDGET_H
