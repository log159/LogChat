#include "qaudiocapture.h"
#include <QMessageBox>
#include <QDebug>

QAudioCapture::QAudioCapture(QObject *parent)
    : QObject(parent),
      m_audioInput(nullptr),
      m_file(nullptr)
{

}

/*
 * 使用startRecord开始录音，并指定录音后的保存位置
 * 使用stopRecord停止录音并保存
*/

//开始录音
void QAudioCapture::startRecord(QString filename)
{
    QAudioDeviceInfo audio_device_info = QAudioDeviceInfo::defaultInputDevice(); //获取输入设备
    qDebug()<<"输入设备"<<audio_device_info.deviceName();
    if(!audio_device_info.isNull())
    {
        //文件操作
        m_file = new QFile;
        m_file->setFileName(filename);
        m_file->open(QIODevice::WriteOnly | QIODevice::Truncate);
        //初始设置
        QAudioFormat format;
        format.setSampleRate(16000); //采样频率
        format.setChannelCount(1); //通道数
        format.setSampleSize(16); //设置每次得到的样本位值
        format.setCodec("audio/pcm"); //编码方式
        if(!audio_device_info.isFormatSupported(format)) //判断是否支持改格式
        {
            format = audio_device_info.nearestFormat(format);
        }
        //开始录音
        m_audioInput = new QAudioInput(format,this);
        m_audioInput->start(m_file);
    }
}
//停止录音
void QAudioCapture::stopRecord()
{
    if(m_audioInput) m_audioInput->stop();
    if(m_file)
    {
        m_file->close();
        delete m_file; //删除文件
        m_file = nullptr;
    }
}



//析构函数
QAudioCapture::~QAudioCapture()
{
    if(m_audioInput)
    {
        delete m_audioInput;
        m_audioInput = nullptr;
    }
    if(m_file)
    {
        delete m_file;
        m_file = nullptr;
    }
}
