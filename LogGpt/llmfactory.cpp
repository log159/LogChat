#include "llmfactory.h"

ChatGPTApi *LLMFactory::getChatGPTApi(QObject *parent)
{
    return new ChatGPTApi(parent);
}

XfxhApi *LLMFactory::getXfxhApi(QObject *parent)
{
    return new XfxhApi(parent);
}
