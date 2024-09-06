#ifndef VITSAPI_H
#define VITSAPI_H

#include <QObject>
#include <QString>
#include <QDateTime>

#include "vitsbase.h"


class VitsApi : public VITSBase
{
    Q_OBJECT
public:
    explicit VitsApi(QObject *parent = nullptr);

    void start(const QString& text);

signals:

public slots:
};

#endif // VITSAPI_H
