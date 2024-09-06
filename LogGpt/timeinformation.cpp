#include "timeinformation.h"


const QString TimeInformation::getDateTimeString()
{

    QDateTime now = QDateTime::currentDateTime();
    QString str="%1%2%3%4%5%6";
    int year = now.date().year();
    int month = now.date().month();
    int day = now.date().day();
    int hour = now.time().hour();
    int minute = now.time().minute();
    int second = now.time().second();
    str = str.arg(year).arg(month).arg(day).arg(hour).arg(minute).arg(second);
    return str;
}

const QString TimeInformation::getDateTimeHashString()
{
    static long long hash_num=0;
    QDateTime now = QDateTime::currentDateTime();
    QString str="%1%2%3%4%5%6";
    int year = now.date().year();
    int month = now.date().month();
    int day = now.date().day();
    int hour = now.time().hour();
    int minute = now.time().minute();
    int second = now.time().second();
    str = str.arg(year).arg(month).arg(day).arg(hour).arg(minute).arg(second);
    str+="_"+QString::number(hash_num);
    ++hash_num;
    return str;
}
