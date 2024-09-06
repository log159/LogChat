#ifndef TIMEINFORMATION_H
#define TIMEINFORMATION_H

#include <QObject>
#include <QDateTime>
#include <QString>

#include "singletonbase.h"

class TimeInformation : public SingletonBase
{

public:

    static const QString getDateTimeString();

    static const QString getDateTimeHashString();
};

#endif // TIMEINFORMATION_H
