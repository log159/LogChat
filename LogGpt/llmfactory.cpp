#include "llmfactory.h"

LLMBase *LLMFactory::getNew(QObject *parent)
{
    int id=Config::get_USER(::EnUser::LLM_MODEL_ID).toInt();
    qDebug()<<"llm id is = "<<id;
    if(id==0)
        return getChatGPTApi(parent);
    else if(id==1)
        return getXfxhApi(parent);
    else if(id==2)
        return getDeepSeekApi(parent);
    else
        return nullptr;
}

ChatGPTApi *LLMFactory::getChatGPTApi(QObject *parent)
{
    return new ChatGPTApi(parent);
}

XfxhApi *LLMFactory::getXfxhApi(QObject *parent)
{
    return new XfxhApi(parent);
}

DeepSeekApi *LLMFactory::getDeepSeekApi(QObject *parent)
{
    return new DeepSeekApi(parent);
}
