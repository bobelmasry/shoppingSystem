#include "shelf.h"
#include "items.h"

map<pair<int, int>, vector<Item>> Shelf::shelf;

Shelf::Shelf()
{

    int items_placed = 0;

    for (const auto& item : Item::items) {
        int row = items_placed / 5;
        int col = items_placed % 5;
        shelf[{row, col}].push_back(item);


        ++items_placed;
    }



}
