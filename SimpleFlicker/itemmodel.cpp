#include "itemmodel.h"

ItemModel::ItemModel(QObject *parent) : QAbstractItemModel(parent)
{
    rc = 0;
    cc = 1;
}

QModelIndex ItemModel::index(int row, int column, const QModelIndex &parent) const
{    
    if (row < rc  && row >= 0 && column < cc && column >= 0)
    {
        auto item = catalog->getItem(row);
        return createIndex(row, 0);
    }
    return QModelIndex();
}

QModelIndex ItemModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int ItemModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return rc;
}

int ItemModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return cc;
}

QVariant ItemModel::data(const QModelIndex &index, int role) const
{
    if (index.row() >= rc)
    {
        return QVariant();
    }
    Item a = catalog->getItem(index.row());

    switch (role)
    {
        case Qt::DisplayRole:
        {
            return a.Name;
        }
        case Qt::DecorationRole:
        {
            return a.thumbnail;
        }
        case Qt::SizeHintRole:
        {
            return cellSize;
        }
    }
    return QVariant();
}

bool ItemModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (parent.isValid())
        return false;
    beginInsertRows(parent, row, row + count -1);
    rc+= count;
    endInsertRows();

    return true;
}

bool ItemModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (parent.isValid())
        return false;

    beginRemoveRows(parent, row, row);
    rc-= count;
    endRemoveRows();
    return true;
}

bool ItemModel::hasChildren(const QModelIndex &parent) const
{
    if (parent.isValid())
        return false;
    return true;
}

void ItemModel::setCatalog(Catalog *catalog)
{
    this->catalog = catalog;
}

void ItemModel::addItem(Item astroFile, int row)
{
    insertRow(row);
}

void ItemModel::updateItem(Item astroFile, int row)
{
    auto index = createIndex(row, 0);
    emit dataChanged(index, index);
}

void ItemModel::removeItem(Item astroFile, int row)
{
    removeRow(row);
}
