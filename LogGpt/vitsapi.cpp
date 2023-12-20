#include "vitsapi.h"

VitsApi::VitsApi(QObject *parent) : QObject(parent)
{

}

void VitsApi::start(QString url)
{
    qDebug()<<"向 vits-api 端发送请求"<<url;
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    QNetworkReply* reply = manager->get(QNetworkRequest(QUrl(url)));
    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200) {
                QString currentDir = Config::get_OUTPUT_WAV_WAY();
                QFile outputFile(currentDir);
                if (outputFile.open(QIODevice::WriteOnly)) {
                    outputFile.write(reply->readAll());
                    outputFile.close();
                    //播放音频
                    emit playerWay(currentDir);

                } else {
                    qDebug() << "Failed to open output file";
                }
            } else {
                qDebug() << "HTTP error:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            }
        } else {
            qDebug() << "Network error:" << reply->error();
        }
        reply->deleteLater();
        qDebug()<<"------------VITS 请求资源释放-----------";
    });

}
