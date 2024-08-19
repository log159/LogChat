#ifndef CHATGPTAPI_H
#define CHATGPTAPI_H

#include <QObject>

#include "llmbase.h"


class ChatGPTApi : public LLMBase
{
    Q_OBJECT

public:
    explicit ChatGPTApi(QObject *parent = nullptr);

public:
    void start(const QString& str)override;
private:
    void init();
    void initConnect();
signals:

public slots:
};

#endif // CHATGPTAPI_H
