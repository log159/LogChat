#ifndef LLMFACTORY_H
#define LLMFACTORY_H

#include "singletonbase.h"
#include "llmbase.h"
#include "chatgptapi.h"
#include "xfxhapi.h"

class LLMFactory:public SingletonBase
{
public:
    static ChatGPTApi* getChatGPTApi(QObject* parent);
    static XfxhApi*    getXfxhApi(QObject* parent);
};

#endif // LLMFACTORY_H
