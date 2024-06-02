#include "netlive2d.h"

bool NetLive2D::isConnect = false;
bool NetLive2D::getIsConnect()
{
    return isConnect;
}

void NetLive2D::setIsConnect(bool value)
{
    isConnect = value;
}

NetLive2D::NetLive2D(QObject *parent) : QObject(parent)
{
    init();
    initConnect();
}

void NetLive2D::startListen()
{
    qDebug()<<"服务器端启动监听";
    unsigned short port=QString("8899").toUShort();
    tcpServer->listen(QHostAddress::Any,port);
}

void NetLive2D::init()
{
    tcpServer=new QTcpServer(this);
}

void NetLive2D::initConnect()
{
    connect(tcpServer,&QTcpServer::newConnection,this,[=](){
        tcpSocket=tcpServer->nextPendingConnection();
        qDebug()<<"连接到客户端";
        isConnect=true;
        connect(tcpSocket,&QTcpSocket::readyRead,this,[=](){
            QByteArray data=tcpSocket->readAll();
            qDebug()<<"来自客户端的请求"<<data;
        });
        connect(tcpSocket,&QTcpSocket::disconnected,this,[=](){
            tcpSocket->close();
            tcpSocket->deleteLater();
            qDebug()<<"已和客户端断开连接";
            isConnect=false;
        });

    });

}

void NetLive2D::sendHandle(QString strHandle)
{
    if(tcpSocket==nullptr){return ;}
    QString msg=strHandle;
    tcpSocket->write(msg.toUtf8());
    qDebug()<<"服务器端发送信息"<<msg;
}
