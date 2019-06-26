#include "videoplayer.h"
#include <QDebug>
#include <QJsonArray>
#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>

#include <QJsonObject>


YoutubePlayer::YoutubePlayer(QObject *parent)
    :QObject(parent)
{
    //vlcInstance = new VlcInstance(VlcCommon::args(), this);
    //mediaPlayer = new VlcMediaPlayer(vlcInstance);
    qmlPlayer = new VlcQmlPlayer(this);
    //qmlPlayer->removePlayer();
    //qmlPlayer->setPlayer(mediaPlayer);
}
// TODO maybe i need a destructor for this->media
// libvlc_release(vlcinstance->core
// delete vlcInstance, mediaPlayer, qmlPlayer

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

    auto _lm = libvlc_media_new_location(qmlPlayer->instance()->core(),
                                         video.toString().toLatin1().data());
    libvlc_media_slaves_add(_lm, libvlc_media_slave_type_audio, 0,
                            audio.toString().toLatin1().data());
    auto nm = new VlcMedia{_lm};
    //qmlPlayer->setUrl(video);
    //mediaPlayer->open(nm);

    qmlPlayer->open(nm);
    //delete media;
    //libvlc_media_release(media->core());
    //media = nm;
}

VlcQmlPlayer* YoutubePlayer::getPlayer()
{
    return qmlPlayer;
}
