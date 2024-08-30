#ifndef MODELCONFIGITEM_H
#define MODELCONFIGITEM_H

#include <QString>
#include <QDebug>


class ModelConfigItem
{
private:
    int         m_ModelId;
    QString     m_ModelName;
    QString     m_FilePath;
    bool        m_LookEnable;
    int         m_TopApha;
    int         m_ModelSize;
    int         m_ModelX;
    int         m_ModelY;
    int         m_MouseSpeed;
    int         m_EyeTime;
    int         m_EyeDeviation;
    int         m_EyeSpeed;
    int         m_AudioAdd;
    int         m_AudioSmooth;
    QString     m_ModelDescription;

public:
    ModelConfigItem();

    //get
    inline       int getModelId()const{return m_ModelId;}
    inline const QString getModelName()const{return m_ModelName;}
    inline const QString getFilePath()const{return m_FilePath;}
    inline bool getLookEnable()const{return m_LookEnable;}
    inline int getTopApha()const{return m_TopApha;}
    inline int getModelSize()const{return m_ModelSize;}
    inline int getModelX()const{return m_ModelX;}
    inline int getModelY()const{return m_ModelY;}
    inline int getMouseSpeed()const{return m_MouseSpeed;}
    inline int getEyeTime()const{return m_EyeTime;}
    inline int getEyeDeviation()const{return m_EyeDeviation;}
    inline int getEyeSpeed()const{return m_EyeSpeed;}
    inline int getAudioAdd()const{return m_AudioAdd;}
    inline int getAudioSmooth()const{return m_AudioSmooth;}
    inline const QString getModelDescription()const{return m_ModelDescription;}

public:
    //set
    inline void setModelId(int i){m_ModelId=i;}
    inline void setModelName(const QString& str){m_ModelName=str;}
    inline void setFilePath(const QString& str){m_FilePath=str;}
    inline void setLookEnable(bool bo){m_LookEnable=bo;}
    inline void setTopApha(int i){m_TopApha=i;}
    inline void setModelSize(int i){m_ModelSize=i;}
    inline void setModelX(int i){m_ModelX=i;}
    inline void setModelY(int i){m_ModelY=i;}
    inline void setMouseSpeed(int i){m_MouseSpeed=i;}
    inline void setEyeTime(int i){m_EyeTime=i;}
    inline void setEyeDeviation(int i){m_EyeDeviation=i;}
    inline void setEyeSpeed(int i){m_EyeSpeed=i;}
    inline void setAudioAdd(int i){m_AudioAdd=i;}
    inline void setAudioSmooth(int i){m_AudioSmooth=i;}
    inline void setModelDescription(const QString& str){m_ModelDescription=str;}

public:
    static void printInformation(ModelConfigItem& modItem);

};

#endif // MODELCONFIGITEM_H
