#include "config.h"

const QString Config::PY_INTERPRETER_WAY    ="/python/python.exe";                              //python解释器路径
const QString Config::PY_CHAT_SCRIPT_WAY    ="/openpy/qtopenai.py";                             //openai脚本路径
const QString Config::OUTPUT_WAV_WAY        ="/wav/%1.wav";                                     //音频文件输出路径
const QString Config::CHARACTER_CONFIG_WAY  ="/config/config.txt";                              //配置文件路径
const QString Config::OPENAI_KEY_PY_WAY     ="/openpy/key.py";                                  //openai_key py文件路径
const QString Config::BAIDU_APID_WAY        ="/baiduapi/ID.txt";                                //百度翻译账号文件路径
const QString Config::BAIDU_KEY_WAY         ="/baiduapi/KEY.txt";                               //百度翻译密匙文件路径

QString       Config::OPENAI_KEY            ="";                                                //配置openai_key(need file)
QString       Config::URL_PORT              ="23456";                                           //VITS Url地址
int           Config::MAX_SPEAK             =0;                                                 //上文联系最大保留
QString       Config::BAIDU_APID            ="";                                                //百度翻译开发账号(need file)
QString       Config::BAIDU_KEY             ="";                                                //百度翻译开发密匙(need file)
bool          Config::ENABLE_ROLE           =false;                                             //是否启用角色扮演
bool          Config::ENABLE_SOUND          =false;                                             //是否启用语音
bool          Config::ENABLE_BAIDUFANYI     =false;                                             //是否启用百度翻译
bool          Config::ENABLE_LATERLANGUAGE  =false;                                             //是否启用翻译后的语言用来显示

QPair<QString,QString>   Config::LANGUAGE_FROM_TO   =QPair<QString,QString>("auto","jp");       //sound语言转换 默认from auto to jp

void Config::init()
{
    init_OPENAI_KEY();
    init_BAIDU_APID();
    init_BAIDU_KEY();
}

void Config::init_OPENAI_KEY()
{
    QFile file(get_OPENAI_KEY_PY_WAY());
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return;
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString read_str = in.readLine();
    // 使用正则表达式匹配目标字符串
    QRegularExpression regex("mykey=\"(.*?)\"");
    QRegularExpressionMatch match = regex.match(read_str);
    QString extractedString="";
    if (match.hasMatch()) {
         extractedString= match.captured(1);
    } else {
    }
    file.close();

    Config::OPENAI_KEY=extractedString;
}

void Config::init_BAIDU_APID()
{
    QFile file(get_BAIDU_APID_WAY());
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return;
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString read_str = in.readLine();
    file.close();
    Config::BAIDU_APID=read_str;
}

void Config::init_BAIDU_KEY()
{
    QFile file(get_BAIDU_KEY_WAY());
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return;
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString read_str = in.readLine();
    file.close();
    Config::BAIDU_KEY=read_str;
}

void Config::output_OPENAI_KEY(const QString &str)
{
    QFile file(get_OPENAI_KEY_PY_WAY());
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        return;
    }
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out<<"mykey=\""<<str<<"\"";
    file.close();

}

void Config::output_BAIDU_APID(const QString &str)
{
    QFile file(get_BAIDU_APID_WAY());
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        return;
    }
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out<<str;
    file.close();
}

void Config::output_BAIDU_KEY(const QString &str)
{
    QFile file(get_BAIDU_KEY_WAY());
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        return;
    }
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out<<str;
    file.close();
}

const QString Config::get_PY_INTERPRETER_WAY()
{
    return QCoreApplication::applicationDirPath()+Config::PY_INTERPRETER_WAY;
}

const QString Config::get_PY_CHAT_SCRIPT_WAY()
{
    return QCoreApplication::applicationDirPath()+Config::PY_CHAT_SCRIPT_WAY;
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

const QString Config::get_CHARACTER_CONFIG_WAY()
{
    return QCoreApplication::applicationDirPath()+Config::CHARACTER_CONFIG_WAY;
}

const QString Config::get_OPENAI_KEY_PY_WAY()
{
    return QCoreApplication::applicationDirPath()+Config::OPENAI_KEY_PY_WAY;
}

const QString Config::get_BAIDU_APID_WAY()
{
    return  QCoreApplication::applicationDirPath()+Config::BAIDU_APID_WAY;
}

const QString Config::get_BAIDU_KEY_WAY()
{
    return  QCoreApplication::applicationDirPath()+Config::BAIDU_KEY_WAY;
}

const QString Config::get_OPENAI_KEY()
{
    return Config::OPENAI_KEY;
}

const QString Config::get_URL_PATH()
{
    return Config::URL_PORT;
}
const QString Config::get_URL_ADDRESS()
{
    return QString("http://127.0.0.1:"+Config::URL_PORT+"/voice/vits?text=%1&id=0");
}
void Config::set_MAX_SPEAK(const int &num)
{
    if(num<=0){Config::MAX_SPEAK=0;}
    if(num>=50){Config::MAX_SPEAK=50;}
    else {Config::MAX_SPEAK=num;}
}


int Config::get_MAX_SPEAK()
{
    return Config::MAX_SPEAK;
}

const QString Config::get_BAIDU_APID()
{
    return Config::BAIDU_APID;
}

const QString Config::get_BAIDU_KEY()
{
    return  Config::BAIDU_KEY;
}

const QString Config::get_CHARACTER_CONFIG()
{
    //读取角色配置信息
    QFile file(Config::get_CHARACTER_CONFIG_WAY());
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return QString("你好");
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString fileAll=in.readAll();
    file.close();
    return  fileAll;
}

bool Config::get_ENABLE_ROLE()
{
    return Config::ENABLE_ROLE;
}

bool Config::get_ENABLE_SOUND()
{
    return Config::ENABLE_SOUND;
}

bool Config::get_ENABLE_BAIDUFANYI()
{
    return Config::ENABLE_BAIDUFANYI;
}

bool Config::get_ENABLE_LATERLANGUAGE()
{
    return Config::ENABLE_LATERLANGUAGE;
}

const QPair<QString, QString> Config::get_LANGUAGE_FROM_TO()
{
    return Config::LANGUAGE_FROM_TO;
}

void Config::set_OPENAI_KEY(const QString &str)
{
    output_OPENAI_KEY(str);
    Config::OPENAI_KEY=str;
}

void Config::set_URL_PORT(const QString &str)
{
    Config::URL_PORT=str;
}

void Config::set_BAIDU_APID(const QString &str)
{
    output_BAIDU_APID(str);
    Config::BAIDU_APID=str;
}

void Config::set_BAIDU_KEY(const QString &str)
{
    output_BAIDU_KEY(str);
    Config::BAIDU_KEY=str;
}

void Config::set_CHARACTER_CONFIG(const QString &str)
{
    QFile file(Config::get_CHARACTER_CONFIG_WAY());
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        return;
    }
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out<<str;
    file.close();
}

void Config::set_ENABLE_ROLE(const bool &bo)
{
    Config::ENABLE_ROLE=bo;
}

void Config::set_ENABLE_SOUND(const bool &bo)
{
    Config::ENABLE_SOUND=bo;
}

void Config::set_ENABLE_BAIDUFANYI(const bool &bo)
{
    Config::ENABLE_BAIDUFANYI=bo;
}

void Config::set_ENABLE_LATERLANGUAGE(const bool &bo)
{
    Config::ENABLE_LATERLANGUAGE=bo;
}

void Config::set_LANGUAGE_FROM_TO(const QPair<QString, QString> &pair)
{
    Config::LANGUAGE_FROM_TO.first=pair.first;
    Config::LANGUAGE_FROM_TO.second=pair.second;
}
