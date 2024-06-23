#ifndef VITSBASE_H
#define VITSBASE_H

#include <QObject>
#include <QString>
#include <QNetworkReply>
#include "config.h"

class VITSBase : public QObject
{
    Q_OBJECT
public:
    explicit VITSBase(QObject *parent = nullptr);

    virtual ~VITSBase();

    virtual void start(QString text) = 0;

signals:
    void playerWay(QString);
public slots:
};

#endif // VITSBASE_H
