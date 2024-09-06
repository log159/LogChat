#ifndef VITSFACTORY_H
#define VITSFACTORY_H

#include "config.h"
#include "singletonbase.h"
#include "vitsapi.h"
#include "gptsovitsapi.h"
#include "selfvits.h"

class VITSFactory:public SingletonBase
{
public:

    static VITSBase* getNew(QObject* parent);

private:

    static VitsApi* getVitsApi(QObject* parent);

    static GPTSoVitsApi* getGPTSoVitsApi(QObject* parent);

    static SelfVits* getSelfVitsApi(QObject* parent);
};

#endif // VITSFACTORY_H
