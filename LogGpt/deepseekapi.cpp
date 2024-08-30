#include "deepseekapi.h"

DeepSeekApi::DeepSeekApi(QObject *parent) : LLMBase(parent)
{
}

void DeepSeekApi::start(const QString &str)
{
    qDebug()<<"使用模型 深度求索";
    qDebug()<<"发送内容为————>"<<str;
    qDebug()<<ConfigConstWay::get_TRUE_WAY(ConfigConstWay::DEEPSEEK_DEMO_WAY);
    QStringList list;
    list<<Config::get_IKS(::EnIks::LLM_DEEPSEEK).key
       <<Config::get_URL(::EnUrl::URL_DEEPSEEK_BASEURL)
      <<str.toUtf8();
    m_Process->start(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::DEEPSEEK_DEMO_WAY),list);
}
