#include "audioplayer.h"


AudioPlayer::AudioPlayer(const QUrl &audioUrl, QObject *parent) : QObject(parent), player(new QMediaPlayer(this)) {
    player->setMedia(QMediaContent(audioUrl));
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &AudioPlayer::onMediaStatusChanged);
    player->play();
}
AudioPlayer::~AudioPlayer() {
    player->stop();
    qDebug()<<"------------------音频端析构------------------";
}

void AudioPlayer::onMediaStatusChanged(QMediaPlayer::MediaStatus status) {
    if (status == QMediaPlayer::EndOfMedia) {
        emit endof();
        this->deleteLater();
        qDebug() << "------------音频播放资源释放-----------";
    }
}
