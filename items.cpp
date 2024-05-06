#include "items.h"
#include "qstandardpaths.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
using namespace std;

vector<Item> Item::items;

Item::Item()
{

}

Item::Item(QString n, int s, double p, QString c, QString b):stock(s),price(p),category(c),brand(b),name(n)
{
    items.push_back(*this);
    qDebug()<<"pushed in an item in the list, called paramterized const"<<Qt::endl;
}

void Item::addItem(QString n, int s, double p, QString c, QString b)
{
    stock=s;
    price=p;
    category=c;
    brand=b;
    name=n;

    // Get the desktop directory path
    QString desktopDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    // Create the full file path
    QString filePath = desktopDir + "/products.txt";

    QFile file(filePath);

    file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);

        QTextStream out(&file);
        out << n << "," << s << "," << p << "," << c << "," << b << Qt::endl;

        qDebug()<<"added an Item"<<Qt::endl;

    file.close();

}


vector<Item> readProductsFromFile()
{
    vector<Item> products;

    // Get the desktop directory path
    QString desktopDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    // Create the full file path
    QString filePath = desktopDir + "/products.txt";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file:" << file.errorString();
        return products;
    }

    QTextStream in(&file);
    in.readLine(); // Skip header line

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        if (fields.size() == 5) {
            QString name = fields[0];
            double price = fields[1].toDouble();
            int quantity = fields[3].toInt(); // Changed index from 3 to 1
            QString category = fields[4]; // Changed index from 4 to 3
            QString brand = fields[2].trimmed(); // Changed index from 2 to 4

            // Create an Item object using the constructor
            Item item(name, price, quantity, category, brand);
            products.push_back(item);
        } else {
            qDebug() << "Invalid line format:" << line;
        }
    }

    file.close();
    return products;
}




//////////the getters

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
    Item::items.clear();
    readProductsFromFile();

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
    Item::items.clear();
    readProductsFromFile();

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
    Item::items.clear();
    readProductsFromFile();

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
    Item::items.clear();
    readProductsFromFile();

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
    Item::items.clear();
    readProductsFromFile();

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
    Item::items.clear();
    readProductsFromFile();

    for (auto& item : items) {
        if (item.getCategory() == "Deserts") {
            filteredItems.push_back(item);
        }
    }

    items = filteredItems;
}

void Item::frozen()
{
    vector<Item> filteredItems;

    Item::items.clear();
    readProductsFromFile();

    for (auto& item : items) {
        if (item.getCategory() == "Frozen Food") {
            filteredItems.push_back(item);
        }
    }

    items = filteredItems;
    qDebug()<<"items=filteredItem"<<Qt::endl;
}

void Item::printitems() {
    for (auto& item : items)
    {
        qDebug()<< item.getName()<<item.getPrice()<<item.getBrand()<<item.getCategory()<<item.stock<< Qt::endl;
    }
}


