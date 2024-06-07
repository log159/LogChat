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
#include "modelconfigitem.h"


class Config:public SingletonBase{

private:

    static const QVector<QString>           VITS_ALL_V;            //全部vits模型
    static const QVector<QString>           LANGUAGE_V;            //全部百度翻译语种
    static const QVector<QString>           CHATGPT_MODEL_V;       //全部支持ChatGPT模型
    static const QVector<QString>           XFXH_MODEL_V;          //全部支持讯飞星火模型
    static const QMap<QString,bool>         LIVE2DENABLEINIT_M;    //全部Live2D ENABLE默认值
    static const QMap<QString,int>          LIVE2DPARAMINIT_M;     //全部Live2D PARAM默认值
    static       QMap<QString,QString>      LIVE2DSTRING_M;        //全部Live2D STRING默认值
    static       QVector<ModelConfigItem>   LIVE2DMODELCONFIG_V;   //全部加载的Live2D配置信息
//    static       QList<QPair<QString,QString>   HISTORY;

    static const QString            SETCONFIG_WAY;         //设置配置路径
    static const QString            OUTPUT_WAV_WAY;        //音频文件输出路径
    static const QString            CHARACTER_CONFIG_WAY;  //角色扮演配置文件路径
    static const QString            CHATGPT_DEMO_WAY;      //chatgptEXE路径
    static const QString            CHATGPT_QUESTION_WAY;  //chatgptQUESTION路径
    static const QString            CHATGPT_KEY_WAY;       //CHATGPT_key路径
    static const QString            CHATGPT_BASEAPI_WAY;   //CHATGPT_baseapi路径
    static const QString            BAIDU_APPID_WAY;       //百度翻译APPID文件路径
    static const QString            BAIDU_KEY_WAY;         //百度翻译KEY文件路径
    static const QString            XFXH_APPID_WAY;        //讯飞星火APPID文件路径
    static const QString            XFXH_KEY_WAY;          //讯飞星火KEY文件路径
    static const QString            XFXH_SECRET_WAY;       //讯飞星火SECRET文件路径
    static const QString            XFXH_QUESTION_WAY;     //讯飞星火QUESTION路径
    static const QString            XFXH_DEMO_WAY;         //讯飞星火EXE路径
    static const QString            UNITY_DEMO_WAY;        //Unity Live2D EXE路径
    static const QString            UNITY_DEMO_WORK_WAY;       //Unity 工作目录
    static const QString            UNITY_STARTMODELPATH_WAY;  //Unity 模型文件加载路径
    static const QString            UNITY_MODELLIST_WAY;       //Unity Live 2D路径列表
    static const QString            UNITY_MODELCONFIGLIST_WAY; //Unity 模型文件配置加载路径
    static const QString            HISTORY_WAY;               //未归档Chat历史记录

    static QString                  CHATGPT_KEY;           //配置CHATGPT_key(need file)
    static QString                  CHATGPT_BASEAPI;       //配置CHATGPT_baseapi(need file)
    static QString                  URL_ADDRESS;           //VITS Url地址
    static QString                  URL_PORT;              //VITS Url端口
    static QString                  BAIDU_APID;            //百度翻译APPID (need file)
    static QString                  BAIDU_KEY;             //百度翻译开KEY (need file)
    static QString                  XFXH_APPID;            //讯飞星火APPID (need file)
    static QString                  XFXH_KEY;              //讯飞星火KEY   (need file)
    static QString                  XFXH_SECRET;           //讯飞星火SECRET(need file)
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
    static int                      SOUND_ID;              //音频播放ID


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
    static void init_CHATGPT_KEY();
    static void init_CHATGPT_BASEAPI();
    static void init_BAIDU_APPID();
    static void init_BAIDU_KEY();
    static void init_XFXH_APPID();
    static void init_XFXH_KEY();
    static void init_XFXH_SECRET();
    static void init_LIVE2DMODELCONFIG_V();
    static void init_HISTORY();

private:
    //修改文件配置
    static void output_CHATGPT_KEY(const QString& str);
    static void output_CHATGPT_BASEAPI(const QString& str);
    static void output_BAIDU_APPID(const QString& str);
    static void output_BAIDU_KEY(const QString& str);
    static void output_XFXH_APPID(const QString& str);
    static void output_XFXH_KEY(const QString& str);
    static void output_XFXH_SECRET(const QString& str);
    static void output_ALLSETCONFIG(const QJsonObject& js);
    static void output_LIVE2DMODELCONFIG_V(QVector<ModelConfigItem>& modV);


public:
    //获取路径信息
    static const QString get_SETCONFIG_WAY();
    static const QString get_OUTPUT_WAV_WAY();
    static const QString get_CHARACTER_CONFIG_WAY();
    static const QString get_CHATGPT_DEMO_WAY();
    static const QString get_CHATGPT_QUESTION_WAY();
    static const QString get_CHATGPT_KEY_WAY();
    static const QString get_CHATGPT_BASEAPI_WAY();
    static const QString get_BAIDU_APID_WAY();
    static const QString get_BAIDU_KEY_WAY();
    static const QString get_XFXH_APPID_WAY();
    static const QString get_XFXH_KEY_WAY();
    static const QString get_XFXH_SECRET_WAY();
    static const QString get_XFXH_QUESTION_WAY();
    static const QString get_XFXH_DEMO_WAY();
    static const QString get_UNITY_DEMO_WAY();
    static const QString get_UNITY_DEMO_WORK_WAY();
    static const QString get_UNITY_STARTMODELPATH_WAY();
    static const QString get_UNITY_MODELLIST_WAY();
    static const QString get_UNITY_MODELCONFIGLIST_WAY();
    static const QString get_HISTORY_WAY();

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
    //获取配置信息
    static const QString get_CHATGPT_KEY();
    static const QString get_CHATGPT_BASEAPI();
    static const QString get_CHATGPT_QUESTION();
    static const QString get_URL_ADDRESSS();
    static const QString get_URL_PATH();
    static const QString get_URL_ADDRESS_ALL();
    static const QString get_CHARACTER_CONFIG();
    static const QString get_BAIDU_APID();
    static const QString get_BAIDU_KEY();
    static const QString get_XFXH_APPID();
    static const QString get_XFXH_KEY();
    static const QString get_XFXH_SECRET();
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
    static int           get_SOUND_ID();
public:
    //设置配置信息
    static void          set_CHATGPT_KEY(const QString& str);
    static void          set_CHATGPT_BASEAPI(const QString& str);
    static void          set_CHATGPT_QUESTION(const QString& str);
    static void          set_URL_ADDRESS(const QString& str);
    static void          set_URL_PORT(const QString& str);
    static void          set_CHARACTER_CONFIG(const QString& str);
    static void          set_BAIDU_APID(const QString& str);
    static void          set_BAIDU_KEY(const QString& str);
    static void          set_XFXH_APPID(const QString& str);
    static void          set_XFXH_KEY(const QString& str);
    static void          set_XFXH_SECRET(const QString& str);
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
    static void          set_SOUND_ID(int id);
    static void          set_ALLSETCONFIG();


};

#endif // CONFIG_H


