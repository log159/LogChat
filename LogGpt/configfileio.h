#ifndef CONFIGFILEIO_H
#define CONFIGFILEIO_H

#include <QCoreApplication>
#include <QTextCodec>
#include <QSettings>
#include <QFile>
#include <QPair>
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

    //举例 base=EnIks::LLM_CHATGPT id="123" key="abc114514" secret="zxc332211" 没有或不需要则留空字符串 保存到配置文件
    static void setIksConfig(const ::EnIks& baseName,const QString& id=NULLVALUE,const QString& key=NULLVALUE,const QString& secret=NULLVALUE);
    //通过EnIks枚举获取到ID,KEY,SECRET数据
    static ::IKS getIksConfig(const ::EnIks& baseName);

    //存储一个url地址，urlName自定义
    static void setUrlConfig(const ::EnUrl& urlName,const QString& url);
    //获取一个url地址，urlName要在文件存在否则为空
    static const QString getUrlConfig(const ::EnUrl& urlName);

private:

};

#endif // CONFIGFILEIO_H
