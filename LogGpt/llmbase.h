#ifndef LLMBASE_H
#define LLMBASE_H

#include <QObject>
#include <QProcess>
#include <QStringList>
#include <QDebug>
#include <QByteArray>

#include "config.h"
#include "configfileio.h"

class LLMBase : public QObject
{
    Q_OBJECT
protected:
    typedef void (QProcess::*FinishedFunc)(int,QProcess::ExitStatus);

    QProcess*   m_Process   =nullptr;
    bool        m_Stop      =false;
public:
    explicit LLMBase(QObject *parent = nullptr);

    virtual ~LLMBase();

    virtual void start(const QString& str) = 0;

    void stop();
protected:
    void init();
    void initConnect();
signals:
    void read(QString str);
    void quit();
    void stopQuit();
public slots:
};

#endif // LLMBASE_H
