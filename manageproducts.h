#ifndef MANAGEPRODUCTS_H
#define MANAGEPRODUCTS_H

#include "items.h"
#include <QDialog>
using namespace std;

namespace Ui {
class manageProducts;
}

class manageProducts : public QDialog
{
    Q_OBJECT

public:
    manageProducts(QWidget *parent = nullptr);
    ~manageProducts();
    void setEditLinesText(manageProducts* itemWindow);


private slots:
    void on_pushButton_clicked();

private:
    Ui::manageProducts *ui;
    static map<pair<int, int>, vector<Item>> del;
};

#endif // MANAGEPRODUCTS_H
