#include "configconstway.h"

//const QString ConfigConstWay::SETCONFIG_WAY         ="/config/setconfig.json";
//const QString ConfigConstWay::OUTPUT_WAV_WAY        ="/wav/%1.wav";
//const QString ConfigConstWay::CHARACTER_CONFIG_WAY  ="/config/config.txt";
//const QString ConfigConstWay::CHATGPT_DEMO_WAY      ="/chatgptapi/dist/qtopenai.exe";
//const QString ConfigConstWay::XFXH_QUESTION_WAY     ="/xfxhapi/question.txt";
//const QString ConfigConstWay::XFXH_DEMO_WAY         ="/xfxhapi/demo.exe";
//const QString ConfigConstWay::UNITY_DEMO_WAY        ="/unity2d/Live2D.exe";
//const QString ConfigConstWay::UNITY_DEMO_WORK_WAY   ="/unity2d";
//const QString ConfigConstWay::UNITY_STARTMODELPATH_WAY="/unity2d/model/STARTMODELPATH.txt";
//const QString ConfigConstWay::UNITY_MODELLIST_WAY     ="/unity2d/model/MODELLIST.txt";
//const QString ConfigConstWay::UNITY_MODELCONFIGLIST_WAY="/unity2d/model/MODELCONFIGLIST.txt";
//const QString ConfigConstWay::HISTORY_WAY              ="/ConfigConstWay/history.json";


const QString ConfigConstWay::IKS_INI_WAY           ="/Config/IKS_INI.ini";
const QString ConfigConstWay::URL_INI_WAY           ="/Config/URL_INI.ini";


QString ConfigConstWay::get_IKS_INI_WAY()
{
    return QCoreApplication::applicationDirPath()+IKS_INI_WAY;
}

QString ConfigConstWay::get_URL_INI_WAY()
{
    return QCoreApplication::applicationDirPath()+URL_INI_WAY;
}
