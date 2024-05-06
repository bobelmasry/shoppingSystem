#ifndef ITEM_H
#define ITEM_H

#include <QString>
using namespace std;
class Item
{
private:


public:


    //the struct of Item
    int stock;
    double price;
    QString category;
    QString brand;
    QString image;
    QString name;
    int id;
    void addItem(QString n, int s,double p, QString c, QString b, int id);
    Item(QString n, int s, double p, QString c, QString b, int id);
    Item();



    //the getters
    QString getName();
    double getPrice();
    QString getBrand();
    int getQuantity();
    QString getCategory();



    //the sorters
    static void sort_by_price();
    static void sort_by_brand();
    static void sort_by_name();


    //the catagorizers
    static void meat();
    static void dairy();
    static void grain();
    static void frozen();
    static void desert();
    static void drinks();
    static void fruit();



    //the items in an array
    static vector<Item>items;

    static void printitems();




};

vector<Item> readProductsFromFile();

#endif // ITEM_H
