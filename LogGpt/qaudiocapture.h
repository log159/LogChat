#ifndef QAUDIOCAPTURE_H
#define QAUDIOCAPTURE_H

#include <QObject>
#include <QAudioInput>
#include <QFile>

class QAudioCapture : public QObject
{
    Q_OBJECT
public:
    explicit QAudioCapture(QObject *parent = nullptr);

    void startRecord(QString filename); //开始录音
    void stopRecord(); //停止录音
    ~QAudioCapture();

private:
    QAudioInput *m_audioInput; //录音输入对象
    QFile *m_file; //文件储存

signals:

};

#endif // QAUDIOCAPTURE_H
