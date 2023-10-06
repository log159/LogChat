#ifndef USERITEMSWIDGET_H
#define USERITEMSWIDGET_H

#include <QWidget>

#include "listitemswidget.h"

namespace Ui {
class UserItemsWidget;
}

class UserItemsWidget : public ListItemsWidget
{
    Q_OBJECT

public:
    explicit UserItemsWidget(QWidget *parent = nullptr);
    ~UserItemsWidget();
private:
    void init();

private:
    Ui::UserItemsWidget *ui;
};

#endif // USERITEMSWIDGET_H
