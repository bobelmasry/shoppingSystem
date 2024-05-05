#ifndef SHELF_H
#define SHELF_H

#include <vector>
using namespace std;
#include "items.h"

class Item;

class Shelf
{
public:
    Shelf();
    vector<vector<Item>>shelf;


};

#endif // SHELF_H
