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

    void start(const QString& text);

signals:

public slots:
};

#endif // GPTSOVITSAPI_H
