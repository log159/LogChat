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

#include "config.h"
#include "modelpartitem.h"
#include "live2dpartitemswidget.h"
#include "live2ddrawitemswidget.h"
#include "live2danimationitemswidget.h"

enum EnItem{
    PARAMETERLIST,
    PARAMETERCHANGELIST,
    DRAWABLELIST,
    DRAWABLECHANGELIST
};
static QMap<EnItem,QString>ItemM{
    {PARAMETERLIST,"PARAMETERLIST"},
    {PARAMETERCHANGELIST,"PARAMETERCHANGELIST"},
    {DRAWABLELIST,"DRAWABLELIST"},
    {DRAWABLECHANGELIST,"DRAWABLECHANGELIST"}
};

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
    const int WIDTH                         =900;
    const int HEIGHT                        =600;
    const QString ConfigFileName            ="ModelConfig.ini";

private:


    QMap<QString,QVector<int>>  m_ParameterItemsMap;    //PARAMETERLIST
    QMap<QString,bool>          m_DrawableItemsMap;         //DRAWINGLIST
    QMap<QString,QString>       m_ValueExplainMap;      //"*.cdi3.json"
    QMap<QString,int>           m_ParameterCoverMap;    //PARAMETERCHANGELIST
    QMap<QString,bool>          m_DrawableCoverMap;        //DRAWINGCHANGELIST
    QMap<QString,QVector<int>>  m_HarmCoverMap;         //HARMONICCHANGELIST

public:
    explicit ChangeLive2DWidget(QWidget *parent = nullptr);
    ~ChangeLive2DWidget();

    void refresh(const QString& path="");

private:
    void init();
    void initValueExplainMap(const QString& path);
    void initParameterItemsMap(const QString& path);
    void initDrawableItemsMap(const QString& path);
    void initParameterCoverMap(const QString& path="");
    void initDrawableCovermap(const QString& path="");
    void initHarmCoverMap(const QString& path="");
signals:
    void sendhandle(QString);

private:
    Ui::ChangeLive2DWidget *ui;
};

#endif // CHANGELIVE2DWIDGET_H
