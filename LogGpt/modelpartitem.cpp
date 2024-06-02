#include "modelpartitem.h"

ModelPartItem::ModelPartItem()
{

}

void ModelPartItem::printInformation(ModelPartItem &partItem)
{
    qDebug()<<partItem.getName()<<"\n"
            <<partItem.getDefaultValue()<<"\n"
            <<partItem.getMinValue()<<"\n"
            <<partItem.getMaxValue()<<"\n";

}
