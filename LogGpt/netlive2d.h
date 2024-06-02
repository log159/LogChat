#ifndef NETLIVE2D_H
#define NETLIVE2D_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QString>
#include <QDebug>

class NetLive2D : public QObject
{
private:
    static bool isConnect;
public:
    explicit NetLive2D(QObject *parent = nullptr);

    void startListen();
    static bool getIsConnect();
    static void setIsConnect(bool value);

private:
    void init();
    void initConnect();
private:
    QTcpServer* tcpServer=nullptr;
    QTcpSocket* tcpSocket=nullptr;
signals:

public slots:
    void sendHandle(QString);
};

#endif // NETLIVE2D_H
