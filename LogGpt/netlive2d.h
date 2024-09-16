#ifndef NETLIVE2D_H
#define NETLIVE2D_H

//新的方式 Unity端作为服务器
#define IS_CUSTOMER
//旧的方式 C++端作为服务器
//#define IS_SERVER

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QRegularExpression>
#include <QTimer>
#include <QSharedPointer>

#include "configlive2d.h"
#include "configwindow.h"
#include "configfileio.h"
#include "configconstway.h"

class NetLive2D : public QObject
{
    Q_OBJECT
private:
    static bool IsConnect;
private:
#ifdef IS_SERVER
    QTcpServer* m_TcpServer;
#endif
    QTcpSocket* m_TcpSocket;
public:

    static NetLive2D* getInstance();

    void startListen();
    void stopListen();
    static bool getIsConnect();
    static void setIsConnect(bool bo);

public:

    void receiveHandle(QString strHandle);
    void sendHandle(QString strHandle);


signals:
    void myMousePass();

public slots:
};

#endif // NETLIVE2D_H
