#ifndef SELFVITS_H
#define SELFVITS_H

#include <QObject>
#include <QString>
#include <QDateTime>

#include "vitsbase.h"

class SelfVits : public VITSBase
{
    Q_OBJECT
public:
    explicit SelfVits(QObject *parent = nullptr);

    void start(const QString& text);

signals:

public slots:
};

#endif // SELFVITS_H
