#include "checkout.h"
#include "ui_checkout.h"
#include <QMessageBox>
#include "cartwindow.h"
#include "mainwindow.h"

Checkout::Checkout(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::checkout)
{
    ui->setupUi(this);
    qDebug()<<"shown checkout window";
    ui->expired->hide();
    ui->field_2->hide();
    ui->creditwarning->hide();
    ui->csv_warning->hide();
}

Checkout::~Checkout()
{
    delete ui;
}

void Checkout::on_pushButton_clicked()
{
    QString credit_card;
    QString date;
    QString csv;

    bool csv_ok=false;
    bool date_ok=false;
    bool credit_ok=false;
    bool everything_full;

    credit_card=ui->creditcard->text();
    date=ui->date->sectionText(QDateTimeEdit::YearSection);
    csv=ui->csv->text();

    if(credit_card.length()!=12)
    {
        ui->creditwarning->show();
    }
    else
    {
        ui->creditwarning->hide();
    credit_ok=true;
    }

    if(csv.toInt()<1000||csv.toInt()>99)
    {
        csv_ok=true;
        ui->csv_warning->hide();
    }
    else
    {
        csv_ok=false;
        ui->csv_warning->hide();
    }
    if(date.toInt()>=2024)
    {
        date_ok=true;
        ui->expired->hide();
    }
    else
        ui->expired->show();
    if(!ui->creditcard->text().isEmpty()&&!ui->csv->text().isEmpty())
        everything_full=true;
    else
        ui->field_2->show();


    if(csv_ok&&date_ok&&everything_full&&credit_ok)
    {
        sucess(cartWindow::payment);
        ui->expired->hide();
        ui->field_2->hide();
    }

}

void Checkout::sucess(double paymentAmount)
{
    QString message = "Payment of $" + QString::number(paymentAmount) + " was successful!";

    // Show a QMessageBox with an information icon and the constructed message
    QMessageBox::information(nullptr, "Payment Successful", message);
    cartWindow::clear_cart(MainWindow::username);
    ui->field_2->hide();
    hide();
}

