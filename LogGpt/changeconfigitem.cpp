#include "changeconfigitem.h"

ChangeConfigItem::ChangeConfigItem()
{

}

void ChangeConfigItem::printInformation(ChangeConfigItem &item)
{
    qDebug()<<item.getName()<<"\n"
            <<item.getDefaultValue()<<"\n"
            <<item.getMinValue()<<"\n"
            <<item.getMaxValue()<<"\n";

}
