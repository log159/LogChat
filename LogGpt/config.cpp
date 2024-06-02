#include "config.h"

const QVector<QString>   Config::VITS_ALL_V     ={"vits","bert-vits2","w2v2-vits"};
const QVector<QString>   Config::LANGUAGE_V     ={"auto","jp","zh","en","yue","wyw","cht"};
const QVector<QString>   Config::CHATGPT_MODEL_V={"gpt-3.5-turbo"};
const QVector<QString>   Config::XFXH_MODEL_V   ={"general","generalv2","generalv3"};
const QMap<QString,bool>  Config::LIVE2DENABLEINIT_M   ={
    {"look_enable",true},
    {"top_enable",true}

};
const QMap<QString,int>  Config::LIVE2DPARAMINIT_M= {
    {"model_size",300},
    {"model_x",0},
    {"model_y",0},
    {"model_rx",0},
    {"model_ry",0},
    {"model_rz",0},
    {"mouse_speed",15},
    {"eye_time",250},
    {"eye_deviation",200},
    {"eye_speed",1000},
    {"audio_add",1000},
    {"audio_smooth",100}
};
QMap<QString,QString>   Config::LIVE2DSTRING_M={
    {"model_name","null"},
    {"file_path","null"},
    {"model_description","null"}

};
      QVector<ModelConfigItem>   Config::LIVE2DMODELCONFIG_V    ={};
const QString Config::SETCONFIG_WAY         ="/config/setconfig.json";
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
int           Config::CHATGPT_MODEL_ID      =0;                                                 //ChatGpt模型ID
int           Config::VITS_ID               =0;                                                 //vits模型ID
int           Config::SPEAKER_ID            =0;                                                 //讲述人ID
int           Config::EMOTION_ID            =0;                                                 //情感控制ID
int           Config::BAIDU_FROM_ID         =0;                                                 //原语种ID
int           Config::BAIDU_TO_ID           =1;                                                 //翻译后语种ID
int           Config::RESERVE_LONG          =10;                                                //上下文保留最大长度
int           Config::SOUND_ID              =0;                                                 //音频播放ID

void Config::init()
{
    init_ALLSETCONFIG();
    init_CHATGPT_KEY();
    init_CHATGPT_BASEAPI();
    init_BAIDU_APPID();
    init_BAIDU_KEY();
    init_XFXH_APPID();
    init_XFXH_KEY();
    init_XFXH_SECRET();
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

void Config::setFileInformation(const QString &path, const QJsonObject &js)
{
    // Convert the JSON object to a document
      QJsonDocument doc(js);
      QString jsonString = doc.toJson(QJsonDocument::Indented);

      // Define the file path
      QString filePath = path;

      // Open a file for writing
      QFile file(filePath);
      if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
          qDebug() << "Failed to open file for writing.";
      }
      QTextStream out(&file);
      out << jsonString;

      file.close();

}

void Config::init_ALLSETCONFIG()
{

    QString jsonString=Config::getFileAllInformation(Config::get_SETCONFIG_WAY());
    jsonString.remove('\t');
    jsonString.remove('\r');
    jsonString.remove('\n');
    jsonString.remove(' ');

    QMap<QString, QString> resultMap = Config::parseJsonToQMap(jsonString);

    // Print the QMap content
    for (auto it = resultMap.constBegin(); it != resultMap.constEnd(); ++it) {

        if(it.key()=="baidu_from")
        {
            Config::set_BAIDU_FROM_ID(it.value().toInt());
        }
        else if (it.key()=="baidu_to") {
            Config::set_BAIDU_TO_ID(it.value().toInt());
        }
        else if (it.key()=="chatgpt_model") {
//            gpt-3.5-turbo //暂时只有gpt-3.5-turbo了
            Config::set_CHATGPT_MODEL_ID(it.value().toInt());
        }
        else if (it.key()=="enable_baidu") {
            Config::set_ENABLE_BAIDUFANYI(static_cast<bool>(it.value().toInt()));
        }
        else if (it.key()=="enable_baidushow") {
            Config::set_ENABLE_LATERLANGUAGE(static_cast<bool>(it.value().toInt()));

        }
        else if (it.key()=="enable_character") {
            Config::set_ENABLE_ROLE(static_cast<bool>(it.value().toInt()));
        }
        else if (it.key()=="enable_vits") {
            Config::set_ENABLE_SOUND(static_cast<bool>(it.value().toInt()));
        }
        else if (it.key()=="llm_change") {
            Config::set_LLM_MODEL_ID(it.value().toInt());
        }
        else if (it.key()=="vits_address") {
            Config::set_URL_ADDRESS(it.value());
        }
        else if (it.key()=="vits_emotion") {
            Config::set_EMOTION_ID(it.value().toInt());
        }
        else if (it.key()=="vits_id") {
            Config::set_VITS_ID(it.value().toInt());
        }
        else if (it.key()=="vits_port") {
            Config::set_URL_PORT(it.value());
        }
        else if (it.key()=="vits_speaker") {
            Config::set_SPEAKER_ID(it.value().toInt());
        }
        else if (it.key()=="xfxh_model") {
            Config::set_XFXH_MODEL_ID(it.value().toInt());
        }

    }

}
QMap<QString, QString> Config::parseJsonToQMap(const QString &jsonString) {
    QMap<QString, QString> resultMap;

    // Step 1: Parse JSON string to QJsonDocument
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());

    // Step 2: Check if the document is a valid JSON object
    if (!jsonDoc.isObject()) {
        qWarning() << "Invalid JSON object";
        return resultMap;
    }

    // Step 3: Get the QJsonObject
    QJsonObject jsonObj = jsonDoc.object();

    // Step 4: Iterate through the QJsonObject and save to QMap
    for (QJsonObject::const_iterator it = jsonObj.constBegin(); it != jsonObj.constEnd(); ++it) {
        QString key = it.key();
        QString value = it.value().toString();
        resultMap.insert(key, value);
    }

    return resultMap;
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

void Config::init_LIVE2DMODELCONFIG_V()
{
    QString modelListStr=getFileAllInformation(Config::get_UNITY_MODELCONFIGLIST_WAY());

    QString handleStr=modelListStr;
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

        // 按行拆分文件内容
        QStringList lines = modelStrV.at(i).split('\n', QString::SkipEmptyParts);
        // 创建一个 QMap 以存储键值对
        QMap<QString, QString> keyValueMap;

        for (const QString& line : lines) {
            int index=line.indexOf(QChar(':'));
            if(index!=-1){
                QString key=line.mid(0,index);
                QString value=line.mid(index+1);
                value.chop(1);
                keyValueMap[key]=value;
            }
        }
//        // 输出提取的键值对
//        QMapIterator<QString, QString> it(keyValueMap);
//        while (it.hasNext()) {
//            it.next();
//            qDebug() << it.key() << ":" << it.value();
//        }
        ModelConfigItem modelConfigItem;
        modelConfigItem.setModelId(keyValueMap["model_id"].toInt());
        modelConfigItem.setModelName(keyValueMap["model_name"]);
        modelConfigItem.setFilePath(keyValueMap["file_path"]);
        modelConfigItem.setLookEnable(bool(keyValueMap["look_enable"].toInt()));
        modelConfigItem.setTopEnable(bool(keyValueMap["top_enable"].toInt()));
        modelConfigItem.setModelSize(keyValueMap["model_size"].toInt());
        modelConfigItem.setModelX(keyValueMap["model_x"].toInt());
        modelConfigItem.setModelY(keyValueMap["model_y"].toInt());
        modelConfigItem.setMouseSpeed(keyValueMap["mouse_speed"].toInt());
        modelConfigItem.setEyeTime(keyValueMap["eye_time"].toInt());
        modelConfigItem.setEyeDeviation(keyValueMap["eye_deviation"].toInt());
        modelConfigItem.setEyeSpeed(keyValueMap["eye_speed"].toInt());
        modelConfigItem.setAudioAdd(keyValueMap["audio_add"].toInt());
        modelConfigItem.setAudioSmooth(keyValueMap["audio_smooth"].toInt());
        modelConfigItem.setModelDescription(keyValueMap["model_description"]);

        modelConfigItem.setModelId(i);//id对齐

        Config::LIVE2DMODELCONFIG_V.push_back(modelConfigItem);

//        ModelConfigItem::printInformation(modelConfigItem);
        qDebug()<<modelConfigItem.getFilePath();
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

void Config::output_ALLSETCONFIG(const QJsonObject &js)
{
    Config::setFileInformation(get_SETCONFIG_WAY(),js);
}

void Config::output_LIVE2DMODELCONFIG_V(QVector<ModelConfigItem>& modV)
{
    QVector<ModelConfigItem> dataModV(modV);
    QString data="";
    for(int i=0;i<dataModV.size();++i){
        dataModV[i].setModelId(i);//id对齐
        QString dataItem=QString("{\n\t%1:%2,\n\t%3:%4,\n\t%5:%6,\n\t%7:%8,\n\t%9:%10,\n\t%11:%12,\n\t%13:%14,\n\t%15:%16,\n\t%17:%18,\n\t%19:%20,\n\t%21:%22,\n\t%23:%24,\n\t%25:%26,\n\t%27:%28,\n\t%29:%30,\n};\n");

        dataItem= dataItem.arg("model_id").arg(QString::number(dataModV[i].getModelId()))
                .arg("model_name").arg(dataModV[i].getModelName())
                .arg("file_path").arg(dataModV[i].getFilePath())
                .arg("look_enable").arg(QString::number(int(dataModV[i].getLookEnable())))
                .arg("top_enable").arg(QString::number(int(dataModV[i].getTopEnable())))
                .arg("model_size").arg(QString::number(int(dataModV[i].getModelSize())))
                .arg("model_x").arg(QString::number(int(dataModV[i].getModelX())))
                .arg("model_y").arg(QString::number(int(dataModV[i].getModelY())))
                .arg("mouse_speed").arg(QString::number(int(dataModV[i].getMouseSpeed())))
                .arg("eye_time").arg(QString::number(int(dataModV[i].getEyeTime())))
                .arg("eye_deviation").arg(QString::number(int(dataModV[i].getEyeDeviation())))
                .arg("eye_speed").arg(QString::number(int(dataModV[i].getEyeSpeed())))
                .arg("audio_add").arg(QString::number(int(dataModV[i].getAudioAdd())))
                .arg("audio_smooth").arg(QString::number(int(dataModV[i].getAudioSmooth())))
                .arg("model_description").arg(dataModV[i].getModelDescription());
        data+=dataItem;
    }
    data.chop(1);//丢弃最后的空格

    setFileInformation(Config::get_UNITY_MODELCONFIGLIST_WAY(),data);

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

const QString Config::get_SETCONFIG_WAY(){
    return QCoreApplication::applicationDirPath()+Config::SETCONFIG_WAY;
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

QMap<QString, QString> Config::get_LIVE2DSTRING_M()
{
    return Config::LIVE2DSTRING_M;
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

int Config::get_CHATGPT_MODEL_ID()
{
    return Config::CHATGPT_MODEL_ID;
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

void Config::set_LIVE2DMODELCONFIG_V(QVector<ModelConfigItem> &modV)
{
    Config::LIVE2DMODELCONFIG_V.clear();
    Config::LIVE2DMODELCONFIG_V=modV;
    output_LIVE2DMODELCONFIG_V(modV);
}

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

void Config::set_CHATGPT_MODEL_ID(int id)
{
    Config::CHATGPT_MODEL_ID=id;
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

void Config::set_ALLSETCONFIG()
{
    QJsonObject json;

       // Add key-value pairs to the object
       json["vits_address"] = Config::get_URL_ADDRESSS();
       json["vits_port"] = Config::get_URL_PATH();
       json["vits_id"] = QString::number(Config::get_VITS_ID());
       json["vits_speaker"] = QString::number(Config::get_SPEAKER_ID());
       json["vits_emotion"] = QString::number(Config::get_EMOTION_ID());
       json["llm_change"] = QString::number(Config::get_LLM_MODEL_ID());
       json["chatgpt_model"] = QString::number(Config::get_CHATGPT_MODEL_ID());
       json["xfxh_model"] = QString::number(Config::get_XFXH_MODEL_ID());
       json["baidu_from"] = QString::number(Config::get_BAIDU_FROM_ID());
       json["baidu_to"] = QString::number(Config::get_BAIDU_TO_ID());
       json["enable_character"] = QString::number(Config::get_ENABLE_ROLE());
       json["enable_vits"] = QString::number((Config::get_ENABLE_SOUND()));
       json["enable_baidu"] = QString::number(Config::get_ENABLE_BAIDUFANYI());
       json["enable_baidushow"] = QString::number(Config::get_ENABLE_LATERLANGUAGE());


       Config::output_ALLSETCONFIG(json);

}

