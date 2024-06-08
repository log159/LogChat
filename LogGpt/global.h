#ifndef GLOBAL_H
#define GLOBAL_H
#include <QMap>
#include <QString>

enum EnIks{
    LLM_CHATGPT,    /*ChatGPT 语言大模型*/
    LLM_XFXH,       /*讯飞星火语言大模型*/
    MT_BDFY,        /*百度翻译语言转换*/
    STT_BDYUN       /*百度云语音转文字*/
};

//每一组ID,KEY,SECRET数据的枚举在INI文件的属性名字
static QMap<EnIks,QString>IksM={
    {EnIks::LLM_CHATGPT,    "LLM_CHATGPT"},     /*ChatGPT 语言大模型*/
    {EnIks::LLM_XFXH,       "LLM_XFXH"},        /*讯飞星火语言大模型*/
    {EnIks::MT_BDFY,        "MT_BDFY"},         /*百度翻译语言转换*/
    {EnIks::STT_BDYUN,      "STT_BAIDUYUN"}     /*百度云语音转文字*/

};
struct IKS{
    QString id;
    QString key;
    QString secret;
};

static const QVector<QString>           VITS_ALL_V={"vits","bert-vits2","w2v2-vits"};               //全部vits模型
static const QVector<QString>           LANGUAGE_V={"auto","jp","zh","en","yue","wyw","cht"};       //全部百度翻译语种
static const QVector<QString>           CHATGPT_MODEL_V={"gpt-3.5-turbo"};                          //全部ChatGPT模型
static const QVector<QString>           XFXH_MODEL_V={"general","generalv2","generalv3"};           //全部讯飞星火模型
static const QMap<QString,bool>         LIVE2DENABLEINIT_M ={
    {"look_enable",true},
    {"top_enable",true}
};//全部Live2D ENABLE默认值
static const QMap<QString,int>          LIVE2DPARAMINIT_M= {
    {"model_size",300},
    {"model_x",0},
    {"model_y",0},
    {"model_rx",0},
    {"model_ry",0},
    {"model_rz",0},
    {"mouse_speed",15},
    {"eye_time",250},
    {"eye_deviation",200},
    {"eye_speed",1000},
    {"audio_add",1000},
    {"audio_smooth",100}
};//全部Live2D PARAM默认值
static       QMap<QString,QString>      LIVE2DSTRING_M={
    {"model_name","null"},
    {"file_path","null"},
    {"model_description","null"}
};//全部Live2D STRING默认值

#endif // GLOBAL_H
