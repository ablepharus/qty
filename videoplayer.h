#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QObject>
#include <QProcess>

class VideoPlayer : public QObject
{
    Q_OBJECT
public:
    VideoPlayer();
public slots:
    void play(QString url);
protected:
    QList<QProcess*> player_processes;
};

#endif // VIDEOPLAYER_H
