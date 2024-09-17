#include "transformation.h"



QString Transformation::IntToStringF1(int num)
{
    QString str="";
    if(num<0)str+="-";
    str+=(QString::number(qAbs(int(num)/100))
          +"."
          +QString::number(qAbs(int(num)/10%10)));
    return str;
}

QString Transformation::IntToStringF2(int num)
{
    QString str="";
    if(num<0)str+="-";
    str+=(QString::number(qAbs(int(num)/100))
          +"."
          +QString::number(qAbs(int(num)/10%10))
          +QString::number(qAbs(int(num)%10)));
    return str;

}
