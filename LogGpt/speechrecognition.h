#ifndef SPEECHRECOGNITION_H
#define SPEECHRECOGNITION_H

#include <qhttppost.h>

#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QHostInfo>
#include <QFile>
#include <QMessageBox>
#include <QIODevice>

class speechRecognition : public QObject
{
    Q_OBJECT
public:
    explicit speechRecognition(QObject *parent = nullptr);

    QString speechIdentify(QString client_id, QString client_secret, QString filename); //开始识别
    QString getJsonValue(QByteArray ba,QString key);

private:
    QString accessToken; //token

signals:

};

#endif // SPEECHRECOGNITION_H
