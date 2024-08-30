#include "chatgptapi.h"

ChatGPTApi::ChatGPTApi(QObject *parent) : LLMBase(parent)
{
}
void ChatGPTApi::start(const QString &str)
{
    qDebug()<<"使用模型 ChatGPT ："<<CHATGPT_MODEL_V.at(0);
    qDebug()<<"发送内容为————>"<<str;

    qDebug()<<ConfigConstWay::get_TRUE_WAY(ConfigConstWay::CHATGPT_DEMO_WAY);
    QStringList list;
    list<<Config::get_IKS(::EnIks::LLM_CHATGPT).key
       <<Config::get_URL(::EnUrl::URL_CHATGPT_BASEURL)
        <<str.toUtf8();
    m_Process->start(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::CHATGPT_DEMO_WAY),list);
}
