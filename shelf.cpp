#include "shelf.h"
#include "items.h"
#include <QPushButton>
#include "mainwindow.h"

map<pair<int, int>, vector<Item>> Shelf::shelf;


Shelf::Shelf()
{
    int items_placed = 0;

    for (const auto& item : Item::items) {
        int row = items_placed / 7;
        int col = items_placed % 7;
        shelf[{row, col}] = {item};
        ++items_placed;
    }
}

void setButtonNames(MainWindow *mainWindow) {
    int index = 0; // Index for accessing items in the Item::items list
    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 7; ++col) {
            QString buttonName = "p" + QString::number(row) + QString::number(col); // Button name format
            QPushButton *button = mainWindow->findChild<QPushButton*>(buttonName); // Find the button by name
            if (button) {
                if (index < Item::items.size()) {
                    QString itemName = Item::items[index].getName();
                    QString itemBrand = Item::items[index].getBrand();
                    double itemPrice = Item::items[index].getPrice();
                    int itemStock = Item::items[index].getQuantity();

                    // Set button text to item name, brand, price, and stock
                    button->setText(itemName + "\n" + itemBrand + "\n$" + QString::number(itemPrice) + "\nStock: " + QString::number(itemStock));
                } else {
                    // If no more items in the list, set empty text
                    button->setText("");
                }
                ++index; // Move to the next item index
            }
        }
    }
}

