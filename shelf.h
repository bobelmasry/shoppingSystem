#ifndef SHELF_H
#define SHELF_H

#include <map>
#include <vector>
using namespace std;
#include "items.h"

class Item;

class Shelf
{
public:
    Shelf();
    static map<pair<int, int>, vector<Item>> shelf;


};

#endif // SHELF_H
