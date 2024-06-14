#include "xfxhapi.h"

XfxhApi::XfxhApi(QObject *parent) : LLMBase(parent)
{
    init();
    initConnect();
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

void XfxhApi::init()
{
    m_Process=new QProcess(this);
}

void XfxhApi::initConnect()
{
    QObject::connect(m_Process,&QProcess::readyReadStandardOutput, [=]() {
        QByteArray outputData = m_Process->readAllStandardOutput();
        QString receivedData = QString::fromUtf8(outputData);
        qDebug() << "接收到内容————>" << receivedData;
        emit read(receivedData);
    });
    FinishedFunc finished = &QProcess::finished;
    connect(m_Process,finished,[=](){
        qDebug()<<"------------LLM 请求资源释放-----------";
        m_Process->deleteLater();
        delete m_Process;
        emit quit();
    });
}

void XfxhApi::handleReceivedData()
{

}
