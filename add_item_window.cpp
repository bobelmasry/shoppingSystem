#include "add_item_window.h"
#include "ui_add_item_window.h"
#include "item.h"

Add_Item_Window::Add_Item_Window(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Add_Item_Window)
{
    ui->setupUi(this);
    ui->all_fields_label->hide();
    ui->product_label->hide();
}


void Add_Item_Window::on_pushButton_clicked()
{
    prod_name=ui->prod_name->text();
    price=ui->prod_price->value();
    brand=ui->brand_name->text();
    stock=ui->stock_count->value();
    category=ui->category->currentText();

    if(prod_name.isEmpty()||price==0||brand.isEmpty()||stock==0||category=="---")
        ui->all_fields_label->show();
    else
        {
        Item item(prod_name,stock,price,category,brand);
        hide();
        }

}




Add_Item_Window::~Add_Item_Window()
{
    delete ui;
}


