#ifndef NETTCP_H
#define NETTCP_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QString>
#include <QDebug>

class NetTcp : public QObject
{
    Q_OBJECT
public:
    explicit NetTcp(QObject *parent = nullptr);

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

#endif // NETTCP_H
