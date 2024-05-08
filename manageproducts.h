#ifndef MANAGEPRODUCTS_H
#define MANAGEPRODUCTS_H

#include <QDialog>

namespace Ui {
class manageProducts;
}

class manageProducts : public QDialog
{
    Q_OBJECT

public:
    explicit manageProducts(QWidget *parent = nullptr);
    void removeProduct(const QString& productName);
    ~manageProducts();

private:
    Ui::manageProducts *ui;
};

#endif // MANAGEPRODUCTS_H
