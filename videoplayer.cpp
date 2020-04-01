#include "videoplayer.h"
#include <QDebug>
#include <QJsonArray>
#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>

#include <QJsonObject>
#include <QAbstractListModel>

#include "playlist.h"

YoutubePlayer::YoutubePlayer(QObject *parent)
    :QObject(parent),
      qmlPlayer(new VlcQmlPlayer(this)),
      m_playlist(new Playlist(this))
{
    setObjectName("player");
    //vlcInstance = new VlcInstance(VlcCommon::args(), this);
    //mediaPlayer = new VlcMediaPlayer(vlcInstance);
    //qmlPlayer = new VlcQmlPlayer(this);
    //m_playlist = new Playlist(this);
    this->metaObject()->connectSlotsByName(this);
    mediaPlayer = qmlPlayer->player();
    //qmlPlayer->removePlayer();
    //qmlPlayer->setPlayer(mediaPlayer);
    connect(qmlPlayer->player(), &VlcMediaPlayer::end,
            this, &YoutubePlayer::maybeNext);
}
void YoutubePlayer::play(QJsonArray formats)
{
    QString audio, video;
//    for(auto it=formats.begin();
//        it != formats.end() && (audio.isNull() || video.isNull());
//        it++)
    for(auto it=formats.end();
        it!= formats.begin() && (audio.isNull() || video.isNull());
        it--)
    {
        auto obj = (*it).toObject();
        if(audio.isEmpty() && obj["acodec"].toString() != "none")
            audio = obj["url"].toString();

        if(video.isEmpty() && obj["vcodec"].toString() != "none"){
            qDebug() << "Found video? " << obj["format_note"];
            video = obj["url"].toString();
           }
    }
    qDebug() << video << " - " << audio;
    play(QUrl{video}, QUrl{audio});
}

void YoutubePlayer::play(QUrl video, QUrl audio)
{
    qDebug() << "Video Url: " << video.toString().toLatin1().data();

    auto v = new VlcMedia{video.toString(), qmlPlayer->instance()};
    libvlc_media_slaves_add(v->core(), libvlc_media_slave_type_audio, 0,
                            audio.toString().toLatin1().data());

    qmlPlayer->open(v);
}

void YoutubePlayer::next()
{
    auto a = m_playlist->nextTrack()["formats"].toArray();
    if(a.empty())
        return;

    qDebug() << "Next: " << a;
    qmlPlayer->pause();
    play(a);
    m_playlist->m_currentTrackIndex++;

    emit m_playlist->currentTrackChanged();
}

void YoutubePlayer::maybeNext()
{
    next();
}

void YoutubePlayer::playFirst()
{
    m_playlist->m_currentTrackIndex = 0;
    auto a = m_playlist->currentTrack()["formats"].toArray();
    if(a.empty())
        return;

    qmlPlayer->pause();
    play(a);
    emit m_playlist->currentTrackChanged();
}

void YoutubePlayer::prev()
{
    auto a = m_playlist->prevTrack()["formats"].toArray();
    if(a.empty())
        return;

    qDebug() << "Prev: " << a;
    qmlPlayer->pause();
    play(a);
    m_playlist->m_currentTrackIndex--;
    emit m_playlist->currentTrackChanged();
}

VlcQmlPlayer* YoutubePlayer::getPlayer()
{
    return qmlPlayer;
}

void YoutubePlayer::seekFwd()
{
    qmlPlayer->setTime(mediaPlayer->time() + 10 * 1000);
}
void YoutubePlayer::seekBck()
{
    qmlPlayer->setTime(mediaPlayer->time() - 10 * 1000);
}

void YoutubePlayer::seekFwdFwd()
{
    qmlPlayer->setTime(mediaPlayer->time() + 60 * 1000);
}

void YoutubePlayer::seekBckBck()
{
    qmlPlayer->setTime(mediaPlayer->time() - 60 * 1000);
}

void YoutubePlayer::on_playlist_mediaAdded(QModelIndexList newMedia)
{
    auto model = m_playlist->property("model").value<QAbstractListModel*>();
    qDebug() << "My playlist got some media";
    if(model->rowCount() == newMedia.size()
            && qmlPlayer->state() == Vlc::Paused)
        play(newMedia[0].data(model->roleNames().key("formats")).value<QJsonArray>());
}

void YoutubePlayer::on_playlist_mediaReset()
{
    qDebug() << "AAAAAA RESEEEEEEEET";
}
