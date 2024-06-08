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
public:
    explicit LLMBase(QObject *parent = nullptr);

    virtual void start(const QString& str) = 0;
signals:
    void read(QString str);
    void quit();
public slots:
};

#endif // LLMBASE_H
