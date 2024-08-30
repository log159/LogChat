#include "vitsfactory.h"



VITSBase *VITSFactory::getNew(QObject *parent)
{
    int id=Config::get_USER(EnUser::VITS_MODEL_SELECT).toInt();
    qDebug()<<"vits id is = "<<id;
    if(id==0)
        return getVitsApi(parent);
    else if(id==1)
        return getGPTSoVitsApi(parent);
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
