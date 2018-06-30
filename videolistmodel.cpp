#include "videolistmodel.h"
#include <QProcess>
#include <QDebug>
VideoListModel::VideoListModel(QObject *parent)
    :QJsonListModel(parent)
{

}

void VideoListModel::query(QString query)
{
    qDebug() << "Searching for" << query;
    QProcess p;
    p.start("./ytclick.py",
            QStringList{} << query << "json");
    if( !p.waitForFinished())
    {
        qDebug("ERROR");
        qDebug() << p.errorString();
    }
    auto ba = p.readAll();
    qDebug() << "Json: " << ba;
    load(ba);
    qDebug() << m_roleNumbers.keys();
    emit listChanged();
}

void VideoListModel::play(QString url)
{
    qDebug() << "PLay " << url;
    QProcess p;
    p.start("mpv", QStringList{} << url);
    p.waitForFinished();
    qDebug() << p.readAll();
    qDebug() << "Played";
}
