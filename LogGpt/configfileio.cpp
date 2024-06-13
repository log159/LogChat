#include "configfileio.h"

const QString           ConfigFileIO::NULLVALUE="";


void ConfigFileIO::setIksConfig(const ::EnIks &baseName, const QString &id, const QString &key, const QString &secret)
{
    QString fileName = ConfigConstWay::get_TRUE_WAY(ConfigConstWay::IKS_INI_WAY);
    QSettings *setting = new QSettings(fileName , QSettings::IniFormat);
    setting->setIniCodec(QTextCodec::codecForName("UTF-8"));
    if(id!=""){
        setting->setValue(::IksM[baseName]+"/id",id);
    }
    if(key!=""){
        setting->setValue(::IksM[baseName]+"/key",key);
    }
    if(secret!=""){
        setting->setValue(::IksM[baseName]+"/secret",secret);
    }
    // 生成文件
    setting->sync();
}

IKS ConfigFileIO::getIksConfig(const ::EnIks &baseName)
{
    QString fileName = ConfigConstWay::get_TRUE_WAY(ConfigConstWay::IKS_INI_WAY);
    QSettings *setting = new QSettings(fileName , QSettings::IniFormat);
    setting->setIniCodec(QTextCodec::codecForName("UTF-8"));
    ::IKS iks={"","",""};
    if(QFile::exists(fileName))
    {
        iks.id = setting->value(::IksM[baseName]+"/id",NULLVALUE).toString();
        iks.key= setting->value(::IksM[baseName]+"/key",NULLVALUE).toString();
        iks.secret=setting->value(::IksM[baseName]+"/secret",NULLVALUE).toString();
        return iks;
    }
    else {
        // 生成文件
        setting->sync();
        return iks;
    }
}

void ConfigFileIO::setUrlConfig(const ::EnUrl &urlName, const QString &url)
{
    QString fileName = ConfigConstWay::get_TRUE_WAY(ConfigConstWay::URL_INI_WAY);
    QSettings *setting = new QSettings(fileName , QSettings::IniFormat);
    setting->setIniCodec(QTextCodec::codecForName("UTF-8"));
    if(url!=""){
        setting->setValue(UrlM[urlName],url);
    }
    setting->sync();
}

const QString ConfigFileIO::getUrlConfig(const ::EnUrl &urlName)
{
    QString fileName = ConfigConstWay::get_TRUE_WAY(ConfigConstWay::URL_INI_WAY);
    QSettings *setting = new QSettings(fileName , QSettings::IniFormat);
    setting->setIniCodec(QTextCodec::codecForName("UTF-8"));
    if(QFile::exists(fileName))
    {
        QString data = setting->value(UrlM[urlName],NULLVALUE).toString();
        return data;
    }
    else {
        setting->sync();
        return NULLVALUE;
    }
}

void ConfigFileIO::setUserConfig(const ::EnUser &keyName, const QString &value)
{
    QString fileName =  ConfigConstWay::get_TRUE_WAY(ConfigConstWay::USER_INI_WAY);
    QSettings *setting = new QSettings(fileName , QSettings::IniFormat);
    setting->setIniCodec(QTextCodec::codecForName("UTF-8"));
    if(keyName!=::EnUser::NULL_MARK){
        setting->setValue(::UserM[keyName],value);
    }
    setting->sync();
}

QString ConfigFileIO::getUserConfig(const ::EnUser &keyName)
{
    if(keyName==::EnUser::NULL_MARK){
        return NULLVALUE;
    }

    QString fileName = ConfigConstWay::get_TRUE_WAY(ConfigConstWay::USER_INI_WAY);
    QSettings *setting = new QSettings(fileName , QSettings::IniFormat);
    setting->setIniCodec(QTextCodec::codecForName("UTF-8"));
    if(QFile::exists(fileName))
    {
        QString data = setting->value(::UserM[keyName]).toString();
        return data;
    }
    else {
        setting->sync();
        return NULLVALUE;
    }
}


