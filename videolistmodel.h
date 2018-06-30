#ifndef VIDEOLISTMODEL_H
#define VIDEOLISTMODEL_H

#include <QObject>
#include "qjsonlistmodel.h"

class VideoListModel : public QJsonListModel
{
        Q_OBJECT
    public:
        explicit VideoListModel(QObject *parent = 0);
public slots:
        void query(QString query);
        void play(QString url);
    signals:
        void listChanged();
};

#endif // VIDEOLISTMODEL_H
