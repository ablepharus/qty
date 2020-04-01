#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>
#include <QJsonObject>
#include "qjsonlistmodel.h"
#include "videolistmodel.h"

class QAbstractListModel;
class QJsonListModel;
class VideoListModel;

class Playlist : public QObject
{
    Q_OBJECT
    friend class YoutubePlayer;
public:
    explicit Playlist(QObject *parent = nullptr);

    Q_PROPERTY(VideoListModel* model MEMBER m_model)
    Q_PROPERTY(int currentTrackIndex MEMBER m_currentTrackIndex NOTIFY currentTrackChanged)

    QJsonObject currentTrack();
    QJsonObject nextTrack();
    QJsonObject prevTrack();

signals:
    void mediaAdded(QModelIndexList newMedia);
    void mediaReset(); // model changed, propagate
    void currentTrackChanged();
public slots:
    void addEntry(QJsonObject obj);
    void addEntry(const QJsonListModel &model, int index);
    void copyEntry(QAbstractListModel *model, int index);
    void copyMyEntry(int index);

    void resetMedia(); // model changed, handle changes

    void playAt(int index);
protected:
    VideoListModel *m_model;
    int m_currentTrackIndex{-1};
};

#endif // PLAYLIST_H
