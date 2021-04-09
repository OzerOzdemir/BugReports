#ifndef CATALOG_H
#define CATALOG_H

#include "item.h"

#include <QObject>

class Catalog : public QObject
{
    Q_OBJECT
public:
    explicit Catalog(QObject *parent = nullptr);
    Item getItem(int row);
    volatile bool canceled = false;

public slots:
    void generateItems(int numberOfItems, int sleepMs);

signals:
    void ItemeAdded(Item item, int row);

private:
    QList<Item> itemList;
    QMutex listMutex;
};

#endif // CATALOG_H
