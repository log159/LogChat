#ifndef VITSAPI_H
#define VITSAPI_H

#include <QObject>
#include <QNetworkReply>
#include <QString>
#include <QDateTime>

#include "vitsbase.h"
#include "config.h"

class VitsApi : public VITSBase
{
    Q_OBJECT
public:
    explicit VitsApi(QObject *parent = nullptr);

    void start(QString url);

signals:

public slots:
};

#endif // VITSAPI_H
