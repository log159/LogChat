#ifndef CONFIG_H
#define CONFIG_H

#include <QCoreApplication>
#include <QString>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QDebug>
#include <QVector>
#include <QRegularExpression>
#include <QMap>
#include <QPair>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QList>


#include "singletonbase.h"
#include "global.h"
#include "configfileio.h"
#include "configconstway.h"
#include "modelconfigitem.h"



class Config:public SingletonBase{
public:
    //初始化
    static void init();
private:
    //临时存储信息
    static QVector<ModelConfigItem>   LIVE2DMODELCONFIG_V;   //全部加载的Live2D配置信息
public:
    static QVector<ModelConfigItem> get_LIVE2DMODELCONFIG_V();

private:
    //init l2d初始化通用配置信息
    static void init_LIVE2DMODELCONFIG_V();
    //修改文件配置
    static void output_LIVE2DMODELCONFIG_V(QVector<ModelConfigItem>& modV);

public:
    //获取配置信息
    static const ::IKS get_IKS(const ::EnIks& iks);
    static const QString get_URL(const ::EnUrl& urlName);
    static const QString get_USER(const ::EnUser& key);
    static QString get_OTHER(const QString& path,const QString& baseName,const QString& keyName);
    static QMap<QString,QString> get_OTHER_BASE(const QString& path,const QString& baseName);

public:
    //设置配置信息
    static void set_IKS(const ::EnIks& iks, const QString &id, const QString &key, const QString &secret);
    static void set_URL(const ::EnUrl& urlName,const QString& url);
    static void set_USER(const ::EnUser& key,const QString& value);
    static void set_OTHER(const QString& path,const QString& baseName,const QString& keyName,const QString& value);
    static void set_OTHER_BASE(const QString& path,const QString& baseName,QMap<QString,QString>data);

public:
    static const QString get_VITS_URL();
    static const QString get_GPTSOVITS_URL();
    static const QString get_VITSSELF_URL();
    static const QString get_UNITY_STARTMODELPATH();
    static const QString get_CHARACTERCONFIG();

    static void          set_XFXH_QUESTION(const QString& str);
    static void          set_UNITY_STARTMODELPATH(const QString& str);
    static void          set_LIVE2DMODELCONFIG_V(QVector<ModelConfigItem>& modV);
};

#endif // CONFIG_H


