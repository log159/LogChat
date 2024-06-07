#ifndef QHTTPPOST_H
#define QHTTPPOST_H

#include <QObject>
#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

class Qhttppost : QObject
{
    Q_OBJECT
public:
    explicit Qhttppost(QObject *parent = nullptr);
    bool postSyn(QString url, QMap<QString, QString> headerdata, QByteArray requestData, QByteArray &replydata); //提交
};

#endif // QHTTPPOST_H
