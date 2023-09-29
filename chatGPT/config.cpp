#include "config.h"

const QString Config::URL_ADDRESS       ="http://127.0.0.1:23456/voice/vits?text=%1&id=0";  //Url地址
const QString Config::PY_INTERPRETER    ="/python/python.exe";                              //python解释器路径
const QString Config::PY_CHAT_SCRIPT    ="/openpy/qtopenai.py";                             //openai脚本路径
const QString Config::OUTPUT_WAV_WAY    ="/wav/%1.wav";                                     //音频文件输出路径


const QString Config::get_URL_ADDRESS()
{
    return Config::URL_ADDRESS;
}

const QString Config::get_PY_INTERPRETER()
{
    return QCoreApplication::applicationDirPath()+Config::PY_INTERPRETER;
}

const QString Config::get_PY_CHAT_SCRIPT()
{
    return QCoreApplication::applicationDirPath()+Config::PY_CHAT_SCRIPT;
}

const QString Config::get_OUTPUT_WAV_WAY()
{
    // 获取当前时间
    QDateTime now = QDateTime::currentDateTime();
    QString str="%1%2%3%4%5%6";
    int year = now.date().year();
    int month = now.date().month();
    int day = now.date().day();
    int hour = now.time().hour();
    int minute = now.time().minute();
    int second = now.time().second();
    str = str.arg(year).arg(month).arg(day).arg(hour).arg(minute).arg(second);
    return QCoreApplication::applicationDirPath()+(Config::OUTPUT_WAV_WAY).arg(str);
}
