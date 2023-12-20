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
    modItem.getTopEnable()<<"\n"<<
    modItem.getModelSize()<<"\n"<<
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
//    m_ModelName="";
//    m_FilePath="";
//    m_LookEnable=true;
//	m_TopEnable=true;
//    m_ModelSize=Config::get_LIVE2DPARAMINIT_M()["model_size"];
//    m_MouseSpeed=Config::get_LIVE2DPARAMINIT_M()["mouse_speed"];
//    m_EyeTime=Config::get_LIVE2DPARAMINIT_M()["eye_time"];
//    m_EyeDeviation=Config::get_LIVE2DPARAMINIT_M()["eye_deviation"];
//    m_EyeSpeed=Config::get_LIVE2DPARAMINIT_M()["eye_speed"];
//    m_AudioAdd=Config::get_LIVE2DPARAMINIT_M()["audio_add"];
//    m_AudioSmooth=Config::get_LIVE2DPARAMINIT_M()["audio_smooth"];
//	m_ModelDescription="NULL";
}
