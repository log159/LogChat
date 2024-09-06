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

class NetworkManager : public QObject {
    Q_OBJECT
public:
    NetworkManager(QObject *parent = nullptr) : QObject(parent) {
        manager = new QNetworkAccessManager(this);
        connect(manager, &QNetworkAccessManager::finished, this, &NetworkManager::replyFinished);
    }

    void fetchUrl(const QUrl &url) {
        QNetworkRequest request(url);
        manager->get(request);
    }

private slots:
    void replyFinished(QNetworkReply *reply) {
        if (reply->error()) {
            qDebug() << "ERROR:" << reply->errorString();
        }
        // 读取并解析 JSON 数据
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        if (doc.isNull()) {
            qDebug() << "Failed to parse JSON";
            return;
        }

        QJsonObject jsonObject = doc.object();

        // 假设我们只关心 "VITS" 数组
        if (jsonObject.contains("VITS")) {
            QJsonArray vitsArray = jsonObject["VITS"].toArray();
            for (int i = 0; i < vitsArray.size(); ++i) {
                QJsonObject vitsObj = vitsArray.at(i).toObject();
                qDebug() << "ID:" << vitsObj["id"].toInt();
                qDebug() << "Languages:" << vitsObj["lang"].toArray();
                qDebug() << "Name:" << vitsObj["name"].toString(); // 这里将自动处理 UTF-8 编码的汉字
            }
        }

        reply->deleteLater();
    }

private:
    QNetworkAccessManager *manager;
};
#endif // NETWORKMANAGER_H
