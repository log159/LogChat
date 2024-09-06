#include "configconstway.h"

const QString ConfigConstWay::SETCONFIG_WAY             ="/config/setconfig.json";
const QString ConfigConstWay::OUTPUT_WAV_WAY            ="/voice/%1.wav";
const QString ConfigConstWay::OUTPUT_SAVEWAV_WAY        ="/voicesave/%1.wav";
const QString ConfigConstWay::CHARACTER_CONFIG_WAY      ="/config/config.txt";
const QString ConfigConstWay::CHATGPT_DEMO_WAY          ="/chatgptapi/dist/gptchat.exe";
const QString ConfigConstWay::XFXH_QUESTION_WAY         ="/xfxhapi/question.txt";
const QString ConfigConstWay::XFXH_DEMO_WAY             ="/xfxhapi/demo.exe";
const QString ConfigConstWay::DEEPSEEK_DEMO_WAY         ="/deepseekapi/dist/deepseek.exe";
const QString ConfigConstWay::UNITY_DEMO_WAY            ="/unity2d/L2dUnityDemo.exe";
const QString ConfigConstWay::UNITY_DEMO_WORK_WAY       ="/unity2d";
const QString ConfigConstWay::UNITY_MODELS_WAY          ="/unity2d/model/Models";
const QString ConfigConstWay::UNITY_STARTMODELPATH_WAY  ="/unity2d/model/STARTMODELPATH.txt";
const QString ConfigConstWay::UNITY_MODELLIST_WAY       ="/unity2d/model/MODELLIST.txt";
const QString ConfigConstWay::UNITY_MODELCONFIGLIST_WAY ="/unity2d/model/MODELCONFIGLIST.txt";
const QString ConfigConstWay::CONFIGURATION_WAY         ="/config/configuration.ini";

const QString ConfigConstWay::get_TRUE_WAY(const QString &path)
{
    return QCoreApplication::applicationDirPath()+path;
}
