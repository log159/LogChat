#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>

#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>

class NetworkManager : public QObject {
    Q_OBJECT

private:
    QNetworkAccessManager* m_Manager    =nullptr;
public:
    NetworkManager(QObject *parent = nullptr);

    void fetchUrl(const QUrl &url);

private slots:
    void replyFinished(QNetworkReply *reply);

signals:
    void sendSpeakers(QVector<QString>);
};
#endif // NETWORKMANAGER_H
