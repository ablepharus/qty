#ifndef YOUTUBESEARCHER_H
#define YOUTUBESEARCHER_H

#include <QObject>

class YoutubeSearcher : public QObject
{
    Q_OBJECT
public:
    explicit YoutubeSearcher(QObject *parent = nullptr);

signals:

public slots:
};

#endif // YOUTUBESEARCHER_H
