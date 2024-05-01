#ifndef ITEM_H
#define ITEM_H

#include <QString>
class Item
{
public:
    Item();
    int stock;
    double price;
    QString category;
    QString brand;
    QString image;
    Item(int s,double p, QString c, QString b);
};

#endif // ITEM_H
