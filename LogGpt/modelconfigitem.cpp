#include "modelconfigitem.h"

ModelConfigItem::ModelConfigItem()
{
    init();

}
void ModelConfigItem::printInformation(ModelConfigItem &modItem)
{
    qDebug()<<modItem.getModelId()<<"\n"<<
    modItem.getModelName()<<"\n"<<
    modItem.getFilePath()<<"\n"<<
    modItem.getLookEnable()<<"\n"<<
    modItem.getTopApha()<<"\n"<<
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

void ModelConfigItem::init()
{
    this->setModelId(::LIVE2DPARAMINIT_M["model_id"]);
    this->setModelName(::LIVE2DSTRING_M["model_name"]);
    this->setFilePath(::LIVE2DSTRING_M["file_path"]);
    this->setLookEnable(::LIVE2DENABLEINIT_M["look_enable"]);
    this->setTopApha(::LIVE2DPARAMINIT_M["win_topapha"]);
    this->setModelSize(::LIVE2DPARAMINIT_M["model_size"]);
    this->setModelX(::LIVE2DPARAMINIT_M["model_x"]);
    this->setModelY(::LIVE2DPARAMINIT_M["model_y"]);
    this->setMouseSpeed(::LIVE2DPARAMINIT_M["mouse_speed"]);
    this->setEyeTime(::LIVE2DPARAMINIT_M["eye_time"]);
    this->setEyeDeviation(::LIVE2DPARAMINIT_M["eye_deviation"]);
    this->setEyeSpeed(::LIVE2DPARAMINIT_M["eye_speed"]);
    this->setAudioAdd(::LIVE2DPARAMINIT_M["audio_add"]);
    this->setAudioSmooth(::LIVE2DPARAMINIT_M["audio_smooth"]);
    this->setModelDescription(::LIVE2DSTRING_M["model_description"]);
}


