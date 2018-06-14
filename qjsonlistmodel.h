#ifndef QJSONLISTMODEL_H
#define QJSONLISTMODEL_H
#include <QAbstractListModel>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>


class QJsonListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit QJsonListModel(QObject *parent = 0);
    void load(QByteArray arr);

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    QHash<int, QByteArray> roleNames() const {	return m_roleNames;	}
private:
    QJsonArray jsonObjects;
    QHash<int, QByteArray> m_roleNames;
    void generateRoleNames();
};

#endif // QJSONLISTMODEL_H
