#include "baiduapi.h"

BaiduApi::BaiduApi(QObject *parent) : QObject(parent)
{
    init();
    initConnect();
}

void BaiduApi::init()
{
    m_Manager=new QNetworkAccessManager(this);
}

void BaiduApi::initConnect()
{
    connect(m_Manager,&QNetworkAccessManager::finished,this,&BaiduApi::replyFinished);
}
int BaiduApi::functionData(const QString &str)
{
    QString cText=removeInvalid(str);
    qDebug()<<"百度翻译处理前："<<cText;
    QString MD5;
    char salt[60];
    sprintf(salt,"%d",rand());  //获取随机数
    QString sign=QString("%1%2%3%4").arg(Config::get_BAIDU_APID()).arg(cText).arg(salt).arg(Config::get_BAIDU_KEY());//连接加密文件 宏MY_APID 是你的开发账号 宏MY_APID_KEY 是你的开发者密匙

    QByteArray strByteArray = QCryptographicHash::hash(sign.toUtf8(),QCryptographicHash::Md5);
    MD5.append(strByteArray.toHex());//生成md5加密文件
    QString myurl=QString("http://api.fanyi.baidu.com/api/trans/vip/translate?"
           "q=%1&from=%2&to=%3&appid=%4""&salt=%5&sign=%6")
           .arg(cText)
           .arg(Config::get_LANGUAGE_V().at(Config::get_BAIDU_FROM_ID()))
           .arg(Config::get_LANGUAGE_V().at(Config::get_BAIDU_TO_ID()))
           .arg(Config::get_BAIDU_APID()).arg(salt).arg(MD5);//连接上传文本 MY_APID 是你的开发账号
    m_Manager->get(QNetworkRequest(QUrl(myurl)));//发送上传；

    return 1;

}
int BaiduApi::replyFinished(QNetworkReply *reply)
{

    QJsonParseError jsonError;
    QByteArray all=reply->readAll();//获得api返回值
   /* 大概是这样的一个东西
   {"from":"en","to":"zh","trans_result":[{"src":"apple","dst":"\u82f9\u679c"}]}
   你需要解码 */
    QJsonDocument json = QJsonDocument::fromJson(all, &jsonError);
    QJsonObject object = json.object();//json转码；
    QString cResult;
    if(object.contains("error_code"))
    {
        int nResult=object.value("error_code").toInt();

        switch (nResult) {
        case 52001:
            cResult ="52001 请求超时 重试";
            break;
        case 52002:
            cResult ="52002 系统错误 重试";
            break;
        case 54000:
            cResult ="54000 必填参数为空";
            break;
        case 54001:
            cResult ="54001 签名错误";
            break;
        case 54003:
            cResult ="54003 速度过快访问频率受限";
            break;
        case 54004:
            cResult ="54004 账户余额不足";
            break;
        case 54005:
            cResult ="54005 请求频繁";
            break;
        case 58002:
            cResult ="58002 服务关闭";
            break;
        default:
            cResult ="百度翻译其他错误";
            break;
        }
    }
    else {
        QJsonArray value = object.value("trans_result").toArray();//一次解码
        /*
         {"from":"en","to":"zh",
           "trans_result":[{"src":"apple","dst":"\u82f9\u679c"}]}
           第一次解码
         */
        QJsonObject object1=value.at(0).toObject();//二次解码开【】括号；
        /*
           {"src":"apple","dst":"\u82f9\u679c"}
           第二次解码
         */
        //from=object.value("from").toString();
        cResult=object1.value("dst").toString();//得到翻译结果
    }

    emit replyFinishedData(cResult);
    reply->deleteLater();
    return 1;

}

QString BaiduApi::removeInvalid(const QString &str)
{
    QString handleStr=str;
    handleStr.remove(QChar('\n'));
    handleStr.remove(QChar('\r'));
    handleStr.remove(QChar('\t'));
    handleStr.remove(QChar(' '));
    return handleStr;

}
