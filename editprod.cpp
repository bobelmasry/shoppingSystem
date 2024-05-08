#include "editprod.h"
#include "ui_editprod.h"
#include <items.h>

map<pair<int, int>, vector<Item>> EditProd::del;

EditProd::EditProd(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditProd)
{
    ui->setupUi(this);



    int items_placed = 0;

    for (const auto& item : Item::items) {
        int row = items_placed / 7;
        int col = items_placed % 7;
        del[{row, col}] = {item};
        ++items_placed;
    }








}






EditProd::~EditProd()
{
    delete ui;
}
