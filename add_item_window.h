#ifndef ADD_ITEM_WINDOW_H
#define ADD_ITEM_WINDOW_H

#include <QDialog>

namespace Ui {
class Add_Item_Window;
}

class Add_Item_Window : public QDialog
{
    Q_OBJECT

public:
    explicit Add_Item_Window(QWidget *parent = nullptr);
    ~Add_Item_Window();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Add_Item_Window *ui;
    QString prod_name;
    double price;
    QString brand;
    QString category;
    int stock;
};

#endif // ADD_ITEM_WINDOW_H
