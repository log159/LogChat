#ifndef GLOBAL_H
#define GLOBAL_H
#include <QMap>
#include <QString>

//基本功能配置
enum EnIks{
    LLM_CHATGPT,    /*ChatGPT 语言大模型*/
    LLM_XFXH,       /*讯飞星火 语言大模型*/
    LLM_DEEPSEEK,   /*深度求索 语言大模型*/
    MT_BDFY,        /*百度翻译语言转换*/
    STT_BDYUN       /*百度云语音转文字*/
};

//每一组ID,KEY,SECRET数据的枚举在INI文件的属性名字
static QMap<EnIks,QString>IksM={
    {EnIks::LLM_CHATGPT,    "LLM_CHATGPT"},
    {EnIks::LLM_XFXH,       "LLM_XFXH"},
    {EnIks::LLM_DEEPSEEK,   "LLM_DEEPSEEK"},
    {EnIks::MT_BDFY,        "MT_BDFY"},
    {EnIks::STT_BDYUN,      "STT_BAIDUYUN"}

};
struct IKS{
    QString id;
    QString key;
    QString secret;
};

//URL配置
enum EnUrl{
    URL_CHATGPT_BASEURL,
    URL_DEEPSEEK_BASEURL,
    URL_VITSSELF_RULEURL
};
static      QMap<EnUrl,QString>UrlM={
    {URL_CHATGPT_BASEURL,"URL_CHATGPT_BASEURL"},
    {URL_DEEPSEEK_BASEURL,"URL_DEEPSEEK_BASEURL"},
    {URL_VITSSELF_RULEURL,"URL_VITSSELF_RULEURL"}
};


enum EnUser{
    NULL_MARK,                  /*NULL*/
    VITS_MODEL_SELECT,          /*Vits 模型选择*/
    VITS_URL_ADDRESS,           /*Vits Url地址*/
    VITS_URL_PORT,              /*Vits Url端口*/
    GPTSOVITS_URL_ADDRESS,      /*GPT-SoVits地址*/
    GPTSOVITS_URL_PORT,         /*GPT-SoVits端口*/
    GPTSOVITS_LANGUAGE,         /*GPT-SoVits目标语种*/
    ENABLE_ROLE,                /*是否启用角色扮演*/
    ENABLE_SOUND,               /*是否启用语音*/
    ENABLE_BAIDUFANYI,          /*是否启用百度翻译*/
    ENABLE_LATERLANGUAGE,       /*是否启用翻译后的语言用来显示*/
    ENABLE_RESERVE,             /*是否保留上下文记忆*/
    LLM_MODEL_ID,               /*LLM模型ID 0 chatgpt 1讯飞星火*/
    XFXH_MODEL_ID,              /*讯飞星火模型ID*/
    CHATGPT_MODEL_ID,           /*ChatGpt模型ID*/
    VITS_ID,                    /*vits模型ID*/
    SPEAKER_ID,                 /*讲述人ID*/
    EMOTION_ID,                 /*情感控制ID*/
    BAIDU_FROM_ID,              /*原语种ID*/
    BAIDU_TO_ID,                /*翻译后语种ID*/
    RESERVE_LONG,               /*上下文保留最大长度*/
    CHARACTER_CONFIG,           /*角色设定信息*/
    USERNAME,                   /*用户名*/
    CHARACTERNAME,              /*角色名*/
    CHARACTERGENDER,            /*角色性别*/
    AUDIOSYNTHESIS,             /*音频合成规则*/
    AUDIOBREAKSTR,              /*音频分割字符串*/
};

static      QMap<EnUser,QString>UserM={
    {NULL_MARK,"NULL"},
    {VITS_MODEL_SELECT,"VITS_MODEL_SELECT"},
    {VITS_URL_ADDRESS,"VITS_URL_ADDRESS"},
    {VITS_URL_PORT,"VITS_URL_PORT"},
    {GPTSOVITS_URL_ADDRESS,"GPTSOVITS_URL_ADDRESS"},
    {GPTSOVITS_URL_PORT,"GPTSOVITS_URL_PORT"},
    {GPTSOVITS_LANGUAGE,"GPTSOVITS_LANGUAGE"},
    {ENABLE_ROLE,"ENABLE_ROLE"},
    {ENABLE_SOUND,"ENABLE_SOUND"},
    {ENABLE_BAIDUFANYI,"ENABLE_BAIDUFANYI"},
    {ENABLE_LATERLANGUAGE,"ENABLE_LATERLANGUAGE"},
    {ENABLE_RESERVE,"ENABLE_RESERVE"},
    {LLM_MODEL_ID,"LLM_MODEL_ID"},
    {XFXH_MODEL_ID,"XFXH_MODEL_ID"},
    {CHATGPT_MODEL_ID,"CHATGPT_MODEL_ID"},
    {VITS_ID,"VITS_ID"},
    {SPEAKER_ID,"SPEAKER_ID"},
    {EMOTION_ID,"EMOTION_ID"},
    {BAIDU_FROM_ID,"BAIDU_FROM_ID"},
    {BAIDU_TO_ID,"BAIDU_TO_ID"},
    {RESERVE_LONG,"RESERVE_LONG"},
    {CHARACTER_CONFIG,"CHARACTER_CONFIG"},
    {USERNAME,"USERNAME"},
    {CHARACTERNAME,"CHARACTERNAME"},
    {CHARACTERGENDER,"CHARACTERGENDER"},
    {AUDIOSYNTHESIS,"AUDIOSYNTHESIS"},
    {AUDIOBREAKSTR,"AUDIOBREAKSTR"},
};

static const QVector<QString>           VITS_MODEL_V        ={"vits","gpt-sovits","self-vits"};
static const QVector<QString>           VITS_ALL_V          ={"vits","bert-vits2","w2v2-vits"};             //全部vits模型
static const QVector<QString>           LANGUAGE_V          ={"auto","jp","zh","en","yue","wyw","cht"};     //百度翻译全部语种
static const QVector<QString>           GPTSOVITS_LANGUAGE_V={"zh","ja","en"};                              //GPT-SoVits全部语种
static const QVector<QString>           CHATGPT_MODEL_V     ={
    "gpt-3.5-turbo",
    "gpt-3.5-turbo-0125",
    "gpt-3.5-turbo-1106",
    "gpt-3.5-turbo-instruct",
    "gpt-4-turbo",
    "gpt-4-turbo-2024-04-09",
    "gpt-4-turbo-preview",
    "gpt-4-0125-preview",
    "gpt-4-1106-preview",
    "gpt-4",
    "gpt-4-0613",
    "gpt-4-0314",
    "gpt-4o-mini",
    "gpt-4o-mini-2024-07-18",
    "gpt-4o",
    "gpt-4o-2024-05-13",
    "gpt-4o-2024-08-06",
    "chatgpt-4o-latest"
};//全部ChatGPT模型
static const QVector<QString>           XFXH_MODEL_V        ={"general","generalv2","generalv3","generalv3.5"};           //全部讯飞星火模型
static const QMap<QString,bool>         LIVE2DENABLEINIT_M  ={
    {"look_enable",true}
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
    {"audio_smooth",100},
    {"win_topapha",0}
};//全部Live2D PARAM默认值
static       QMap<QString,QString>      LIVE2DSTRING_M={
    {"model_name","null"},
    {"file_path","null"},
    {"model_description","null"}
};//全部Live2D STRING默认值


#endif // GLOBAL_H
