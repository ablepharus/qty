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
    explicit QJsonListModel(QObject *parent = nullptr);
    void load(QByteArray arr);
    void load(QJsonArray arr);

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    QHash<int, QByteArray> roleNames() const override {	return m_roleNames;	}
protected:
    QJsonArray jsonObjects;
    QHash<int, QByteArray> m_roleNames;
    QHash<QByteArray, int> m_roleNumbers;
    void generateRoleNames();
};

#endif // QJSONLISTMODEL_H
