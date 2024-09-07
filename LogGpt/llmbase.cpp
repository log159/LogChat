#include "llmbase.h"

LLMBase::LLMBase(QObject *parent) : QObject(parent)
{
    init();
    initConnect();
}

LLMBase::~LLMBase()
{
    m_Process->close();
    qDebug()<<"------------------LLM端析构------------------";
}

void LLMBase::stop()
{
    m_Stop=true;
}

void LLMBase::init()
{
    m_Process=new QProcess(this);
}
void LLMBase::initConnect()
{
    QObject::connect(m_Process,&QProcess::readyReadStandardOutput, [=]() {
        if(m_Process==nullptr)return;
        if(m_Stop==true){emit stopQuit(); return;}
        QByteArray outputData = m_Process->readAllStandardOutput();
        QString receivedData = QString::fromUtf8(outputData);
        qDebug() << "接收到内容————>" << receivedData;
        emit read(receivedData);
    });
    FinishedFunc finished = &QProcess::finished;
    connect(m_Process,finished,[=](){
        if(m_Process==nullptr)return;
        if(m_Stop==true){emit stopQuit(); return;}
        qDebug()<<"------------LLM 请求资源释放-----------";
        emit quit();
    });
}
