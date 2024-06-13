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

private:

    //临时存储信息
    static QVector<ModelConfigItem>   LIVE2DMODELCONFIG_V;   //全部加载的Live2D配置信息
public:
    //初始化
    static void init();
private:
    //io操作
    static const QString getFileInformation(const QString& path);
    static const QString getFileAllInformation(const QString& path);
    static void setFileInformation(const QString& path,const QString& str);
    static void setFileInformation(const QString& path,const QJsonObject& js);

    //其它操作
    static QMap<QString, QString> parseJsonToQMap(const QString &jsonString);

    //init操作
    static void init_LIVE2DMODELCONFIG_V();

private:
    //修改文件配置
    static void output_ALLSETCONFIG(const QJsonObject& js);
    static void output_LIVE2DMODELCONFIG_V(QVector<ModelConfigItem>& modV);


public:
    //获取Vector
    static QVector<QString> get_VITS_MODEL_V();
    static QVector<QString> get_VITS_ALL_V();
    static QVector<QString> get_LANGUAGE_V();
    static QVector<QString> get_CHATGPT_MODEL_V();
    static QVector<QString> get_XFXH_MODEL_V();
    static QVector<ModelConfigItem> get_LIVE2DMODELCONFIG_V();
    //获取map
    static QMap<QString,bool>    get_LIVE2DENABLEINIT_M();
    static QMap<QString,int>     get_LIVE2DPARAMINIT_M();
    static QMap<QString,QString> get_LIVE2DSTRING_M();

public:
    //获取配置信息
    static const ::IKS get_IKS(const ::EnIks& iks);
    static const QString get_URL(const ::EnUrl& urlName);
    static const QString get_USER(const ::EnUser& key);
public:
    //设置配置信息
    static void set_IKS(const ::EnIks& iks, const QString &id, const QString &key, const QString &secret);
    static void set_URL(const ::EnUrl& urlName,const QString& url);
    static void set_USER(const ::EnUser& key,const QString& value);
public:
    //获取非重要的用户配置信息
    static const QString get_URL_ADDRESS_ALL();
    static const QString get_XFXH_QUESTION();
    static const QString get_UNITY_STARTMODELPATH();


    //设置非重要的用户配置信息
    static void          set_XFXH_QUESTION(const QString& str);
    static void          set_UNITY_STARTMODELPATH(const QString& str);
    static void          set_LIVE2DMODELCONFIG_V(QVector<ModelConfigItem>& modV);

};

#endif // CONFIG_H


