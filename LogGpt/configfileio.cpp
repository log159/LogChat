#include "configfileio.h"

const QString           ConfigFileIO::NULLVALUE="";


const QString ConfigFileIO::getFileInformation(const QString &path)
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

const QString ConfigFileIO::getFileAllInformation(const QString &path)
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

void ConfigFileIO::setFileInformation(const QString &path, const QString &str)
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

void ConfigFileIO::setFileInformation(const QString &path, const QJsonObject &js)
{

      QJsonDocument doc(js);
      QString jsonString = doc.toJson(QJsonDocument::Indented);

      QString filePath = path;
      QFile file(filePath);
      if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
          qDebug() << "Failed to open file for writing.";
      }
      QTextStream out(&file);
      out << jsonString;

      file.close();

}

void ConfigFileIO::copyDirectory(const QString &sourceDir, const QString &destinationDir)
{
    QDir source(sourceDir);
    QDir destination(destinationDir);

    if (!destination.exists()) {
        destination.mkpath("."); // 创建目标目录
    }

    QFileInfoList files = source.entryInfoList(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs | QDir::Hidden | QDir::System);
    foreach (QFileInfo file, files) {
        QString srcPath = file.absoluteFilePath();
        QString dstPath = destination.absoluteFilePath(file.fileName());

        if (file.isDir()) {
            copyDirectory(srcPath, dstPath); // 递归复制目录
        } else {
            QFile::copy(srcPath, dstPath); // 复制文件
        }
    }
}


void ConfigFileIO::setIksConfig(const ::EnIks &baseName, const QString &id, const QString &key, const QString &secret)
{
    QString fileName = ConfigConstWay::get_TRUE_WAY(ConfigConstWay::CONFIGURATION_WAY);
    QSettings *setting = new QSettings(fileName , QSettings::IniFormat);
    setting->setIniCodec(QTextCodec::codecForName("UTF-8"));
    setting->setValue("IKS/"+::IksM[baseName]+"/id",id);
    setting->setValue("IKS/"+::IksM[baseName]+"/key",key);
    setting->setValue("IKS/"+::IksM[baseName]+"/secret",secret);
    setting->sync();
    setting->deleteLater();
}

IKS ConfigFileIO::getIksConfig(const ::EnIks &baseName)
{
    QString fileName = ConfigConstWay::get_TRUE_WAY(ConfigConstWay::CONFIGURATION_WAY);
    QSettings *setting = new QSettings(fileName , QSettings::IniFormat);
    setting->setIniCodec(QTextCodec::codecForName("UTF-8"));
    ::IKS iks={"","",""};
    if(QFile::exists(fileName))
    {
        iks.id = setting->value("IKS/"+::IksM[baseName]+"/id",NULLVALUE).toString();
        iks.key= setting->value("IKS/"+::IksM[baseName]+"/key",NULLVALUE).toString();
        iks.secret=setting->value("IKS/"+::IksM[baseName]+"/secret",NULLVALUE).toString();
        setting->deleteLater();
        return iks;
    }
    else {
        setting->sync();
        setting->deleteLater();
        return iks;
    }
}

void ConfigFileIO::setUrlConfig(const ::EnUrl &urlName, const QString &url)
{
    QString fileName = ConfigConstWay::get_TRUE_WAY(ConfigConstWay::CONFIGURATION_WAY);
    QSettings *setting = new QSettings(fileName , QSettings::IniFormat);
    setting->setIniCodec(QTextCodec::codecForName("UTF-8"));
    setting->setValue("URL/"+UrlM[urlName],url);
    setting->sync();
    setting->deleteLater();
}

const QString ConfigFileIO::getUrlConfig(const ::EnUrl &urlName)
{
    QString fileName = ConfigConstWay::get_TRUE_WAY(ConfigConstWay::CONFIGURATION_WAY);
    QSettings *setting = new QSettings(fileName , QSettings::IniFormat);
    setting->setIniCodec(QTextCodec::codecForName("UTF-8"));
    if(QFile::exists(fileName))
    {
        QString data = setting->value("URL/"+UrlM[urlName],NULLVALUE).toString();
        setting->deleteLater();
        return data;
    }
    else {
        setting->sync();
        setting->deleteLater();
        return NULLVALUE;
    }
}

void ConfigFileIO::setUserConfig(const ::EnUser &keyName, const QString &value)
{
    QString fileName =  ConfigConstWay::get_TRUE_WAY(ConfigConstWay::CONFIGURATION_WAY);
    QSettings *setting = new QSettings(fileName , QSettings::IniFormat);
    setting->setIniCodec(QTextCodec::codecForName("UTF-8"));
    if(keyName!=::EnUser::NULL_MARK){
        setting->setValue("USER/"+::UserM[keyName],value);
    }
    setting->sync();
    setting->deleteLater();
}

QString ConfigFileIO::getUserConfig(const ::EnUser &keyName)
{
    if(keyName==::EnUser::NULL_MARK){
        return NULLVALUE;
    }

    QString fileName = ConfigConstWay::get_TRUE_WAY(ConfigConstWay::CONFIGURATION_WAY);
    QSettings *setting = new QSettings(fileName , QSettings::IniFormat);
    setting->setIniCodec(QTextCodec::codecForName("UTF-8"));
    if(QFile::exists(fileName))
    {
        QString data = setting->value("USER/"+::UserM[keyName]).toString();
        setting->deleteLater();
        return data;
    }
    else {
        setting->sync();
        setting->deleteLater();
        return NULLVALUE;
    }

}

void ConfigFileIO::setOtherConfig(const QString& path,const QString &baseName, const QString &keyName, const QString &value)
{
    QString fileName = path;
    QSettings *setting = new QSettings(fileName , QSettings::IniFormat);
    setting->setIniCodec(QTextCodec::codecForName("UTF-8"));
    setting->setValue(baseName+"/"+keyName,value);
    setting->sync();
    setting->deleteLater();
}

QString ConfigFileIO::getOtherConfig(const QString& path,const QString &baseName, const QString &keyName)
{
    QString fileName = path;
    QSettings *setting = new QSettings(fileName , QSettings::IniFormat);
    setting->setIniCodec(QTextCodec::codecForName("UTF-8"));
    if(QFile::exists(fileName))
    {
        QString data = setting->value(baseName+"/"+keyName,NULLVALUE).toString();
        setting->deleteLater();
        return data;
    }
    else {
        setting->sync();
        setting->deleteLater();
        return NULLVALUE;
    }

}

QMap<QString, QString> ConfigFileIO::getOtherBaseAllConfig(const QString &path, const QString &baseName)
{
    QMap<QString,QString>paramMap;
    QSettings* setting=new QSettings(path, QSettings::IniFormat);
    setting->setIniCodec(QTextCodec::codecForName("UTF-8"));
    setting->beginGroup(baseName);
    QStringList keys = setting->allKeys();
    for (const QString& key : keys) {
        paramMap.insert(key, setting->value(key).toString());
    }
    setting->deleteLater();
    return paramMap;
}

void ConfigFileIO::setOtherBaseAllConfig(const QString &path, const QString &baseName, QMap<QString, QString> data)
{
    {
        QSettings clearGroupSetting(path, QSettings::IniFormat);
        clearGroupSetting.setIniCodec(QTextCodec::codecForName("UTF-8"));
        clearGroupSetting.beginGroup(baseName);
        clearGroupSetting.remove("");
        clearGroupSetting.endGroup();
    }

    QSettings* setting=new QSettings(path, QSettings::IniFormat);
    setting->setIniCodec(QTextCodec::codecForName("UTF-8"));
    setting->beginGroup(baseName);
    for (auto it = data.begin(); it != data.end(); ++it) {
        setting->setValue(it.key(), it.value());
    }
    setting->endGroup();
    setting->deleteLater();
}


