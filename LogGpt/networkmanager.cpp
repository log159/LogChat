#include "networkmanager.h"

NetworkManager::NetworkManager(QObject *parent) : QObject(parent) {
    m_Manager = new QNetworkAccessManager(this);
    connect(m_Manager, &QNetworkAccessManager::finished, this, &NetworkManager::replyFinished);
}
void NetworkManager::fetchUrl(const QUrl &url) {
    QNetworkRequest request(url);
    m_Manager->get(request);
}

void NetworkManager::replyFinished(QNetworkReply *reply) {
    if (reply->error()) {
        qDebug() << "ERROR:" << reply->errorString();
    }
    // 读取并解析 JSON 数据
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if (doc.isNull()) {
        emit sendSpeakers({});
        return;
    }
    QJsonObject jsonObject = doc.object();

    qDebug()<<jsonObject;

    QVector<QString> modelsV={"VITS","BERT-VITS2","W2V2-VITS","GPT-SOVITS"};
    QVector<QString> dataV;
    for(int i=0;i<modelsV.size();++i){
        if (jsonObject.contains(modelsV[i])) {
            QJsonArray vitsArray = jsonObject[modelsV[i]].toArray();
            for (int j = 0; j < vitsArray.size(); ++j) {
                QJsonObject vitsObj = vitsArray.at(j).toObject();
                QString lang="[";
                for(auto& val:vitsObj["lang"].toArray().toVariantList()){
                    lang+=val.toString()+",";
                }
                lang[lang.size()-1]=QChar(']');
                dataV.push_back(modelsV[i]+"|"+"id"+QString::number(vitsObj["id"].toInt())+"|"+vitsObj["name"].toString()+"|"+lang);
                qDebug()<<dataV.back();
            }
        }
    }
    emit sendSpeakers(dataV);
    reply->deleteLater();
}
