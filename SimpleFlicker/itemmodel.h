#ifndef ITEMMODEL_H
#define ITEMMODEL_H

#include "catalog.h"
#include "item.h"

#include <QAbstractItemModel>
#include <QObject>

class ItemModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit ItemModel(QObject *parent = nullptr);

signals:

public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);
    bool hasChildren(const QModelIndex &parent) const;

    void setCatalog(Catalog* catalog);
    void addItem(Item astroFile, int row);
    void updateItem(Item astroFile, int row);
    void removeItem(Item astroFile, int row);


private:
    int rc;
    int cc;
    Catalog* catalog;
    QSize cellSize = QSize(20, 20);
};

#endif // ITEMMODEL_H
