#ifndef CHANGELIVE2DWIDGET_H
#define CHANGELIVE2DWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMap>
#include <QFile>
#include <QDebug>
#include <QRegExp>
#include <QVector>
#include <QDir>
#include <QTimer>

#include "modelpartitem.h"
#include "live2dpartitemswidget.h"
#include "live2ddrawitemswidget.h"

namespace Ui {
class ChangeLive2DWidget;
}

class ChangeLive2DWidget : public QDialog
{
    Q_OBJECT
    typedef void (Live2DPartItemsWidget::*SendPassByPart)(ModelPartItem);
    typedef void (Live2DDrawItemsWidget::*SendPassByDraw)(ModelPartItem);

private:
    const int _Width      =900;
    const int _Height     =600;

    QMap<QString,QVector<int>>  m_PartItemsMap;
    QMap<QString,bool>          m_DrawItemsMap;
    QMap<QString,QString>       m_ValueExplainMap;
    QMap<QString,int>           m_ItemsCoverMap;
    QMap<QString,bool>          m_DrawsCovermap;

public:
    explicit ChangeLive2DWidget(QWidget *parent = nullptr);
    ~ChangeLive2DWidget();

    void refresh(const QString& path="");

private:
    void init();
    void initValueExplainMap(const QString& path);
    void initPartsItemMap(const QString& path);
    void initDrawsItemMap(const QString& path);
    void initPartsCoverMap(const QString& path="");
    void initDrawsCovermap(const QString& path="");
signals:
    void sendhandle(QString);

private:
    Ui::ChangeLive2DWidget *ui;
};

#endif // CHANGELIVE2DWIDGET_H
