#ifndef CHANGECONFIGITEM_H
#define CHANGECONFIGITEM_H

#include <QString>
#include <QDebug>

#include "transformation.h"

class ChangeConfigItem
{

private:
    QString m_Name;
    int     m_DefaultValue;
    int     m_MinValue;
    int     m_MaxValue;

public:
    ChangeConfigItem();

    //get
    inline const QString    getName()const {return m_Name;}
    inline int           getDefaultValue()const{return m_DefaultValue;}
    inline int           getMinValue()const{return m_MinValue;}
    inline int           getMaxValue()const{return m_MaxValue;}

public:
    inline void     setName(const QString& str) {m_Name=str;}
    inline void     setDefaultValue(const int& db){m_DefaultValue=db;}
    inline void     setMinValue(const int& db){m_MinValue=db;}
    inline void     setMaxValue(const int& db){m_MaxValue=db;}
public:
    static void printInformation(ChangeConfigItem& item);

};

#endif // CHANGECONFIGITEM_H
