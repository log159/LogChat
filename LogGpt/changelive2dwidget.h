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
#include "live2danimationitemswidget.h"

namespace Ui {
class ChangeLive2DWidget;
}

class ChangeLive2DWidget : public QDialog
{
    Q_OBJECT
    typedef void (Live2DPartItemsWidget::*SendPassByPart)(ModelPartItem);
    typedef void (Live2DDrawItemsWidget::*SendPassByDraw)(ModelPartItem);

private:
//    struct defaultHarmItem{
//        int

//    }
private:
    const int _Width      =900;
    const int _Height     =600;

    QMap<QString,QVector<int>>  m_PartItemsMap;     //PARAMETERLIST
    QMap<QString,bool>          m_DrawItemsMap;     //DRAWINGLIST
    QMap<QString,QString>       m_ValueExplainMap;  //"*.cdi3.json"
    QMap<QString,int>           m_PartCoverMap;     //PARAMETERCHANGELIST
    QMap<QString,bool>          m_DrawsCoverMap;    //DRAWINGCHANGELIST
    QMap<QString,QVector<int>>  m_HarmCoverMap;     //HARMONICCHANGELIST

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
    void initHarmCoverMap(const QString& path="");
signals:
    void sendhandle(QString);

private:
    Ui::ChangeLive2DWidget *ui;
};

#endif // CHANGELIVE2DWIDGET_H
