#include "audioplayer.h"


AudioPlayer::AudioPlayer(const QUrl &audioUrl, QObject *parent) : QObject(parent), m_Player(new QMediaPlayer(this)) {

    initConnect();
    m_Player->setMedia(QMediaContent(audioUrl));
    if(Config::get_USER(::EnUser::ENABLE_SELFVOLUME).toInt()!=0){
        int value=Config::get_USER(::EnUser::AUDIOVOLUME).toInt();
        if(0<=value && value<=100)
            m_Player->setVolume(value);
    }
    m_Player->play();
}
AudioPlayer::~AudioPlayer() {
    m_Player->stop();
    qDebug()<<"------------------音频端析构------------------";
}

void AudioPlayer::initConnect()
{
    connect(m_Player, &QMediaPlayer::mediaStatusChanged, this, &AudioPlayer::onMediaStatusChanged);
}

void AudioPlayer::onMediaStatusChanged(QMediaPlayer::MediaStatus status) {
    if (status == QMediaPlayer::EndOfMedia) {
        emit endof();
        this->deleteLater();
        qDebug() << "------------音频播放资源释放-----------";
    }
}
