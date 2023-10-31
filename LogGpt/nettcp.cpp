#include "nettcp.h"

NetTcp::NetTcp(QObject *parent) : QObject(parent)
{
//    init();
//    initConnect();
}

void NetTcp::init()
{
    //服务器端启动
    qDebug()<<"服务器端启动";
    tcpServer=new QTcpServer(this);
    unsigned short port=QString("8899").toUShort();
    tcpServer->listen(QHostAddress::Any,port);

}

void NetTcp::initConnect()
{
    connect(tcpServer,&QTcpServer::newConnection,this,[=](){
        tcpSocket=tcpServer->nextPendingConnection();
        qDebug()<<"连接到客户端";
        connect(tcpSocket,&QTcpSocket::readyRead,this,[=](){
            QByteArray data=tcpSocket->readAll();
            qDebug()<<"来自客户端的请求"<<data;
        });
        connect(tcpSocket,&QTcpSocket::disconnected,this,[=](){
            tcpSocket->close();
            tcpSocket->deleteLater();
            qDebug()<<"已和客户端断开连接";
        });

    });

}

void NetTcp::sendHandle(QString strHandle)
{
    if(tcpSocket==nullptr){return ;}
    QString msg=strHandle;
    tcpSocket->write(msg.toUtf8());
    qDebug()<<"服务器端发送信息"<<msg;
}
