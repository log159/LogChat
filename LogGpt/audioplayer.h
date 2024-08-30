#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMediaContent>
#include <QDebug>

class AudioPlayer : public QObject
{
    Q_OBJECT
public:
    AudioPlayer(const QUrl &audioUrl, QObject *parent = nullptr);
    ~AudioPlayer();

private slots:
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);

private:
    QMediaPlayer *player;
signals:
    void endof();
};

#endif // AUDIOPLAYER_H
