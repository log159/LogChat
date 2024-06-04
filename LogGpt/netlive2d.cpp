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

            receiveHandle(data);
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

void NetLive2D::receiveHandle(QString strHandle)
{
    //窗口句柄
    if(strHandle.at(0)==QChar('H')){
        QString input = strHandle;
        QRegularExpression regex("Hwnd:(\\d+);");
        QRegularExpressionMatch match = regex.match(input);

        if (match.hasMatch()) {
            QString number = match.captured(1);
            HWND hwnd = reinterpret_cast<HWND>(number.toInt());
            if (IsWindow(hwnd)) {
                qDebug()<<"找到Window,更新窗口句柄";
                ConfigLive2d::setLive2DWindow(hwnd);
            }
        }


    }
    //位置信息
    if(strHandle.at(0)==QChar('P')){
        QRegularExpression re("Pos:([-\\d\\.]+),([-\\d\\.]+),([-\\d\\.]+),([-\\d\\.]+);");
        QRegularExpressionMatch match = re.match(strHandle);

        if (match.hasMatch()) {
            float x = match.captured(1).toFloat();
            float y = match.captured(2).toFloat();
            float z = match.captured(3).toFloat();
            float w = match.captured(4).toFloat();

            //转化为Qt坐标系保存
            ConfigLive2d::setModelX(x);
            ConfigLive2d::setModelY(ConfigWindow::getDesktopHeight()-y);
            ConfigLive2d::setMouseX(z);
            ConfigLive2d::setMouseY(ConfigWindow::getDesktopHeight()-w);

    //        qDebug() << "Extracted values:" << x << y << z << w;
            emit myMousePass();

        } else {
            qDebug() << "No match found!";
        }
    }

}
