#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QObject>
#include <QProcess>
#include <QJsonArray>
#include <QModelIndexList>

#include <VLCQtQml/QmlPlayer.h>
#include <VLCQtCore/MediaListPlayer.h>
#include <VLCQtCore/MediaPlayer.h>
#include <VLCQtCore/Video.h>

#include <vlc/vlc.h>
#include <vlc/libvlc_media.h>

class Playlist;

class YoutubePlayer : public QObject
{
    Q_OBJECT
public:
    YoutubePlayer(QObject *parent=nullptr);
    Q_PROPERTY(bool showVideo MEMBER m_showVideo NOTIFY showVideoChanged)
    Q_PROPERTY(VlcQmlPlayer* player READ getPlayer)
    Q_PROPERTY(Playlist* playlist MEMBER m_playlist)

    VlcQmlPlayer* getPlayer();
public slots:
    void play(QJsonArray formats);
    void play(QUrl video, QUrl audio);

    void seekFwd();
    void seekBck();
    void seekFwdFwd();
    void seekBckBck();

    void next();
    void prev();
    void maybeNext();
    void playFirst();

    void on_playlist_mediaAdded(QModelIndexList newMedia);
    void on_playlist_mediaReset();
protected:
    VlcMediaPlayer *mediaPlayer;
    VlcInstance *vlcInstance;
    VlcMedia *media{nullptr};
    VlcQmlPlayer *qmlPlayer;
    Playlist *m_playlist;

    bool m_showVideo{true};
signals:
    void showVideoChanged(bool showVideo);
};

using VideoPlayer = YoutubePlayer;
#endif // VIDEOPLAYER_H
