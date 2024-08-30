#ifndef DEEPSEEKAPI_H
#define DEEPSEEKAPI_H

#include <QObject>

#include "llmbase.h"

class DeepSeekApi : public LLMBase
{
    Q_OBJECT
public:
    explicit DeepSeekApi(QObject *parent = nullptr);
public:
    void start(const QString& str)override;
signals:

public slots:
};

#endif // DEEPSEEKAPI_H
