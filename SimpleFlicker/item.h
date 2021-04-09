#ifndef ITEM_H
#define ITEM_H

#include <QImage>
#include <QString>


struct Item
{
    int Id;
    QString Name;
    QImage thumbnail;
};

#endif // ITEM_H
