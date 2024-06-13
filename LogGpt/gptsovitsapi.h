#ifndef GPTSOVITSAPI_H
#define GPTSOVITSAPI_H

#include <QObject>

#include "config.h"
#include "vitsbase.h"

class GPTSoVitsApi : public VITSBase
{
    Q_OBJECT
public:
    explicit GPTSoVitsApi(QObject *parent = nullptr);

    void start(QString url);

signals:

public slots:
};

#endif // GPTSOVITSAPI_H
