#include "config.h"

const QVector<QString>   Config::VITS_ALL_V     ={"vits","bert-vits2","w2v2-vits"};
const QVector<QString>   Config::LANGUAGE_V     ={"auto","jp","zh","en"};
const QVector<QString>   Config::CHATGPT_MODEL_V={"gpt-3.5-turbo"};
const QVector<QString>   Config::XFXH_MODEL_V   ={"general","generalv2","generalv3"};
const QMap<QString,bool>  Config::LIVE2DENABLEINIT_M   ={
    {"look_enable",true},
    {"top_enable",true}

};
const QMap<QString,int>  Config::LIVE2DPARAMINIT_M= {
    {"model_size",300},
    {"mouse_speed",15},
    {"eye_time",250},
    {"eye_deviation",200},
    {"eye_speed",1000},
    {"audio_add",1000},
    {"audio_smooth",100}
};
      QVector<QString>           Config::LIVE2DMODEL_V          ={};
      QVector<ModelConfigItem>   Config::LIVE2DMODELCONFIG_V    ={};
const QString Config::OUTPUT_WAV_WAY        ="/wav/%1.wav";
const QString Config::CHARACTER_CONFIG_WAY  ="/config/config.txt";
const QString Config::CHATGPT_DEMO_WAY      ="/chatgptapi/dist/qtopenai.exe";
const QString Config::CHATGPT_QUESTION_WAY  ="/chatgptapi/dist/question.txt";
const QString Config::CHATGPT_KEY_WAY        ="/chatgptapi/dist/KEY.txt";
const QString Config::CHATGPT_BASEAPI_WAY    ="/chatgptapi/dist/APIBASE.txt";
const QString Config::BAIDU_APPID_WAY       ="/baiduapi/ID.txt";
const QString Config::BAIDU_KEY_WAY         ="/baiduapi/KEY.txt";
const QString Config::XFXH_APPID_WAY        ="/xfxhapi/ID.txt";
const QString Config::XFXH_KEY_WAY          ="/xfxhapi/KEY.txt";
const QString Config::XFXH_SECRET_WAY       ="/xfxhapi/SECRET.txt";
const QString Config::XFXH_QUESTION_WAY     ="/xfxhapi/question.txt";
const QString Config::XFXH_DEMO_WAY         ="/xfxhapi/demo.exe";
const QString Config::UNITY_DEMO_WAY        ="/unity2d/Live2D.exe";
const QString Config::UNITY_DEMO_WORK_WAY   ="/unity2d";
const QString Config::UNITY_STARTMODELPATH_WAY="/unity2d/model/STARTMODELPATH.txt";
const QString Config::UNITY_MODELLIST_WAY     ="/unity2d/model/MODELLIST.txt";
const QString Config::UNITY_MODELCONFIGLIST_WAY="/unity2d/model/MODELCONFIGLIST.txt";


QString       Config::CHATGPT_KEY            ="";                                                //配置CHATGPT_key(need file)
QString       Config::CHATGPT_BASEAPI        ="";                                                //配置CHATGPT_baseapi(need file)
QString       Config::URL_ADDRESS           ="127.0.0.1";                                       //VITS Url地址
QString       Config::URL_PORT              ="23456";                                           //VITS Url地址
QString       Config::BAIDU_APID            ="";                                                //百度翻译开发账号(need file)
QString       Config::BAIDU_KEY             ="";                                                //百度翻译开发密匙(need file)
QString       Config::XFXH_APPID            ="";                                                //讯飞星火APPID (need file)
QString       Config::XFXH_KEY              ="";                                                //讯飞星火KEY   (need file)
QString       Config::XFXH_SECRET           ="";                                                //讯飞星火SECRET(need file)
bool          Config::ENABLE_ROLE           =false;                                             //是否启用角色扮演
bool          Config::ENABLE_SOUND          =false;                                             //是否启用语音
bool          Config::ENABLE_BAIDUFANYI     =false;                                             //是否启用百度翻译
bool          Config::ENABLE_LATERLANGUAGE  =false;                                             //是否启用翻译后的语言用来显示
bool          Config::ENABLE_RESERVE        =false;                                             //是否保留上下文记忆

int           Config::LLM_MODEL_ID          =0;                                                 //LLM模型ID
int           Config::XFXH_MODEL_ID         =0;                                                 //讯飞星火模型ID
int           Config::VITS_ID               =0;                                                 //vits模型ID
int           Config::SPEAKER_ID            =0;                                                 //讲述人ID
int           Config::EMOTION_ID            =0;                                                 //情感控制ID
int           Config::BAIDU_FROM_ID         =0;                                                 //原语种ID
int           Config::BAIDU_TO_ID           =1;                                                 //翻译后语种ID
int           Config::RESERVE_LONG          =10;                                                //上下文保留最大长度
int           Config::SOUND_ID              =0;                                                 //音频播放ID

void Config::init()
{
    init_CHATGPT_KEY();
    init_CHATGPT_BASEAPI();
    init_BAIDU_APPID();
    init_BAIDU_KEY();
    init_XFXH_APPID();
    init_XFXH_KEY();
    init_XFXH_SECRET();
    init_LIVE2DMODEL_V();
    init_LIVE2DMODELCONFIG_V();
}

const QString Config::getFileInformation(const QString &path)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return {};
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString read_str = in.readLine();
    file.close();
    return read_str;
}

const QString Config::getFileAllInformation(const QString &path)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return {};
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString read_str = in.readAll();
    file.close();
    return read_str;
}

void Config::setFileInformation(const QString &path, const QString &str)
{
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        return;
    }
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out<<str;
    file.close();
}

void Config::init_CHATGPT_KEY()
{
    Config::CHATGPT_KEY=Config::getFileInformation(get_CHATGPT_KEY_WAY());
}

void Config::init_CHATGPT_BASEAPI()
{
    Config::CHATGPT_BASEAPI=Config::getFileInformation(get_CHATGPT_BASEAPI_WAY());
}

void Config::init_BAIDU_APPID()
{
    Config::BAIDU_APID=Config::getFileInformation(get_BAIDU_APID_WAY());
}

void Config::init_BAIDU_KEY()
{
    Config::BAIDU_KEY=Config::getFileInformation(get_BAIDU_KEY_WAY());
}

void Config::init_XFXH_APPID()
{
    Config::XFXH_APPID=Config::getFileInformation(get_XFXH_APPID_WAY());
}

void Config::init_XFXH_KEY()
{
    Config::XFXH_KEY=Config::getFileInformation(get_XFXH_KEY_WAY());
}

void Config::init_XFXH_SECRET()
{
    Config::XFXH_SECRET=Config::getFileInformation(get_XFXH_SECRET_WAY());
}

void Config::init_LIVE2DMODEL_V()
{
    QString modelListStr=getFileAllInformation(Config::get_UNITY_MODELLIST_WAY());
    QString str="";
    for(int i=0;i<modelListStr.size();++i){
        QChar ch=modelListStr.at(i);
        if(ch==QChar('[')){
        }
        else if(ch==QChar(']')){
            Config::LIVE2DMODEL_V.push_back(str);
            str="";
        }
        else {
            if(ch!=QChar('\n')){
                str+=ch;
            }
        }
    }
//    for(int i=0;i<Config::LIVE2DMODEL_V.size();++i){
//        qDebug()<<LIVE2DMODEL_V.at(i);
//    }

}

void Config::init_LIVE2DMODELCONFIG_V()
{
    QString modelListStr=getFileAllInformation(Config::get_UNITY_MODELCONFIGLIST_WAY());

    QString handleStr=modelListStr;
    handleStr.remove(QChar('\n'), Qt::CaseInsensitive);
    handleStr.remove(QChar('\t'), Qt::CaseInsensitive);
    modelListStr=handleStr;

    QVector<QString>modelStrV;
    int modelListId=0;

    for (int i=0;i<modelListStr.size();++i) {
        if(modelListId>=modelStrV.size()){
            modelStrV.push_back(QString());
        }
        modelStrV[modelListId]+=modelListStr[i];
        if(modelListStr[i]==QChar(';')){
            modelListId++;
        }
    }

    Config::LIVE2DMODELCONFIG_V.clear();

    for(int i=0;i<modelStrV.size();++i){
        const char* modelCharPtr=modelStrV[i].toStdString().data();
        int modelId;
        char modelName[1024];
        char filePath[1024];
        int lookEnable;
        int topEnable;
        int modelSize;
        int mouseSpeed;
        int eyeTime;
        int eyeDeviation;
        int eyeSpeed;
        int audioAdd;
        int audioSmooth;
        char modelDescription[4096];
        sscanf(modelCharPtr,"%*[(]%d%*[)]%*[{]%*[^:]%*[:]%[^,]%*[,]%*[^:]%*[:]%[^,]%*[,]%*[^:]%*[:]%d%*[,]%*[^:]%*[:]%d%*[,]%*[^:]%*[:]%d%*[,]%*[^:]%*[:]%d%*[,]%*[^:]%*[:]%d%*[,]%*[^:]%*[:]%d%*[,]%*[^:]%*[:]%d%*[,]%*[^:]%*[:]%d%*[,]%*[^:]%*[:]%d%*[,]%*[^:]%*[:]%[^}]",&modelId,modelName,&filePath,&lookEnable,&topEnable,&modelSize,&mouseSpeed,&eyeTime,&eyeDeviation,&eyeSpeed,&audioAdd,&audioSmooth,&modelDescription);

        ModelConfigItem modelConfigItem;
        modelConfigItem.setModelId(modelId);
        modelConfigItem.setModelName(modelName);
        modelConfigItem.setFilePath(filePath);
        modelConfigItem.setLookEnable(bool(lookEnable));
        modelConfigItem.setTopEnable(bool(topEnable));
        modelConfigItem.setModelSize(modelSize);
        modelConfigItem.setMouseSpeed(mouseSpeed);
        modelConfigItem.setEyeTime(eyeTime);
        modelConfigItem.setEyeDeviation(eyeDeviation);
        modelConfigItem.setEyeSpeed(eyeSpeed);
        modelConfigItem.setAudioAdd(audioAdd);
        modelConfigItem.setAudioSmooth(audioSmooth);
        modelConfigItem.setModelDescription(modelDescription);

        Config::LIVE2DMODELCONFIG_V.push_back(modelConfigItem);

//        ModelConfigItem::printInformation(modelConfigItem);
//        qDebug()<<endl;
    }



}

void Config::output_CHATGPT_KEY(const QString &str)
{
    Config::setFileInformation(get_CHATGPT_KEY_WAY(),str);
}

void Config::output_CHATGPT_BASEAPI(const QString &str)
{
    Config::setFileInformation(get_CHATGPT_BASEAPI_WAY(),str);
}

void Config::output_BAIDU_APPID(const QString &str)
{
    Config::setFileInformation(get_BAIDU_APID_WAY(),str);
}

void Config::output_BAIDU_KEY(const QString &str)
{
    Config::setFileInformation(get_BAIDU_KEY_WAY(),str);
}

void Config::output_XFXH_APPID(const QString &str)
{
    Config::setFileInformation(get_XFXH_APPID_WAY(),str);
}

void Config::output_XFXH_KEY(const QString &str)
{
    Config::setFileInformation(get_XFXH_KEY_WAY(),str);
}

void Config::output_XFXH_SECRET(const QString &str)
{
    Config::setFileInformation(get_XFXH_SECRET_WAY(),str);
}

void Config::output_LIVE2DMODEL_V(QVector<QString>& strV)
{
    QString data="";
    for (auto& val : strV) {
        data+="["+val+"]\n";
    }
    setFileInformation(get_UNITY_MODELLIST_WAY(),data);
}

//void Config::output_LIVE2DMODELCONFIG_V(QVector<ModelConfigItem> &strV)
//{

//}

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
const QString Config::get_CHATGPT_DEMO_WAY()
{
    return QCoreApplication::applicationDirPath()+Config::CHATGPT_DEMO_WAY;
}

const QString Config::get_CHATGPT_QUESTION_WAY()
{
    return QCoreApplication::applicationDirPath()+Config::CHATGPT_QUESTION_WAY;
}


const QString Config::get_CHATGPT_KEY_WAY()
{
    return QCoreApplication::applicationDirPath()+Config::CHATGPT_KEY_WAY;
}

const QString Config::get_CHATGPT_BASEAPI_WAY()
{
    return QCoreApplication::applicationDirPath()+Config::CHATGPT_BASEAPI_WAY;
}

const QString Config::get_BAIDU_APID_WAY()
{
    return  QCoreApplication::applicationDirPath()+Config::BAIDU_APPID_WAY;
}

const QString Config::get_BAIDU_KEY_WAY()
{
    return  QCoreApplication::applicationDirPath()+Config::BAIDU_KEY_WAY;
}

const QString Config::get_XFXH_APPID_WAY()
{
    return QCoreApplication::applicationDirPath()+Config::XFXH_APPID_WAY;
}

const QString Config::get_XFXH_KEY_WAY()
{
    return QCoreApplication::applicationDirPath()+Config::XFXH_KEY_WAY;
}

const QString Config::get_XFXH_SECRET_WAY()
{
    return QCoreApplication::applicationDirPath()+Config::XFXH_SECRET_WAY;
}

const QString Config::get_XFXH_QUESTION_WAY()
{
    return QCoreApplication::applicationDirPath()+Config::XFXH_QUESTION_WAY;
}

const QString Config::get_XFXH_DEMO_WAY()
{
    return QCoreApplication::applicationDirPath()+Config::XFXH_DEMO_WAY;
}

const QString Config::get_UNITY_DEMO_WAY()
{
    return QCoreApplication::applicationDirPath()+Config::UNITY_DEMO_WAY;
}

const QString Config::get_UNITY_DEMO_WORK_WAY()
{
    return  QCoreApplication::applicationDirPath()+Config::UNITY_DEMO_WORK_WAY;
}

const QString Config::get_UNITY_STARTMODELPATH_WAY()
{
    return QCoreApplication::applicationDirPath()+Config::UNITY_STARTMODELPATH_WAY;
}

const QString Config::get_UNITY_MODELLIST_WAY()
{
    return QCoreApplication::applicationDirPath()+Config::UNITY_MODELLIST_WAY;
}

const QString Config::get_UNITY_MODELCONFIGLIST_WAY()
{
    return QCoreApplication::applicationDirPath()+Config::UNITY_MODELCONFIGLIST_WAY;
}

QVector<QString> Config::get_VITS_ALL_V()
{
    return Config::VITS_ALL_V;
}

QVector<QString> Config::get_LANGUAGE_V()
{
    return Config::LANGUAGE_V;
}

QVector<QString> Config::get_CHATGPT_MODEL_V()
{
    return Config::CHATGPT_MODEL_V;
}

QVector<QString> Config::get_XFXH_MODEL_V()
{
    return Config::XFXH_MODEL_V;
}
QVector<QString> Config::get_LIVE2DMODEL_V(){

    return Config::LIVE2DMODEL_V;
}

QVector<ModelConfigItem> Config::get_LIVE2DMODELCONFIG_V()
{
    return Config::LIVE2DMODELCONFIG_V;
}

QMap<QString, bool> Config::get_LIVE2DENABLEINIT_M()
{
    return Config::LIVE2DENABLEINIT_M;
}

QMap<QString, int> Config::get_LIVE2DPARAMINIT_M()
{
    return Config::LIVE2DPARAMINIT_M;
}
const QString Config::get_CHATGPT_KEY()
{
    return Config::CHATGPT_KEY;
}

const QString Config::get_CHATGPT_BASEAPI()
{
    return Config::CHATGPT_BASEAPI;
}

const QString Config::get_CHATGPT_QUESTION()
{
    //读取角色配置信息
    QFile file(Config::get_CHATGPT_QUESTION_WAY());
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return QString("");
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString fileAll=in.readAll();
    file.close();
    return  fileAll;
}

const QString Config::get_URL_ADDRESSS()
{
    return Config::URL_ADDRESS;
}

const QString Config::get_URL_PATH()
{
    return Config::URL_PORT;
}
const QString Config::get_URL_ADDRESS_ALL()
{
   QString str = QString("http://"
                   +Config::URL_ADDRESS+":"
                   +Config::URL_PORT
                   +"/voice/"
                   +Config::get_VITS_ALL_V().at(Config::get_VITS_ID())
                   +"?text=%1&id="
                   +QString::number(Config::get_SPEAKER_ID())
                   );
   if(Config::get_VITS_ALL_V().at(Config::get_VITS_ID()).compare("w2v2-vits")==0){
       str+=QString("&emotion="+QString::number(Config::get_EMOTION_ID()));
   }
   return str;
}

const QString Config::get_BAIDU_APID()
{
    return Config::BAIDU_APID;
}

const QString Config::get_BAIDU_KEY()
{
    return  Config::BAIDU_KEY;
}

const QString Config::get_XFXH_APPID()
{
    return Config::XFXH_APPID;
}

const QString Config::get_XFXH_KEY()
{
    return Config::XFXH_KEY;
}

const QString Config::get_XFXH_SECRET()
{
    return Config::XFXH_SECRET;
}

const QString Config::get_CHARACTER_CONFIG()
{
    return Config::getFileAllInformation(Config::get_CHARACTER_CONFIG_WAY());
}

const QString Config::get_XFXH_QUESTION()
{
    return Config::getFileAllInformation(Config::get_XFXH_QUESTION_WAY());
}

const QString Config::get_UNITY_STARTMODELPATH()
{
    return Config::getFileInformation(Config::get_UNITY_STARTMODELPATH_WAY());
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

bool Config::get_ENABLE_RESERVE()
{
    return Config::ENABLE_RESERVE;
}

int Config::get_LLM_MODEL_ID()
{
    return Config::LLM_MODEL_ID;
}

int Config::get_XFXH_MODEL_ID()
{
    return Config::XFXH_MODEL_ID;
}
int Config::get_VITS_ID()
{
    return Config::VITS_ID;
}

int Config::get_SPEAKER_ID()
{
    return Config::SPEAKER_ID;
}

int Config::get_EMOTION_ID()
{
    return Config::EMOTION_ID;
}

int Config::get_BAIDU_FROM_ID()
{
    return Config::BAIDU_FROM_ID;
}

int Config::get_BAIDU_TO_ID()
{
    return Config::BAIDU_TO_ID;
}

int Config::get_RESERVE_LONG()
{
    return Config::RESERVE_LONG;
}

int Config::get_SOUND_ID()
{
    return Config::SOUND_ID;
}

void Config::set_CHATGPT_KEY(const QString &str)
{
    Config::output_CHATGPT_KEY(str);
    Config::CHATGPT_KEY=str;
}

void Config::set_CHATGPT_BASEAPI(const QString &str)
{
    Config::output_CHATGPT_BASEAPI(str);
    Config::CHATGPT_BASEAPI=str;
}

void Config::set_URL_ADDRESS(const QString &str)
{
    Config::URL_ADDRESS=str;
}

void Config::set_URL_PORT(const QString &str)
{
    Config::URL_PORT=str;
}

void Config::set_BAIDU_APID(const QString &str)
{
    Config::output_BAIDU_APPID(str);
    Config::BAIDU_APID=str;
}

void Config::set_BAIDU_KEY(const QString &str)
{
    Config::output_BAIDU_KEY(str);
    Config::BAIDU_KEY=str;
}

void Config::set_XFXH_APPID(const QString &str)
{
    Config::output_XFXH_APPID(str);
    Config::XFXH_APPID=str;
}

void Config::set_XFXH_KEY(const QString &str)
{
    Config::output_XFXH_KEY(str);
    Config::XFXH_KEY=str;
}

void Config::set_XFXH_SECRET(const QString &str)
{
    Config::output_XFXH_SECRET(str);
    Config::XFXH_SECRET=str;
}

void Config::set_CHARACTER_CONFIG(const QString &str)
{
    Config::setFileInformation(Config::get_CHARACTER_CONFIG_WAY(),str);
}

void Config::set_XFXH_QUESTION(const QString &str)
{
    Config::setFileInformation(Config::get_XFXH_QUESTION_WAY(),str);
}

void Config::set_UNITY_STARTMODELPATH(const QString &str)
{
    Config::setFileInformation(Config::get_UNITY_STARTMODELPATH_WAY(),str);
}

void Config::set_LIVE2DMODEL_V(QVector<QString> strV)
{
    Config::LIVE2DMODEL_V.clear();
    Config::LIVE2DMODEL_V=strV;
    output_LIVE2DMODEL_V(strV);
}

//void Config::set_LIVE2DMODELCONFIG_V(QVector<QString> strV)
//{
//    Config::LIVE2DMODELCONFIG_V.clear();
//    Config::LIVE2DMODELCONFIG_V=strV;
//    output_
//}

void Config::set_CHATGPT_QUESTION(const QString &str)
{
    Config::setFileInformation(Config::get_CHATGPT_QUESTION_WAY(),str);
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

void Config::set_ENABLE_RESERVE(const bool &bo)
{
    Config::ENABLE_RESERVE=bo;
}

void Config::set_LLM_MODEL_ID(int id)
{
    Config::LLM_MODEL_ID=id;
}

void Config::set_XFXH_MODEL_ID(int id)
{
    Config::XFXH_MODEL_ID=id;
}

void Config::set_VITS_ID(int id)
{
    Config::VITS_ID=id;
}

void Config::set_SPEAKER_ID(int id)
{
    Config::SPEAKER_ID=id;
}

void Config::set_EMOTION_ID(int id)
{
    Config::EMOTION_ID=id;
}

void Config::set_BAIDU_FROM_ID(int id)
{
    Config::BAIDU_FROM_ID=id;
}

void Config::set_BAIDU_TO_ID(int id)
{
    Config::BAIDU_TO_ID=id;
}

void Config::set_RESERVE_LONG(int id)
{
    Config::RESERVE_LONG=id;
}

void Config::set_SOUND_ID(int id)
{
    Config::SOUND_ID=id;
}

