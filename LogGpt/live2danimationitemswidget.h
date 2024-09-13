#ifndef LIVE2DANIMATIONITEMSWIDGET_H
#define LIVE2DANIMATIONITEMSWIDGET_H

#include <QWidget>
#include <QRegExpValidator>
#include <QString>
#include <QRegExp>
#include <QHBoxLayout>

#include "rangeslider.h"

namespace Ui {
class Live2DAnimationItemsWidget;
}

class Live2DAnimationItemsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit Live2DAnimationItemsWidget(QWidget *parent = nullptr);
    ~Live2DAnimationItemsWidget();
public:
    void setName(const QString& str);
    void setExplain(const QString& str);
    void setRule(int index);
    void setUseful(bool bo);
    void setSpeed(int val);

private:
    void init();
    void initConnect();

private:
    Ui::Live2DAnimationItemsWidget *ui;
};

#endif // LIVE2DANIMATIONITEMSWIDGET_H
