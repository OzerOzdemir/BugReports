#include "catalog.h"
#include "item.h"

#include <QPainter>
#include <QThread>
#include <QDebug>

Catalog::Catalog(QObject *parent) : QObject(parent)
{

}

QImage makeImage(int num)
{
    int size =  20;

    QImage image(QSize(size,size),QImage::Format_RGB32);
    QPainter painter(&image);
    painter.setBrush(QBrush(Qt::green));
    painter.fillRect(QRectF(0,0,size,size),Qt::green);
    painter.fillRect(QRectF(size/4,size/4,size/2,size/2),Qt::white);
    painter.setPen(QPen(Qt::black));
    painter.drawText(QRect(size/4,size/4,size/2,size/2), "F" + QString::number(num));
    return image;
}

Item Catalog::getItem(int row)
{
    return itemList.at(row);
}

void Catalog::generateItems(int numberOfItems, int sleepMs)
{
    qDebug() << "Generating one";

    for (int i = 0; i < numberOfItems; i++)
    {
        if (canceled)
            return;

        QThread::msleep(sleepMs);
        Item item;
        item.Id = i;
        item.Name = QString("Item_%1").arg(i);
        item.thumbnail = makeImage(i);
        itemList.append(item);
        emit ItemeAdded(item, i);
    }
}
