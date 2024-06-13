#include "config.h"


QVector<ModelConfigItem>   Config::LIVE2DMODELCONFIG_V    ={};



void Config::init()
{
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

void Config::init_LIVE2DMODELCONFIG_V()
{
    QString modelListStr=getFileAllInformation(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::UNITY_MODELCONFIGLIST_WAY));

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



void Config::output_ALLSETCONFIG(const QJsonObject &js)
{
    Config::setFileInformation(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::SETCONFIG_WAY),js);
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

    setFileInformation(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::UNITY_MODELCONFIGLIST_WAY),data);

}

QVector<QString> Config::get_VITS_MODEL_V()
{
    return ::VITS_MODEL_V;
}

QVector<QString> Config::get_VITS_ALL_V()
{
    return ::VITS_ALL_V;
}

QVector<QString> Config::get_LANGUAGE_V()
{
    return ::LANGUAGE_V;
}

QVector<QString> Config::get_CHATGPT_MODEL_V()
{
    return ::CHATGPT_MODEL_V;
}

QVector<QString> Config::get_XFXH_MODEL_V()
{
    return ::XFXH_MODEL_V;
}

QVector<ModelConfigItem> Config::get_LIVE2DMODELCONFIG_V()
{
    return Config::LIVE2DMODELCONFIG_V;
}

QMap<QString, bool> Config::get_LIVE2DENABLEINIT_M()
{
    return ::LIVE2DENABLEINIT_M;
}

QMap<QString, int> Config::get_LIVE2DPARAMINIT_M()
{
    return ::LIVE2DPARAMINIT_M;
}

QMap<QString, QString> Config::get_LIVE2DSTRING_M()
{
    return ::LIVE2DSTRING_M;
}

const ::IKS Config::get_IKS(const ::EnIks &iks)
{
    return ConfigFileIO::getIksConfig(iks);
}

const QString Config::get_URL(const ::EnUrl &urlName)
{
    return ConfigFileIO::getUrlConfig(urlName);
}

const QString Config::get_URL_ADDRESS_ALL()
{
   QString str = QString("http://"
                   +Config::get_USER(::EnUser::VITS_URL_ADDRESS)+":"
                   +Config::get_USER(::EnUser::VITS_URL_PORT)
                   +"/voice/"
                   +Config::get_VITS_ALL_V().at(Config::get_USER(::EnUser::VITS_ID).toInt())
                   +"?text=%1&id="
                   +QString::number(Config::get_USER(::EnUser::SPEAKER_ID).toInt())
                   );
   if(Config::get_VITS_ALL_V().at(Config::get_USER(::EnUser::VITS_ID).toInt()).compare("w2v2-vits")==0){
       str+=QString("&emotion="+QString::number(Config::get_USER(::EnUser::EMOTION_ID).toInt()));
   }
   return str;
}

const QString Config::get_XFXH_QUESTION()
{
    return Config::getFileAllInformation(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::XFXH_QUESTION_WAY));
}

const QString Config::get_UNITY_STARTMODELPATH()
{
    return Config::getFileInformation(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::UNITY_STARTMODELPATH_WAY));
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
void Config::set_XFXH_QUESTION(const QString &str)
{
    Config::setFileInformation(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::XFXH_QUESTION_WAY),str);
}

void Config::set_UNITY_STARTMODELPATH(const QString &str)
{
    Config::setFileInformation(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::UNITY_STARTMODELPATH_WAY),str);
}

void Config::set_LIVE2DMODELCONFIG_V(QVector<ModelConfigItem> &modV)
{
    Config::LIVE2DMODELCONFIG_V.clear();
    Config::LIVE2DMODELCONFIG_V=modV;
    output_LIVE2DMODELCONFIG_V(modV);
}
