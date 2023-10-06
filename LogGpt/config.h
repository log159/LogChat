#ifndef CONFIG_H
#define CONFIG_H

#include <QCoreApplication>
#include <QString>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QPair>
#include <QDebug>
#include <QRegularExpression>

#include "singletonbase.h"

class Config:public SingletonBase{
private:
    static const QString            PY_INTERPRETER_WAY;    //python解释器路径
    static const QString            PY_CHAT_SCRIPT_WAY;    //openai脚本路径
    static const QString            OUTPUT_WAV_WAY;        //音频文件输出路径
    static const QString            CHARACTER_CONFIG_WAY;  //角色扮演配置文件路径
    static const QString            OPENAI_KEY_PY_WAY;     //openai_key py文件路径
    static const QString            BAIDU_APID_WAY;        //百度翻译账号文件路径
    static const QString            BAIDU_KEY_WAY;         //百度翻译密匙文件路径

    static QString                  OPENAI_KEY;            //配置openai_key(need file)
    static QString                  URL_PORT;              //VITS Url地址
    static int                      MAX_SPEAK;             //上文联系最大保留
    static QString                  BAIDU_APID;            //百度翻译开发账号(need file)
    static QString                  BAIDU_KEY;             //百度翻译开发密匙(need file)
    static bool                     ENABLE_ROLE;           //是否启用角色扮演
    static bool                     ENABLE_SOUND;          //是否启用语音
    static bool                     ENABLE_BAIDUFANYI;     //是否启用百度翻译
    static bool                     ENABLE_LATERLANGUAGE;  //是否启用翻译后的语言用来显示
    static QPair<QString,QString>   LANGUAGE_FROM_TO;      //sound语言转换 默认from auto to jp
public:
    //初始化
    static void init();
private:
    static void init_OPENAI_KEY();
    static void init_BAIDU_APID();
    static void init_BAIDU_KEY();
private:
    //修改文件配置
    static void output_OPENAI_KEY(const QString& str);
    static void output_BAIDU_APID(const QString& str);
    static void output_BAIDU_KEY(const QString& str);

public:
    //获取路径信息
    static const QString get_PY_INTERPRETER_WAY();
    static const QString get_PY_CHAT_SCRIPT_WAY();
    static const QString get_OUTPUT_WAV_WAY();
    static const QString get_CHARACTER_CONFIG_WAY();
    static const QString get_OPENAI_KEY_PY_WAY();
    static const QString get_BAIDU_APID_WAY();
    static const QString get_BAIDU_KEY_WAY();

public:
    //获取配置信息
    static const QString get_OPENAI_KEY();
    static const QString get_URL_PATH();
    static const QString get_URL_ADDRESS();
    static int           get_MAX_SPEAK();
    static const QString get_BAIDU_APID();
    static const QString get_BAIDU_KEY();
    static const QString get_CHARACTER_CONFIG();
    static bool          get_ENABLE_ROLE();
    static bool          get_ENABLE_SOUND();
    static bool          get_ENABLE_BAIDUFANYI();
    static bool          get_ENABLE_LATERLANGUAGE();
    static const QPair<QString,QString> get_LANGUAGE_FROM_TO();
public:
    //设置配置信息
    static void          set_OPENAI_KEY(const QString& str);
    static void          set_URL_PORT(const QString& str);
    static void          set_MAX_SPEAK(const int& num);
    static void          set_BAIDU_APID(const QString& str);
    static void          set_BAIDU_KEY(const QString& str);
    static void          set_CHARACTER_CONFIG(const QString& str);
    static void          set_ENABLE_ROLE(const bool& bo);
    static void          set_ENABLE_SOUND(const bool& bo);
    static void          set_ENABLE_BAIDUFANYI(const bool& bo);
    static void          set_ENABLE_LATERLANGUAGE(const bool& bo);
    static void          set_LANGUAGE_FROM_TO(const QPair<QString,QString>& pair);

};

#endif // CONFIG_H

