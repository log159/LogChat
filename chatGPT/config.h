#ifndef CONFIG_H
#define CONFIG_H

#include <QCoreApplication>
#include <QString>
#include <QDateTime>

#include "singletonbase.h"

class Config:public SingletonBase{
private:
    static const QString URL_ADDRESS;      //Url地址
    static const QString PY_INTERPRETER;   //python解释器路径
    static const QString PY_CHAT_SCRIPT;   //openai脚本路径
    static const QString OUTPUT_WAV_WAY;   //音频文件输出路径
public:
    static const QString get_URL_ADDRESS();
    static const QString get_PY_INTERPRETER();
    static const QString get_PY_CHAT_SCRIPT();
    static const QString get_OUTPUT_WAV_WAY();

};

#endif // CONFIG_H


