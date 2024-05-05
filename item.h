#ifndef ITEM_H
#define ITEM_H

#include <QString>
class Item
{
public:
    Item();
    int stock;
    int x;
    int y;
    double price;
    QString category;
    QString brand;
    QString image;
    QString name;
    Item(QString n, int s,double p, QString c, QString b);
};

#endif // ITEM_H
