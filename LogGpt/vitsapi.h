#ifndef VITSAPI_H
#define VITSAPI_H

#include <QObject>
#include <QNetworkReply>
#include <QString>
#include <QDateTime>

#include "config.h"

class VitsApi : public QObject
{
    Q_OBJECT
public:
    explicit VitsApi(QObject *parent = nullptr);

    void start(QString url);

signals:
    void playerWay(QString);

public slots:
};

#endif // VITSAPI_H
