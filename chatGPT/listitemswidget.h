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
    const int _Width        =415;
    const int _Height       =50;
    const int _IconWidth    =35;
    const int _IconHeight   =35;

protected:
    QLabel * _Icon_lab;
    QTextEdit * _Title_edit;
    QFont _Font;

public:
    explicit ListItemsWidget(QWidget *parent = nullptr);
    ~ListItemsWidget();

    void initItem(const QString& strTitle,const ItemEnum& ItEn,int line);
private:

    void paintEvent(QPaintEvent*e);
    void initWidget();
    void setItemTitle(const QString & strTitle);
    void setItemHeight(const QString & strTitle);

private:
    Ui::ListItemsWidget *ui;
};

#endif // LISTITEMSWIDGET_H
