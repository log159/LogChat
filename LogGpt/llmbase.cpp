#include "llmbase.h"

LLMBase::LLMBase(QObject *parent) : QObject(parent)
{

}

LLMBase::~LLMBase()
{
    qDebug()<<"------------------LLM端析构------------------";
}
