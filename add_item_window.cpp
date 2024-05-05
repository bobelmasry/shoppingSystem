#include "add_item_window.h"
#include "ui_add_item_window.h"
#include <QFile>

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
        QFile file("D://python_projects//other shit//CS//shoppingSysyte//assets//products.csv");
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << prod_name << "," << price << "," << brand << "," << stock << "," << category << "\n";

            file.close();
            hide();
        } else {
            qDebug() << "Failed to open products.csv for appending:" << file.errorString();
        }
    }
        }


Add_Item_Window::~Add_Item_Window()
{
    delete ui;
}


