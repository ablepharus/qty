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
    if(role == m_roleNames.key("json"))
    {
        auto o = jsonObjects[index.row()].toObject();
        //qDebug() << "accessing json: " << o;
        return o;
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
    // qDebug() << "generateRoleNames: " << jsonObjects.first().toObject();
    for (auto key : jsonObjects.first().toObject().keys()) {
        auto new_id = Qt::UserRole + id++;
        m_roleNames.insert(new_id, key.toUtf8());
        m_roleNumbers.insert(key.toUtf8(), new_id);
        //qDebug() << "adding role " << key;
    }
    m_roleNames.insert(Qt::UserRole + id, "json");
    m_roleNumbers.insert("json", id++);
}

QModelIndexList QJsonListModel::load(QByteArray arr)
{
    QJsonParseError err;
    auto jsonDocument = QJsonDocument::fromJson(arr, &err);
    qDebug() << err.error;
    return load(jsonDocument.array());
}

struct _Counter {
    _Counter(int start=0):m_c(start) {}
    int operator()() {return m_c++;}
    int m_c;
};

#include <functional>
template <typename _A>
struct _Generator :public _Counter {
    _Generator(std::function<_A(int)> fn, int start=0): _Counter(start) {this->fn=fn;}
    std::function<_A(int)> fn;
    _A operator()() {return fn(m_c++);}
};


#include <algorithm>
QModelIndexList QJsonListModel::load(QJsonArray arr)
{
    beginResetModel();
    jsonObjects = arr;

    qDebug() << arr.size();
    qDebug() << arr[0].toObject().keys();
    generateRoleNames();
    endResetModel();
    QVector<QModelIndex> l{jsonObjects.size()};/*
    QVector<int> _v{jsonObjects.size(), 0};
    std::transform(_v.begin(), _v.begin() + jsonObjects.size() - 1,
                   _v.begin() + 1, [](int a){qDebug() << "ääääh" << a; return ++a;});
    std::transform(_v.begin(), _v.end(),
                   l.begin(), [this](int a){return index(a);});
    qDebug() << "Listy " << _v << "size: " << _v.size()
             << "should be " << jsonObjects.size() << " l " << l;

    return {l.toList()};*/
    QVector<QModelIndex> ret{arr.size()};

    //qDebug() << "DDYYYYYIIINNG";
    std::generate(ret.begin(), ret.end(),
                  _Generator<QModelIndex>{[this](int i){return this->index(i);},
                                          rowCount() - arr.size()});
    return ret.toList();
}

QModelIndexList QJsonListModel::add(QJsonArray arr)
{
    if(rowCount() == 0)
        return {QList<QModelIndex>{} << load(arr)};
    beginInsertRows(index(0).parent(), rowCount(), rowCount() + arr.count() - 1);
    jsonObjects += arr;
    endInsertRows();
    QVector<QModelIndex> ret{arr.size()};

    std::generate(ret.begin(), ret.end(),
                  _Generator<QModelIndex>{[this](int i){return this->index(i);},
                                          rowCount() - arr.size()});
    return {ret.toList()};
}

QModelIndex QJsonListModel::add(QJsonObject obj)
{
    if(obj.isEmpty())
        return {};
    if(rowCount() == 0)
        return load(QJsonArray{obj})[0];
    auto newIndex = rowCount();
    beginInsertRows({}, newIndex, newIndex);
    // beginInsertRows(index(0).parent(), rowCount(), rowCount());
    jsonObjects.append(obj);
    endInsertRows();
    qDebug() << "New rowcount " << rowCount(index(0)) << ":" << rowCount()
             << " json size " << jsonObjects.size();
    return index(newIndex);
}

bool QJsonListModel::moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild)
{
    /*  On models that support this, moves count rows starting with the given sourceRow under parent sourceParent to row destinationChild under parent destinationParent.

        Returns true if the rows were successfully moved; otherwise returns false.
    */
    QVector<QJsonValue> items{count};
    // sourceAffectedRows
    int sarMin = sourceRow, sarMax = sourceRow + count - 1;
    auto newIndex = destinationChild < sourceRow ?
                destinationChild
              : destinationChild - count + 1;
    beginMoveRows(sourceParent, sarMin, sarMax,
                  sourceParent,
                  destinationChild < sourceRow ? newIndex
                                               : newIndex + 1);

    auto it = items.begin();
    for (int i = sarMin; i <= sarMax; i++)
        *it++ = (jsonObjects.takeAt(i));
    qDebug() << "(source row, destination row) "
             << sourceRow << destinationChild
             << " newIndex " << newIndex;
    it = items.begin();
    for (int i = 0; i < count; i++)
        jsonObjects.insert(newIndex + i, *it++);
    endMoveRows();

    return true;
    /*
     *  bool QAbstractItemModel::beginMoveRows(const QModelIndex &sourceParent, int sourceFirst, int sourceLast, const QModelIndex &destinationParent, int destinationChild)
     *
        Specify the first and last row numbers for the span of rows in the source parent you want to move in the model. Also specify the row in the destination parent to move the span to.
        For example, as shown in the diagram, we move three rows from row 2 to 4 in the source, so sourceFirst is 2 and sourceLast is 4. We move those items to above row 2 in the destination, so destinationChild is 2.

            beginMoveRows(sourceParent, 2, 4, destinationParent, 2);

        This moves the three rows rows 2, 3, and 4 in the source to become 2, 3 and 4 in the destination. Other affected siblings are displaced accordingly.

     */
}

bool QJsonListModel::move(int fromIndex, int toIndex)
{
    return moveRows({}, fromIndex, 1,
                    {}, toIndex);
}
