#ifndef CONFIGFILEIO_H
#define CONFIGFILEIO_H

#include <QCoreApplication>
#include <QTextCodec>
#include <QSettings>
#include <QFile>
#include <QPair>
#include <QMap>
#include <QTextStream>
#include <QJsonDocument>
#include <QDebug>
#include <QDir>
#include <QMap>

#include "singletonbase.h"
#include "global.h"
#include "configconstway.h"


class ConfigFileIO : public SingletonBase
{
private:

public:
    static const QString NULLVALUE;
public:

    //一般文本IO
    static const QString getFileInformation(const QString& path);
    static const QString getFileAllInformation(const QString& path);
    static void setFileInformation(const QString& path,const QString& str);
    static void setFileInformation(const QString& path,const QJsonObject& js);

    static void copyDirectory(const QString &sourceDir, const QString &destinationDir);

    //举例 base=EnIks::LLM_CHATGPT id="123" key="abc114514" secret="zxc332211" 没有或不需要则留空字符串 保存到配置文件
    static void setIksConfig(const ::EnIks& baseName,const QString& id=NULLVALUE,const QString& key=NULLVALUE,const QString& secret=NULLVALUE);
    //通过EnIks枚举获取到ID,KEY,SECRET数据
    static ::IKS getIksConfig(const ::EnIks& baseName);

    //存储一个url地址，urlName自定义
    static void setUrlConfig(const ::EnUrl& urlName,const QString& url);
    //获取一个url地址，urlName要在文件存在否则为空
    static const QString getUrlConfig(const ::EnUrl& urlName);

    static void setUserConfig(const ::EnUser& keyName = ::EnUser::NULL_MARK,const QString& value = "");

    static QString getUserConfig(const ::EnUser& keyName = ::EnUser::NULL_MARK);

    //完全自定义的ini设置
    static void setOtherConfig(const QString& path,const QString& baseName,const QString& keyName,const QString& value);
    //完全自定义的ini获取
    static QString getOtherConfig(const QString& path,const QString& baseName,const QString& keyName);

    //获取自定义的ini的Base下所有的键值对
    static QMap<QString,QString> getOtherBaseAllConfig(const QString& path,const QString& baseName);
    //设置自定义的ini的Base下所有的键值对
    static void setOtherBaseAllConfig(const QString& path,const QString& baseName,QMap<QString,QString>data);



private:

};

#endif // CONFIGFILEIO_H
