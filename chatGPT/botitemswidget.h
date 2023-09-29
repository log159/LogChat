#ifndef BOTITEMSWIDGET_H
#define BOTITEMSWIDGET_H

#include <QWidget>

#include "listitemswidget.h"

namespace Ui {
class BotItemsWidget;
}

class BotItemsWidget : public ListItemsWidget
{
    Q_OBJECT

public:
    explicit BotItemsWidget(QWidget *parent = nullptr);
    ~BotItemsWidget();

private:
    Ui::BotItemsWidget *ui;
};

#endif // BOTITEMSWIDGET_H
