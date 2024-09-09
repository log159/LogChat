#include "netlive2d.h"


bool NetLive2D::IsConnect = false;
bool NetLive2D::getIsConnect()
{
    return IsConnect;
}

void NetLive2D::setIsConnect(bool value)
{
    IsConnect = value;
}

NetLive2D::NetLive2D(QObject *parent) : QObject(parent)
{
    init();
    initConnect();
}


void NetLive2D::startListen()
{

    QString address_str=ConfigFileIO::getOtherConfig(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::CONFIG_UNITY_WAY),"SERVERS","ADDRESS");
    QString port_str=ConfigFileIO::getOtherConfig(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::CONFIG_UNITY_WAY),"SERVERS","PORT");

    qDebug()<<"服务器端启动监听";
    QHostAddress specificAddress(address_str);
    unsigned short port=port_str.toUShort();
    // 检查地址是否有效
    if (!specificAddress.isNull()) {
        if (m_TcpServer->listen(specificAddress, port)) {
            qDebug() << "TCP server is listening on" << specificAddress.toString() << ":" << port;
        } else {
            qDebug() << "Failed to listen on" << specificAddress.toString() << ":" << port;
        }
    } else {
        qDebug() << "Invalid address:" << specificAddress.toString();
    }
}

void NetLive2D::init()
{
    m_TcpServer=new QTcpServer(this);
}

void NetLive2D::initConnect()
{
    connect(m_TcpServer,&QTcpServer::newConnection,this,[=](){
        m_TcpSocket=m_TcpServer->nextPendingConnection();
        qDebug()<<"连接到客户端";
        IsConnect=true;
        connect(m_TcpSocket,&QTcpSocket::readyRead,this,[=](){
            QByteArray data=m_TcpSocket->readAll();
            qDebug()<<"来自客户端的请求"<<data;

            receiveHandle(data);
        });
        connect(m_TcpSocket,&QTcpSocket::disconnected,this,[=](){
            m_TcpSocket->close();
            m_TcpSocket->deleteLater();
            qDebug()<<"已和客户端断开连接";
            IsConnect=false;
        });

    });

}

void NetLive2D::sendHandle(QString strHandle)
{
    if(m_TcpSocket==nullptr){return ;}
    QString msg=strHandle;
    m_TcpSocket->write(msg.toUtf8());
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
