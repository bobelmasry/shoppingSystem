#ifndef EDITPROD_H
#define EDITPROD_H

#include "items.h"
#include <QDialog>
#include <map>
#include <vector>
using namespace std;

namespace Ui {
class EditProd;
}

class EditProd : public QDialog
{
    Q_OBJECT

public:
    explicit EditProd(QWidget *parent = nullptr);
    ~EditProd();

private:
    Ui::EditProd *ui;
     static map<pair<int, int>, vector<Item>> del;
};

#endif // EDITPROD_H
