#include "qjsonlistmodel.h"
#include <QDebug>
#include <QJsonObject>

QJsonListModel::QJsonListModel(QObject *parent)
    :QAbstractListModel(parent)
{
}

QVariant QJsonListModel::data(const QModelIndex &index, int role) const
{
    if(role < Qt::UserRole) {
        qDebug() << "Nope: QJsonListModel::data with non UserRole";
        return QVariant{};
    }
    return jsonObjects[index.row()].toObject()[this->m_roleNames[role]].toVariant();
}

QVariant QJsonListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return "Header";
}

int QJsonListModel::rowCount(const QModelIndex &parent) const
{
    return this->jsonObjects.size();
}

void QJsonListModel::generateRoleNames()
{
    m_roleNames.clear();
    int id = 1;
    qDebug() << "generateRoleNames: " << jsonObjects.first().toObject();
    for (auto key : jsonObjects.first().toObject().keys()) {
        auto new_id = Qt::UserRole + id++;
        m_roleNames.insert(new_id, key.toUtf8());
        m_roleNumbers.insert(key.toUtf8(), new_id);
        qDebug() << "adding role " << key;
    }
}

void QJsonListModel::load(QByteArray arr)
{
    QJsonParseError err;
    auto jsonDocument = QJsonDocument::fromJson(arr, &err);
    qDebug() << err.error;
    beginResetModel();
    jsonObjects = jsonDocument.array();
    qDebug() << jsonDocument.array().size();
    qDebug() << jsonDocument.array()[0].toObject().keys();
    qDebug() << jsonDocument.array()[1].toObject()["name"];
    qDebug() << QJsonValue(jsonDocument.object()["name"]);
    qDebug() << jsonDocument.object();
    generateRoleNames();
    endResetModel();
}
