#include "gptsovitsapi.h"

GPTSoVitsApi::GPTSoVitsApi(QObject *parent) : VITSBase(parent)
{

}

void GPTSoVitsApi::start(const QString& text)
{
    QString url = Config::get_GPTSOVITS_URL().arg(text);
    qDebug()<<"向 gptsovits-api 端发送请求"<<url;
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    QNetworkReply* reply = manager->get(QNetworkRequest(QUrl(url)));
    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200) {

                QDateTime now = QDateTime::currentDateTime();
                QString str=TimeInformation::getDateTimeHashString();

                QString currentDir = (ConfigConstWay::get_TRUE_WAY(ConfigConstWay::OUTPUT_WAV_WAY)).arg(str);
                qDebug()<<"WAV输出路径："<<currentDir;

                QFile outputFile(currentDir);
                if (outputFile.open(QIODevice::WriteOnly)) {
                    outputFile.write(reply->readAll());
                    outputFile.close();
                    //播放音频
                    emit playerWay(currentDir);

                } else {
                    qDebug() << "Failed to open output file";
                    emit quit();
                }
            } else {
                qDebug() << "HTTP error:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
                emit quit();
            }
        } else {
            qDebug() << "Network error:" << reply->error();
            emit quit();
        }
        reply->deleteLater();
        qDebug()<<"------------VITS 请求资源释放-----------";
    });

}
