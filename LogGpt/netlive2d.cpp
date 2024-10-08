#include "netlive2d.h"


bool NetLive2D::IsConnect = false;
NetLive2D *NetLive2D::getInstance()
{
    static NetLive2D instance;
    return &instance;
}
bool NetLive2D::getIsConnect()
{
    return IsConnect;
}

void NetLive2D::setIsConnect(bool bo)
{
    IsConnect = bo;
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

#ifdef IS_SERVER
void NetLive2D::startListen()
{
    if(m_TcpServer!=nullptr){
        disconnect(m_TcpServer,nullptr,nullptr,nullptr);
        delete  m_TcpServer;
        m_TcpServer=nullptr;
    }

    m_TcpServer=new QTcpServer(this);
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
#endif



#ifdef IS_CUSTOMER
void NetLive2D::startListen()
{
    if(m_TcpSocket!=nullptr){
        disconnect(m_TcpSocket,nullptr,nullptr,nullptr);
        delete m_TcpSocket;
        m_TcpSocket=nullptr;
    }
    QString address_str = ConfigFileIO::getOtherConfig(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::CONFIG_UNITY_WAY), "SERVERS", "ADDRESS");
    QString port_str = ConfigFileIO::getOtherConfig(ConfigConstWay::get_TRUE_WAY(ConfigConstWay::CONFIG_UNITY_WAY), "SERVERS", "PORT");

    QHostAddress serverAddress(address_str);
    unsigned short port = port_str.toUShort();

    if (!serverAddress.isNull()) {
        qDebug() << "客户端尝试连接服务器";
        m_TcpSocket=new QTcpSocket; // Create a new QTcpSocket instance
        m_TcpSocket->connectToHost(serverAddress, port); // Connect to the server

        if (m_TcpSocket->waitForConnected(5000)) { // Wait for up to 5 seconds
            IsConnect = true;
            qDebug() << "客户端成功连接到服务器" << serverAddress.toString() << ":" << port;
        } else {
            qDebug() << "客户端无法连接到服务器" << serverAddress.toString() << ":" << port;
        }

        // Connect signals after connection attempt
        connect(m_TcpSocket, &QTcpSocket::readyRead, this, [=]() {
            QByteArray data = m_TcpSocket->readAll();
            qDebug() << "收到来自服务器的响应:" << data;

            receiveHandle(data); // Handle the received data
        });

        connect(m_TcpSocket, &QTcpSocket::disconnected, this, [=]() {
            m_TcpSocket->close();
            IsConnect = false;
            qDebug() << "已与服务器断开连接";
        });

    } else {
        qDebug() << "无效的服务器地址:" << serverAddress.toString();
    }

}

void NetLive2D::stopListen()
{
    qDebug()<<"尝试与服务器断开连接";
    if(m_TcpSocket!=nullptr)
        m_TcpSocket->disconnectFromHost();

}

void NetLive2D::sendHandle(QString strHandle)
{
    if(IsConnect==false)return;
    if(m_TcpSocket == nullptr) { return; }
    QString msg = strHandle;
    m_TcpSocket->write(msg.toUtf8()); // Send message to the server
    qDebug() << "客户端发送信息:" << msg;
}
#endif
