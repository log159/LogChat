#include "vitsapi.h"

VitsApi::VitsApi(QObject *parent) : VITSBase(parent)
{

}

void VitsApi::start(const QString& text)
{

    QString url = Config::get_VITS_URL().arg(text);
    qDebug()<<"向 vits 端发送请求"<<url;
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    QNetworkReply* reply = manager->get(QNetworkRequest(QUrl(url)));
    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200) {

                QDateTime now = QDateTime::currentDateTime();
                QString str=TimeInformation::getDateTimeHashString();
                QString currentDir = (ConfigConstWay::get_TRUE_WAY(ConfigConstWay::OUTPUT_WAV_WAY)).arg(str);

                QFile outputFile(currentDir);
                if (outputFile.open(QIODevice::WriteOnly)) {
                    outputFile.write(reply->readAll());
                    outputFile.close();
                    //发送音频路径
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
