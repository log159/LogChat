#include "vitsfactory.h"



VITSBase *VITSFactory::getNew(QObject *parent)
{
    int id=Config::get_USER(EnUser::VITS_MODEL_SELECT).toInt();
    qDebug()<<"vits id is = "<<id;
    if(id==0)
        return getVitsApi(parent);
    else if(id==1)
        return getGPTSoVitsApi(parent);
    else if(id==2)
        return getSelfVitsApi(parent);
    else
        return nullptr;
}

VitsApi *VITSFactory::getVitsApi(QObject *parent)
{
    return new VitsApi(parent);

}

GPTSoVitsApi *VITSFactory::getGPTSoVitsApi(QObject *parent)
{
    return new GPTSoVitsApi(parent);

}

SelfVits *VITSFactory::getSelfVitsApi(QObject *parent)
{
    return new SelfVits(parent);

}
