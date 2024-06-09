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

    static QString                  URL_ADDRESS;             //VITS Url地址
    static QString                  URL_PORT;                //VITS Url端口
    static bool                     ENABLE_ROLE;           //是否启用角色扮演
    static bool                     ENABLE_SOUND;          //是否启用语音
    static bool                     ENABLE_BAIDUFANYI;     //是否启用百度翻译
    static bool                     ENABLE_LATERLANGUAGE;  //是否启用翻译后的语言用来显示
    static bool                     ENABLE_RESERVE;        //是否保留上下文记忆
    static int                      LLM_MODEL_ID;          //LLM模型ID 0 chatgpt 1讯飞星火
    static int                      XFXH_MODEL_ID;         //讯飞星火模型ID
    static int                      CHATGPT_MODEL_ID;      //ChatGpt模型ID
    static int                      VITS_ID;               //vits模型ID
    static int                      SPEAKER_ID;            //讲述人ID
    static int                      EMOTION_ID;            //情感控制ID
    static int                      BAIDU_FROM_ID;         //原语种ID
    static int                      BAIDU_TO_ID;           //翻译后语种ID
    static int                      RESERVE_LONG;          //上下文保留最大长度

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
    static void init_ALLSETCONFIG();
    static void init_LIVE2DMODELCONFIG_V();
    static void init_HISTORY();

private:
    //修改文件配置
    static void output_ALLSETCONFIG(const QJsonObject& js);
    static void output_LIVE2DMODELCONFIG_V(QVector<ModelConfigItem>& modV);


public:
    //获取Vector
    static QVector<QString> get_VITS_ALL_V();
    static QVector<QString> get_LANGUAGE_V();
    static QVector<QString> get_CHATGPT_MODEL_V();
    static QVector<QString> get_XFXH_MODEL_V();
    static QVector<ModelConfigItem> get_LIVE2DMODELCONFIG_V();
    //获取map
    static QMap<QString,bool>   get_LIVE2DENABLEINIT_M();
    static QMap<QString,int>    get_LIVE2DPARAMINIT_M();
    static QMap<QString,QString> get_LIVE2DSTRING_M();

public:
    //获取重要的配置信息
    static const ::IKS get_IKS(const ::EnIks& iks);
    static const QString get_URL(const ::EnUrl& urlName);
public:
    //设置重要的配置信息
    static void set_IKS(const ::EnIks& iks, const QString &id, const QString &key, const QString &secret);
    static void set_URL(const ::EnUrl& urlName,const QString& url);
public:
    //获取非重要的用户配置信息
    static const QString get_URL_ADDRESSS();
    static const QString get_URL_PATH();
    static const QString get_URL_ADDRESS_ALL();
    static const QString get_CHARACTER_CONFIG();
    static const QString get_XFXH_QUESTION();
    static const QString get_UNITY_STARTMODELPATH();
    static bool          get_ENABLE_ROLE();
    static bool          get_ENABLE_SOUND();
    static bool          get_ENABLE_BAIDUFANYI();
    static bool          get_ENABLE_LATERLANGUAGE();
    static bool          get_ENABLE_RESERVE();
    static int           get_LLM_MODEL_ID();
    static int           get_XFXH_MODEL_ID();
    static int           get_CHATGPT_MODEL_ID();
    static int           get_VITS_ID();
    static int           get_SPEAKER_ID();
    static int           get_EMOTION_ID();
    static int           get_BAIDU_FROM_ID();
    static int           get_BAIDU_TO_ID();
    static int           get_RESERVE_LONG();

    //设置非重要的用户配置信息
    static void          set_URL_ADDRESS(const QString& str);
    static void          set_URL_PORT(const QString& str);
    static void          set_CHARACTER_CONFIG(const QString& str);
    static void          set_XFXH_QUESTION(const QString& str);
    static void          set_UNITY_STARTMODELPATH(const QString& str);
    static void          set_LIVE2DMODELCONFIG_V(QVector<ModelConfigItem>& modV);
    static void          set_ENABLE_ROLE(const bool& bo);
    static void          set_ENABLE_SOUND(const bool& bo);
    static void          set_ENABLE_BAIDUFANYI(const bool& bo);
    static void          set_ENABLE_LATERLANGUAGE(const bool& bo);
    static void          set_ENABLE_RESERVE(const bool& bo);
    static void          set_LLM_MODEL_ID(int id);
    static void          set_XFXH_MODEL_ID(int id);
    static void          set_CHATGPT_MODEL_ID(int id);
    static void          set_VITS_ID(int id);
    static void          set_SPEAKER_ID(int id);
    static void          set_EMOTION_ID(int id);
    static void          set_BAIDU_FROM_ID(int id);
    static void          set_BAIDU_TO_ID(int id);
    static void          set_RESERVE_LONG(int id);
    static void          set_ALLSETCONFIG();


};

#endif // CONFIG_H


