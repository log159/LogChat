#ifndef LLMFACTORY_H
#define LLMFACTORY_H

#include "singletonbase.h"
#include "llmbase.h"
#include "chatgptapi.h"
#include "xfxhapi.h"
#include "deepseekapi.h"

class LLMFactory:public SingletonBase
{
public:
    static LLMBase* getNew(QObject* parent);
private:
    static ChatGPTApi* getChatGPTApi(QObject* parent);
    static XfxhApi*    getXfxhApi(QObject* parent);
    static DeepSeekApi* getDeepSeekApi(QObject* parent);
};

#endif // LLMFACTORY_H
