#ifndef QJSONLISTMODEL_H
#define QJSONLISTMODEL_H
#include <QAbstractListModel>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QtCore/qglobal.h>


class QJsonListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit QJsonListModel(QObject *parent = nullptr);
    QModelIndexList load(QByteArray arr);
    QModelIndexList load(QJsonArray arr);
    QModelIndexList add(QJsonArray arr);
    QModelIndex add(QJsonObject obj);

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    QHash<int, QByteArray> roleNames() const override {	return m_roleNames;	}
    QHash<QByteArray, int> roleNumbers() const { return m_roleNumbers; }

    bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count,
                  const QModelIndex &destinationParent, int destinationChild) override;
    Q_INVOKABLE bool move(int fromIndex, int toIndex);
protected:
    QJsonArray jsonObjects;
    QHash<int, QByteArray> m_roleNames;
    QHash<QByteArray, int> m_roleNumbers;
    void generateRoleNames();
};

#endif // QJSONLISTMODEL_H
