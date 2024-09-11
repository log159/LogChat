#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMediaContent>
#include <QDebug>

#include "config.h"

class AudioPlayer : public QObject
{
    Q_OBJECT
private:
    QMediaPlayer* m_Player;
public:
    AudioPlayer(const QUrl &audioUrl, QObject *parent = nullptr);
    ~AudioPlayer();

private:
    void initConnect();

private slots:
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);


signals:
    void endof();
};

#endif // AUDIOPLAYER_H
