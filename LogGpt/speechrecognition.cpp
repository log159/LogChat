#include "speechrecognition.h"

speechRecognition::speechRecognition(QObject *parent)
    : QObject{parent}
{

}

/*
 * 语音识别相关请求
*/

//发送识别
QString speechRecognition::speechIdentify(QString client_id, QString client_secret, QString filename)
{
    //获取token
    QString token_url = QString("http://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=%1&client_secret=%2").arg(client_id).arg(client_secret);
    QMap<QString,QString> headers;
    headers.insert(QString("Content-Type"),QString("audio/pcm;rate=16000"));
    QByteArray requestdata; //发送内容
    QByteArray replydata; //返回内容
    Qhttppost httputil;
    bool success = httputil.postSyn(token_url,headers,requestdata,replydata);
    if(success)
    {
        QString key = "access_token";
        accessToken = getJsonValue(replydata,key);
        qDebug()<<"获取到token"<<accessToken;
    }
    else return "";

    //获取文件
    QFile file;
    file.setFileName(filename);
    file.open(QIODevice::ReadOnly);
    requestdata = file.readAll();
    file.close();
    replydata.clear();

    //发送http请求
    QString baidu_speech = QString("http://vop.baidu.com/server_api?dev_pid=1537&cuid=%1&token=%2").arg("LAPTOP-71LN9B3Q").arg(accessToken);
    bool result = httputil.postSyn(baidu_speech,headers,requestdata,replydata);
    if(result)
    {
        QString key = "result";
        QString text = getJsonValue(replydata, key);
        qDebug()<<"获取到result"<<text;
        return text;
    }
    else
    {
        QMessageBox::warning(NULL,"语音识别","请求识别");
    }
    return "";
}
QString speechRecognition::getJsonValue(QByteArray ba,QString key)
{
    QJsonParseError parseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(ba,&parseError);
    if(parseError.error == QJsonParseError::NoError)
    {
        if(jsonDocument.isObject())
        {
            QJsonObject jsonObj = jsonDocument.object();
            if(jsonObj.contains(key))
            {
                QJsonValue jsonVal = jsonObj.value(key);
                if(jsonVal.isString()) //字符串
                {
                    return jsonVal.toString();
                }
                else if(jsonVal.isArray()) //数组
                {
                    QJsonArray arr = jsonVal.toArray();
                    QJsonValue jv = arr.at(0);
                    return jv.toString();
                }
            }
        }
    }
    return "";
}
