#include "chatgptapi.h"

ChatGPTApi::ChatGPTApi(QObject *parent) : LLMBase(parent)
{
}
void ChatGPTApi::start(const QString &str)
{
    QString selectModel=CHATGPT_MODEL_V.at(Config::get_USER(::EnUser::CHATGPT_MODEL_ID).toInt());
    qDebug()<<"使用模型 ChatGPT ："<<selectModel;
    qDebug()<<"发送内容为————>"<<str;

    qDebug()<<ConfigConstWay::get_TRUE_WAY(ConfigConstWay::CHATGPT_DEMO_WAY);
    QStringList list;
    list<<Config::get_IKS(::EnIks::LLM_CHATGPT).key
       <<Config::get_URL(::EnUrl::URL_CHATGPT_BASEURL)
        <<str.toUtf8()
       <<selectModel;
    m_Process->start(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::CHATGPT_DEMO_WAY),list);
}
