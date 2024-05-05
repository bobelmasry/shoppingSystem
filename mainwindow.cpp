#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registrationwindow.h"
#include "userwindow.h"
#include "add_item_window.h"
#include <QPixmap>
#include <QFile>
#include <items.h>

QStringList userDetails;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix(":/logo image.png");
    ui->logo->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio));
    ui->manageProductsBtn->hide();
    ui->manageUsersBtn->hide();
    ui->incorrect_login->hide();
    ui->delete_prod_button->hide();
    Item::items=readProductsFromFile();
    Item::sort_by_price();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_signup_clicked()
{
    hide();
    Registrationwindow* registrationwindow=new Registrationwindow;
    registrationwindow->show();
}


void MainWindow::on_loginButton_clicked()
{
    QString username = ui->userNameBox->text();
    QString password = ui->passwordBox->text();

    if (username.isEmpty() || password.isEmpty()) {
        ui->loginErrorLabel->setText("* Empty username or Password");
        ui->incorrect_login->show();

        return;
    }

    QFile file(":/assets/users.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open users.csv for reading:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    QString line;
    bool loggedIn = false;

    while (!(line = in.readLine()).isNull()) {
        QStringList fields = line.split(',');
        userDetails = fields;

        QString csvUsername = fields[0].trimmed();
        QString csvPassword = fields[1].trimmed();

        if (csvUsername == username && csvPassword == password) {
            loggedIn = true;
            break;
        }
    }

    file.close();

    if (loggedIn) {
        ui->loginErrorLabel->setText("");
        ui->incorrect_login->hide();
        qDebug() << "Logged in successfully!";
        ui->userNameBox->deleteLater();
        ui->passwordBox->deleteLater();
        ui->loginButton->deleteLater();
        ui->label_2->deleteLater();
        ui->signup->deleteLater();
        ui->helloLabel->setText("Hello " + userDetails[0].trimmed());

    } else {
        ui->loginErrorLabel->setText("* Incorrect username or password");
        qDebug() << "Incorrect username or password";
    }

    if (loggedIn && userDetails[2].trimmed() == "TRUE"){
        ui->manageProductsBtn->show();
        ui->manageUsersBtn->show();
        ui->delete_prod_button->show();
    }

}



void MainWindow::on_manageProductsBtn_clicked()
{
    Add_Item_Window* itemWindow=new Add_Item_Window;
    itemWindow->show();

}


void MainWindow::on_manageUsersBtn_clicked()
{
    userWindow* user_window=new userWindow;
    user_window->show();

}

void MainWindow::on_sort_clicked()
{

    sort_type=ui->sort_type->currentText();

    if(sort_type=="price")
        Item::sort_by_price();
    if(sort_type=="brand")
        Item::sort_by_brand();
    if(sort_type=="name")
        Item::sort_by_name();

}

