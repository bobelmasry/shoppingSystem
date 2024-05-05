#include "items.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
using namespace std;

vector<Item> Item::items;

Item::Item(QString n, int s, double p, QString c, QString b) : stock(s), price(p), category(c), brand(b), name(n)
{
    QFile file(":/assets/products.csv");

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << n << "," << s << "," << p << "," << c << "," << b << Qt::endl;

        if (out.status() != QTextStream::Ok)
        {
            qWarning() << "Error writing data to file:" << out.status();
        }
        else
        {
            qDebug() << "Data successfully written to file.";
        }
    }
    else
    {
        qWarning() << "Failed to open file for writing:" << file.errorString();
    }

    file.close();
}

QString Item::getName()  {
    return name;
}

double Item::getPrice()  {
    return price;
}

QString Item::getBrand()  {
    return brand;
}

int Item::getQuantity()  {
    return stock;
}

QString Item::getCategory()  {
    return category;
}

vector<Item> readProductsFromFile()
{
    vector<Item> products;

    QFile file(":/assets/products.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << file.errorString();
        return products;
    }

    QTextStream in(&file);
    in.readLine();

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        if (fields.size() == 5) {
            QString name = fields[0];
            double price = fields[1].toDouble();
            QString brand = fields[2];
            int quantity = fields[3].toInt();
            QString category = fields[4];
            Item product(name, price,quantity,brand, category);
            products.push_back(product);
        }
    }


    file.close();
    return products;
}



///////////////////////////the sorters

void Item::sort_by_price()
{

    sort(items.begin(), items.end(), []( Item& a, Item& b) {
        return a.getPrice() < b.getPrice(); //get price sorts by price
    });
}

void Item::sort_by_brand()
{

    sort(items.begin(), items.end(), [](Item& a, Item& b) {
        return a.getBrand() < b.getBrand(); //get brand sorts by brand
    });

}

void Item::sort_by_name()
{
    sort(items.begin(), items.end(), [](Item& a, Item& b) {
        return a.getName() < b.getName(); //get name sorts by name
    });
}


//////////////////the catagorizers


void Item::fruit()
{
    vector<Item> filteredItems;

    for (auto& item : items) {
        if (item.getCategory() == "Fruits and Vegetables") {
            filteredItems.push_back(item);
        }
    }

    items = filteredItems;
}


void Item::meat()
{
    vector<Item> filteredItems;

    for (auto& item : items) {
        if (item.getCategory() == "Meat and Poultry") {
            filteredItems.push_back(item);
        }
    }

    items = filteredItems;
}

void Item::grain()
{
    vector<Item> filteredItems;

    for (auto& item : items) {
        if (item.getCategory() == "Grains") {
            filteredItems.push_back(item);
        }
    }

    items = filteredItems;
}

void Item::drinks()
{
    vector<Item> filteredItems;

    for (auto& item : items) {
        if (item.getCategory() == "Drinks") {
            filteredItems.push_back(item);
        }
    }

    items = filteredItems;
}

void Item::dairy()
{
    vector<Item> filteredItems;

    for (auto& item : items) {
        if (item.getCategory() == "Dairy") {
            filteredItems.push_back(item);
        }
    }

    items = filteredItems;
}


void Item::desert()
{
    vector<Item> filteredItems;

    for (auto& item : items) {
        if (item.getCategory() == "Deserts") {
            filteredItems.push_back(item);
        }
    }

    items = filteredItems;
}


