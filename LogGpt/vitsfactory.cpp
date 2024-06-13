#include "vitsfactory.h"


VitsApi *VITSFactory::getVitsApi(QObject *parent)
{
    return new VitsApi(parent);

}
