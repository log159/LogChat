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
#include "changeconfigitem.h"
#include "live2dparamitemswidget.h"
#include "live2dpartitemswidget.h"
#include "live2ddrawitemswidget.h"
#include "live2dexpandmotitemswidget.h"
#include "live2danimationitemswidget.h"


#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>
#include <QString>
#include <QFile>
#include <QDebug>

namespace Ui {
class ChangeLive2DWidget;
}

class ChangeLive2DWidget : public QDialog
{
    Q_OBJECT
    typedef void (Live2DParamItemsWidget::*SendPassByParam)(ChangeConfigItem);
    typedef void (Live2DPartItemsWidget::*SendPassByPart)(ChangeConfigItem);
    typedef void (Live2DDrawItemsWidget::*SendPassByDraw)(ChangeConfigItem);
    typedef void (Live2dExpAndMotItemsWidget::*SendPassByExpMot)(QPair<QString,int>);


private:
    const int WIDTH                         =900;
    const int HEIGHT                        =600;
    const QString ConfigFileName            ="ModelConfig.ini";

private:

    QString                     m_FilePath  ="";        //存储路径
    QMap<QString,QString>       m_ValueExplainMap;      //"*.cdi3.json"
    QMap<QString,QVector<int>>  m_ParameterItemsMap;    //PARAMETERLIST
    QMap<QString,QVector<int>>  m_PartItemsMap;         //PARTLIST
    QMap<QString,bool>          m_DrawableItemsMap;     //DRAWABLELIST
    QMap<QString,int>           m_ExpressionItemsMap;   //EXPRESSIONLIST
    QMap<QString,int>           m_MotionItemsMap;       //MOTIONLIST
    QMap<QString,int>           m_ParameterCoverMap;    //PARAMETERCHANGELIST
    QMap<QString,int>           m_PartCoverMap;         //PARTCHANGELIST
    QMap<QString,bool>          m_DrawableCoverMap;     //DRAWABLECHANGELIST
//    QMap<QString,QVector<int>>  m_HarmCoverMap;       //HARMONICCHANGELIST

public:
    explicit ChangeLive2DWidget(QWidget *parent = nullptr);
    ~ChangeLive2DWidget();

    void refresh(const QString& path="");

private:
    void init();

    void initValueExplainMap();
    void initParameterItemsMap();
    void initPartItemsMap();
    void initDrawableItemsMap();
    void initExpressionItemsMap();
    void InitMotionItemsMap();
    void initParameterCoverMap();
    void initPartCovermap();
    void initDrawableCovermap();
    void initHarmCoverMap();

    void initUiParameterList();
    void initUiPartList();
    void initUiDrawableList();
    void initUiExpressionList();
    void initUiMotionList();
    void initUiConnectParameterButton();
    void initUiConnectPartButton();
    void initUiConnectDrawableButton();
    void initUiConnectExpressionButton();
    void initUiConnectMotionButton();


    //解析cdi3.json
    QMap<QString, QString> parseCdi3Json(const QString& jsonStr);
signals:
    void sendHandle(QString);

private:
    Ui::ChangeLive2DWidget *ui;
};

#endif // CHANGELIVE2DWIDGET_H
