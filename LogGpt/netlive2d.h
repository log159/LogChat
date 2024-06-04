#ifndef NETLIVE2D_H
#define NETLIVE2D_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QRegularExpression>
#include <QTimer>

#include "configlive2d.h"
#include "configwindow.h"

class NetLive2D : public QObject
{
    Q_OBJECT
private:
    static bool isConnect;
public:
    NetLive2D(QObject *parent = nullptr);

    void startListen();
    static bool getIsConnect();
    static void setIsConnect(bool value);

private:

    void init();
    void initConnect();
    void receiveHandle(QString strHandle);
private:
    QTcpServer* tcpServer=nullptr;
    QTcpSocket* tcpSocket=nullptr;

signals:
    void myMousePass();

public slots:
    void sendHandle(QString);
};

#endif // NETLIVE2D_H
