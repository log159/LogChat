#ifndef VITSFACTORY_H
#define VITSFACTORY_H

#include "singletonbase.h"
#include "vitsapi.h"

class VITSFactory:public SingletonBase
{
public:

    static VitsApi* getVitsApi(QObject* parent);
};

#endif // VITSFACTORY_H
