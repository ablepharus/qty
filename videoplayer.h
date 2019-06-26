#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QObject>
#include <QProcess>
#include <QJsonArray>

#include <VLCQtQml/QmlPlayer.h>
#include <VLCQtCore/MediaListPlayer.h>
#include <VLCQtCore/MediaPlayer.h>
#include <VLCQtCore/Video.h>

#include <vlc/vlc.h>
#include <vlc/libvlc_media.h>


class YoutubePlayer : public QObject
{
    Q_OBJECT
public:
    YoutubePlayer(QObject *parent=nullptr);
    Q_PROPERTY(bool showVideo MEMBER m_showVideo NOTIFY showVideoChanged)
    Q_PROPERTY(VlcQmlPlayer* player READ getPlayer)

    VlcQmlPlayer* getPlayer();
public slots:
    void play(QJsonArray formats);
    void play(QUrl video, QUrl audio);
protected:
    VlcMediaPlayer *mediaPlayer;
    VlcInstance *vlcInstance;
    VlcMedia *media{nullptr};
    VlcQmlPlayer *qmlPlayer;

    bool m_showVideo{true};
signals:
    void showVideoChanged(bool showVideo);
};

using VideoPlayer = YoutubePlayer;
#endif // VIDEOPLAYER_H
