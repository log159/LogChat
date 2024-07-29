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
#include <QPainter>

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

    const int HEIGHT       =50;
    const int ICON_WIDTH    =35;
    const int ICON_HEIGHT   =35;
protected:
    QLabel*     m_IconLab      =nullptr;
    QTextEdit*  m_TitleEdit    =nullptr;
    ItemEnum    m_ItemEnum;
    QFont       m_Font;

public:
    explicit ListItemsWidget(QWidget *parent = nullptr);
    ~ListItemsWidget();

    void initItem(const QString& strTitle,const ItemEnum& ItEn);
    void setAdapt();//调整大小
private:

    void init();
    void initConnect();

private slots:
    void slot_text_change();
private:
    Ui::ListItemsWidget *ui;
};

#endif // LISTITEMSWIDGET_H
