#include "xfxhapi.h"

XfxhApi::XfxhApi(QObject *parent) : LLMBase(parent)
{
}

void XfxhApi::start(const QString &str)
{
    qDebug()<<"使用模型 讯飞星火 ："<<XFXH_MODEL_V.at(Config::get_USER(::EnUser::XFXH_MODEL_ID).toInt());
    qDebug()<<"发送内容为————>"<<str;
    Config::set_XFXH_QUESTION(str);
    QStringList list;
    list<<QString(Config::get_IKS(EnIks::LLM_XFXH).id).toUtf8()
        <<QString(Config::get_IKS(EnIks::LLM_XFXH).key).toUtf8()
        <<QString(Config::get_IKS(EnIks::LLM_XFXH).secret).toUtf8()
        <<QString(XFXH_MODEL_V.at(Config::get_USER(::EnUser::XFXH_MODEL_ID).toInt())).toUtf8()
        <<QString(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::XFXH_QUESTION_WAY)).toUtf8();
    m_Process->start(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::XFXH_DEMO_WAY),list);
}
