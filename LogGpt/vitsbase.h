#ifndef VITSBASE_H
#define VITSBASE_H

#include <QObject>
#include <QString>


class VITSBase : public QObject
{
    Q_OBJECT
public:
    explicit VITSBase(QObject *parent = nullptr);

    virtual void start(QString url) = 0;

signals:
    void playerWay(QString);
public slots:
};

#endif // VITSBASE_H
