#include "modelconfigitem.h"

ModelConfigItem::ModelConfigItem()
{
}

void ModelConfigItem::printInformation(ModelConfigItem &modItem)
{
    qDebug()<<modItem.getModelId()<<"\n"<<
    modItem.getModelName()<<"\n"<<
    modItem.getFilePath()<<"\n"<<
    modItem.getLookEnable()<<"\n"<<
    modItem.getTopEnable()<<"\n"<<
    modItem.getModelSize()<<"\n"<<
    modItem.getModelX()<<"\n"<<
    modItem.getModelY()<<"\n"<<
    modItem.getMouseSpeed()<<"\n"<<
    modItem.getEyeTime()<<"\n"<<
    modItem.getEyeDeviation()<<"\n"<<
    modItem.getEyeSpeed()<<"\n"<<
    modItem.getAudioAdd()<<"\n"<<
    modItem.getAudioSmooth()<<"\n"<<
    modItem.getModelDescription();


}


