#ifndef BAIDUAPI_H
#define BAIDUAPI_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>

#include "config.h"
class BaiduApi : public QObject
{
    Q_OBJECT
private:
    QNetworkAccessManager* m_Manager        =nullptr;

public:
    explicit BaiduApi(QObject *parent = nullptr);
    int functionData(const QString& str);
private:
    void init();
    void initConnect();
private:
    int replyFinished(QNetworkReply *reply);
signals:
    void replyFinishedData(QString);

public slots:

};

#endif // BAIDUAPI_H
