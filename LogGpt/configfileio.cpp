#include "configfileio.h"

const QString           ConfigFileIO::NULLVALUE="";


void ConfigFileIO::setIksConfig(const ::EnIks &baseName, const QString &id, const QString &key, const QString &secret)
{
    QString fileName = ConfigConstWay::get_IKS_INI_WAY();
    QSettings *setting = new QSettings(fileName , QSettings::IniFormat);
    setting->setIniCodec(QTextCodec::codecForName("UTF-8"));
    setting->setValue(::IksM[baseName]+"/id",id);
    setting->setValue(::IksM[baseName]+"/key",key);
    setting->setValue(::IksM[baseName]+"/secret",secret);
    // 生成文件
    setting->sync();
}

IKS ConfigFileIO::getIksConfig(const ::EnIks &baseName)
{
    QString fileName = ConfigConstWay::get_IKS_INI_WAY();
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

void ConfigFileIO::setUrlConfig(const QString &urlName, const QString &url)
{
    QString fileName = ConfigConstWay::get_URL_INI_WAY();
    QSettings *setting = new QSettings(fileName , QSettings::IniFormat);
    setting->setIniCodec(QTextCodec::codecForName("UTF-8"));
    setting->setValue(urlName,url);
    // 生成文件
    setting->sync();
}

const QString ConfigFileIO::getUrlConfig(const QString &urlName)
{
    QString fileName = ConfigConstWay::get_URL_INI_WAY();
    QSettings *setting = new QSettings(fileName , QSettings::IniFormat);
    setting->setIniCodec(QTextCodec::codecForName("UTF-8"));
    if(QFile::exists(fileName))
    {
        QString data = setting->value(urlName,NULLVALUE).toString();
        return data;
    }
    else {
        setting->sync();
        return NULLVALUE;
    }
}
