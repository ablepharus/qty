#include "videolistmodel.h"
#include <QProcess>
#include <QDebug>
#include <QJsonObject>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>
#include "youtubesearcher.h"

VideoListModel::VideoListModel(QObject *parent)
    :QJsonListModel(parent)
{
    connect(&m_queryWatcher, &QFutureWatcher<QByteArray>::finished,
            this, &VideoListModel::finishedQuery);
}

void VideoListModel::query(QString query, int count)
{
    qDebug() << "Searching for: " << query;

    this->m_isBusy = true;
    emit isBusyChanged(true);

    QFuture<QByteArray> fu = QtConcurrent::run(&m_yt, &YoutubeDl::query, query, count);
    m_queryWatcher.setFuture(fu);
}

void VideoListModel::setModelData(QByteArray jsonBa)
{
    QByteArray *json = &jsonBa;
    qDebug() << "Read query size: " << json->size();
    auto jd = QJsonDocument{};
    QJsonParseError err;
    jd = QJsonDocument::fromJson(*json, &err);
    if(err.error != QJsonParseError::NoError || jd.isNull())
        qDebug() <<"Parsing Error: " << err.error << err.offset;
    qDebug() << "Is Arr, Is Obj, IsEmpty: " << jd.isArray() << jd.isObject() << jd.isEmpty();
    qDebug() << "Keys: " << jd.object().keys() << jd.object().count();
    qDebug() << "Arr?: " << jd["entries"].toArray().size() << jd.array().count();
    qDebug() << "Entries size: " << jd.object()["entries"].toArray().size();
    load(jd["entries"].toArray());

    //qDebug() << m_roleNumbers.keys();
    emit listChanged();
    this->m_isBusy = false;
    emit isBusyChanged(false);
}

void VideoListModel::finishedQuery()
{
    setModelData(m_queryWatcher.result());
}
