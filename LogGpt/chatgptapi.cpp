#include "chatgptapi.h"

ChatGPTApi::ChatGPTApi(QObject *parent) : LLMBase(parent)
{
    init();
    initConnect();
}
void ChatGPTApi::init()
{
    m_Process=new QProcess(this);
}

void ChatGPTApi::start(const QString &str)
{
    qDebug()<<"使用模型 ChatGPT ："<<Config::get_CHATGPT_MODEL_V().at(0);
    qDebug()<<"发送内容为————>"<<str;

    qDebug()<<Config::get_CHATGPT_DEMO_WAY();
    QStringList list;
    list<<Config::get_IKS(::EnIks::LLM_CHATGPT).key
       <<Config::get_URL("URL_CHATGPT_BASEURL")
        <<str.toUtf8();
    m_Process->start(Config::get_CHATGPT_DEMO_WAY(),list);

}

void ChatGPTApi::initConnect()
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
