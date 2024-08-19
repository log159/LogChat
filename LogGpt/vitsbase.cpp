#include "vitsbase.h"

VITSBase::VITSBase(QObject *parent) : QObject(parent)
{

}

VITSBase::~VITSBase()
{
    qDebug()<<"------------------VITS端析构------------------";
}
