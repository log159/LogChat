#ifndef CONFIGCONSTWAY_H
#define CONFIGCONSTWAY_H

#include <QString>
#include <QCoreApplication>
#include <QDateTime>

#include "singletonbase.h"


class ConfigConstWay : public SingletonBase
{
public:
    //常量信息
    static const QString            SETCONFIG_WAY;         //设置配置路径
    static const QString            OUTPUT_WAV_WAY;        //音频文件输出路径
    static const QString            OUTPUT_COMPOUNDWAV_WAY;//合成音频文件输出路径
    static const QString            CHARACTER_CONFIG_WAY;  //角色扮演配置文件路径
    static const QString            CHATGPT_DEMO_WAY;      //chatgptEXE路径
    static const QString            XFXH_QUESTION_WAY;     //讯飞星火QUESTION路径
    static const QString            XFXH_DEMO_WAY;         //讯飞星火EXE路径
    static const QString            UNITY_DEMO_WAY;        //Unity Live2D EXE路径
    static const QString            UNITY_DEMO_WORK_WAY;       //Unity 工作目录
    static const QString            UNITY_STARTMODELPATH_WAY;  //Unity 模型文件加载路径
    static const QString            UNITY_MODELLIST_WAY;       //Unity Live 2D路径列表
    static const QString            UNITY_MODELCONFIGLIST_WAY; //Unity 模型文件配置加载路径
    static const QString            IKS_INI_WAY;                //存储APP类信息 ID KEY SECRET 信息的INI文件路径
    static const QString            URL_INI_WAY;                //存储URL类信息 ADDRESS PORT 信息的INI文件路径
    static const QString            USER_INI_WAY;               //存储USERl自定义信息的INI文件路径

    //传入以上相对路径，返回真实路径
    static const QString get_TRUE_WAY(const QString& path);

};

#endif // CONFIGCONSTWAY_H
