#ifndef LISTITEMSWIDGET_H
#define LISTITEMSWIDGET_H

#include <QWidget>
#include <QSizePolicy>
#include <QPalette>
#include <QPainter>
#include <QLabel>
#include <QString>
#include <QFont>
#include <QPixmap>
#include <QTextEdit>
#include <QDebug>

#include "configwindow.h"
enum ItemEnum{
  User,Bot
};

namespace Ui {
class ListItemsWidget;
}

class ListItemsWidget : public QWidget
{
    Q_OBJECT

private:

    const int _Height       =40;
    const int _IconWidth    =35;
    const int _IconHeight   =35;
protected:
    QLabel*     m_IconLab      =nullptr;
    QTextEdit*  m_TitleEdit    =nullptr;
    ItemEnum    m_ItemEnum;
    QFont       m_Font;

public:
    explicit ListItemsWidget(QWidget *parent = nullptr);
    ~ListItemsWidget();

    void initItem(const QString& strTitle,const ItemEnum& ItEn,int line);
    void setAdapt();//调整大小
private:

    void init();
    void setItemTitle(const QString & strTitle);
    void setItemHeight(const QString & strTitle);

private:
    Ui::ListItemsWidget *ui;
};

#endif // LISTITEMSWIDGET_H
