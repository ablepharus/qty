#ifndef VIDEOLISTMODEL_H
#define VIDEOLISTMODEL_H

#include <QObject>
#include <QSettings>
#include <QProcess>
#include "qjsonlistmodel.h"
#include "youtubesearcher.h"

// Take a query, run `ytclick` with query parameters
// hold resulting information

class VideoListModel : public QJsonListModel
{
    Q_OBJECT
public:
    explicit VideoListModel(QObject *parent = nullptr);

    Q_PROPERTY(bool isBusy MEMBER m_isBusy NOTIFY isBusyChanged)
protected:
    bool m_isBusy{false};
    YoutubeDl m_yt;

public slots:
        void query(QString query, int count=10);
private slots:
        void setModelData(QByteArray jsonBa);
    signals:
        void listChanged();
        void isBusyChanged(const bool isBusy);
private:
        QThread *_t{nullptr};
        QByteArray *arr;


public slots:
    void finishedQuery();
private:
    QList<QFuture<QByteArray>> futures;
    QFutureWatcher<QByteArray> m_queryWatcher;
};

#endif // VIDEOLISTMODEL_H
