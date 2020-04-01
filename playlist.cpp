#include "playlist.h"
#include "videoplayer.h"
#include "videolistmodel.h"
#include "qjsonlistmodel.h"

#include <QJsonObject>

Playlist::Playlist(QObject *parent) : QObject(parent),
    m_model{new VideoListModel}
{
    setObjectName("playlist");
    connect(m_model, &QAbstractListModel::modelReset,
            this, &Playlist::resetMedia);
}

void Playlist::addEntry(QJsonObject obj)
{
    qDebug() << "Adding obj: " << obj["title"];
    emit mediaAdded({QList<QModelIndex>{} << m_model->add(obj)});
}

void Playlist::addEntry(const QJsonListModel &model, int index)
{
    qDebug() << "Modelindex: " << index;
    auto d = model.data(model.index(index), model.roleNames().keys("json")[0]);
    qDebug() << "Getting entry " << index << " from model " << &model;
    addEntry(d.value<QJsonObject>());
}

void Playlist::copyEntry(QAbstractListModel *model, int index)
{
    auto &m = *model;
    auto d = m.data(m.index(index), m.roleNames().keys("json")[0]);
    qDebug() << "Getting entry " << index << " from model " << model
             << " with role " << m.roleNames().keys("json")[0];
             // << " data: " << d;
    addEntry(d.value<QJsonObject>());
}

void Playlist::copyMyEntry(int index)
{
    auto model = dynamic_cast<VideoListModel*>(sender());

    auto d = model->data(model->index(index), model->roleNames().keys("json")[0]);
    qDebug() << "Getting entry " << index << " from model " << model
             << " data: " << d;
    addEntry(d.value<QJsonObject>());
}

void Playlist::resetMedia()
{
    qDebug() << "resetting media";
    dynamic_cast<YoutubePlayer*>(parent())->play(
                m_model->index(0).data(m_model->roleNames().key("json")).value<QJsonObject>()["formats"].toArray());
    m_currentTrackIndex = 0;
    emit mediaReset();
    emit currentTrackChanged();
}

QJsonObject Playlist::currentTrack()
{
    return m_model->index(m_currentTrackIndex).data(m_model->roleNames().key("json")).value<QJsonObject>();
}
QJsonObject Playlist::nextTrack()
{
    return m_model->index(m_currentTrackIndex + 1).data(m_model->roleNames().key("json")).value<QJsonObject>();
}

QJsonObject Playlist::prevTrack()
{
    return m_model->index(m_currentTrackIndex - 1).data(m_model->roleNames().key("json")).value<QJsonObject>();
}

void Playlist::playAt(int index)
{
    if(index < 0 || index >= m_model->rowCount())
        qDebug() << "playAt " << index << " not in range";
    m_currentTrackIndex = index;
    emit currentTrackChanged();
    ((YoutubePlayer*)parent())->play(currentTrack()["formats"].toArray());
}
