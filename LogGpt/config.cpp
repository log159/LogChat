#include "config.h"


QVector<ModelConfigItem>   Config::LIVE2DMODELCONFIG_V    ={};


QVector<ModelConfigItem> Config::get_LIVE2DMODELCONFIG_V()
{
    return Config::LIVE2DMODELCONFIG_V;
}

void Config::init()
{
    init_LIVE2DMODELCONFIG_V();
}

QMap<QString, QString> Config::parseJsonToQMap(const QString &jsonString) {
    QMap<QString, QString> resultMap;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());

    if (!jsonDoc.isObject()) {
        qWarning() << "Invalid JSON object";
        return resultMap;
    }
    QJsonObject jsonObj = jsonDoc.object();

    for (QJsonObject::const_iterator it = jsonObj.constBegin(); it != jsonObj.constEnd(); ++it) {
        QString key = it.key();
        QString value = it.value().toString();
        resultMap.insert(key, value);
    }

    return resultMap;
}

void Config::init_LIVE2DMODELCONFIG_V()
{
    QString modelListStr=ConfigFileIO::getFileAllInformation(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::UNITY_MODELCONFIGLIST_WAY));

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
        ModelConfigItem modelConfigItem;
        modelConfigItem.setModelId(keyValueMap["model_id"].toInt());
        modelConfigItem.setModelName(keyValueMap["model_name"]);
        modelConfigItem.setFilePath(keyValueMap["file_path"]);
        modelConfigItem.setLookEnable(bool(keyValueMap["look_enable"].toInt()));
        modelConfigItem.setTopApha(keyValueMap["win_topapha"].toInt());
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
                .arg("win_topapha").arg(QString::number(int(dataModV[i].getTopApha())))
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

    ConfigFileIO::setFileInformation(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::UNITY_MODELCONFIGLIST_WAY),data);

}

const ::IKS Config::get_IKS(const ::EnIks &iks)
{
    return ConfigFileIO::getIksConfig(iks);
}

const QString Config::get_URL(const ::EnUrl &urlName)
{
    return ConfigFileIO::getUrlConfig(urlName);
}

const QString Config::get_VITS_URL()
{
   QString str = QString("http://"
                   +Config::get_USER(::EnUser::VITS_URL_ADDRESS)+":"
                   +Config::get_USER(::EnUser::VITS_URL_PORT)
                   +"/voice/"
                   +VITS_ALL_V.at(Config::get_USER(::EnUser::VITS_ID).toInt())
                   +"?text=%1&id="
                   +QString::number(Config::get_USER(::EnUser::SPEAKER_ID).toInt())
                   );
   if(VITS_ALL_V.at(Config::get_USER(::EnUser::VITS_ID).toInt()).compare("w2v2-vits")==0){
       str+=QString("&emotion="+QString::number(Config::get_USER(::EnUser::EMOTION_ID).toInt()));
   }
   return str;
}

const QString Config::get_UNITY_STARTMODELPATH()
{
    return ConfigFileIO::getFileInformation(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::UNITY_STARTMODELPATH_WAY));
}

const QString Config::get_CHARACTERCONFIG()
{
    QString username = Config::get_USER(::EnUser::USERNAME);
    QString charactername = Config::get_USER(::EnUser::CHARACTERNAME);

    QString character_str= Config::get_USER(::EnUser::CHARACTER_CONFIG);

    character_str.replace("{{user}}",username);
    character_str.replace("{{char}}",charactername);

    return character_str;
}

const QString Config::get_USER(const ::EnUser &key)
{
    return ConfigFileIO::getUserConfig(key);
}

void Config::set_IKS(const ::EnIks &iks, const QString &id, const QString &key, const QString &secret)
{
    ConfigFileIO::setIksConfig(iks,id,key,secret);
}

void Config::set_URL(const ::EnUrl &urlName, const QString &url)
{
    ConfigFileIO::setUrlConfig(urlName,url);
}

void Config::set_USER(const ::EnUser &key, const QString &value)
{
    ConfigFileIO::setUserConfig(key,value);
}

const QString Config::get_GPTSOVITS_URL()
{
    QString str="http://"+Config::get_USER(::EnUser::GPTSOVITS_URL_ADDRESS)+":"+
            Config::get_USER(::EnUser::GPTSOVITS_URL_PORT)+
            "?text=%1&text_language="+
            GPTSOVITS_LANGUAGE_V.at(Config::get_USER(::EnUser::GPTSOVITS_LANGUAGE).toInt());

    return str;
}
void Config::set_XFXH_QUESTION(const QString &str)
{
    ConfigFileIO::setFileInformation(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::XFXH_QUESTION_WAY),str);
}

void Config::set_UNITY_STARTMODELPATH(const QString &str)
{
    ConfigFileIO::setFileInformation(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::UNITY_STARTMODELPATH_WAY),str);
}

void Config::set_LIVE2DMODELCONFIG_V(QVector<ModelConfigItem> &modV)
{
    Config::LIVE2DMODELCONFIG_V.clear();
    Config::LIVE2DMODELCONFIG_V=modV;
    output_LIVE2DMODELCONFIG_V(modV);
}
