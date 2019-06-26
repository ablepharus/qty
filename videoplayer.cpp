#include "videoplayer.h"
#include <QDebug>
VideoPlayer::VideoPlayer()
{

}

void VideoPlayer::play(QString url)
{
    qDebug() << "PLay " << url;
    auto p = new QProcess;
    p->start("mpv", QStringList{} << url);
    //p.waitForFinished();
    //qDebug() << p.readAll();
    qDebug() << "Played";
    player_processes.append(p);
}
