#ifndef VITSBASE_H
#define VITSBASE_H

#include <QObject>
#include <QString>
#include <QNetworkReply>
#include <QDebug>

#include "config.h"
#include "timeinformation.h"

class VITSBase : public QObject
{
    Q_OBJECT
public:

    explicit VITSBase(QObject *parent = nullptr);

    virtual ~VITSBase();

    virtual void start(const QString& text) = 0;

signals:
    void playerWay(QString);

    void quit();
public slots:
};

#endif // VITSBASE_H
