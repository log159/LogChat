#include "live2dpartdrawingitemswidget.h"
#include "ui_live2dpartdrawingitemswidget.h"

Live2DPartDrawingItemsWidget::Live2DPartDrawingItemsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Live2DPartDrawingItemsWidget)
{
    ui->setupUi(this);
}

Live2DPartDrawingItemsWidget::~Live2DPartDrawingItemsWidget()
{
    delete ui;
}
