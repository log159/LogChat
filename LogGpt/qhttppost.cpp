#include "qhttppost.h"

#include <QObject>

Qhttppost::Qhttppost(QObject *parent)
{

}

bool Qhttppost::postSyn(QString url, QMap<QString, QString> headerdata, QByteArray requestData, QByteArray &replydata)
{
    //发送请求对象
    QNetworkAccessManager manager;
    QNetworkRequest request;
    request.setUrl(url);
    QMapIterator<QString, QString> it(headerdata); //迭代器
    while(it.hasNext()) //遍历map
    {
        it.next();
        request.setRawHeader(it.key().toLatin1(),it.value().toLatin1());
    }
    //发送请求
    QNetworkReply *reply = manager.post(request, requestData);
    QEventLoop waiting;
    //等待返回请求
    connect(reply, &QNetworkReply::finished, &waiting,&QEventLoop::quit);
    waiting.exec(); //时间循环等待信号
    //收到返回数据
    if(reply != nullptr && reply->error() == QNetworkReply::NoError)
    {
        replydata = reply->readAll();
        qDebug()<<"post返回信息"<<replydata;
        return true;
    }
    else
    {
        qDebug()<<"post返回错误"<<replydata;
        return true;
    }
}
