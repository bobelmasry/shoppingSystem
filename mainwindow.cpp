#include "mainwindow.h"
#include "qstandardpaths.h"
#include "ui_mainwindow.h"
#include "registrationwindow.h"
#include "userwindow.h"
#include "add_item_window.h"
#include <QPixmap>
#include <QFile>
#include <items.h>
#include <shelf.h>

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
    ui->cart->hide();
    readProductsFromFile();
    setButtonNames(this);
    Item::printitems();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_signup_clicked()
{
    Registrationwindow* registrationwindow=new Registrationwindow;
    registrationwindow->show();
}


void MainWindow::on_loginButton_clicked()
{
    qDebug() << QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString username = ui->userNameBox->text();
    QString password = ui->passwordBox->text();

    if (username.isEmpty() || password.isEmpty()) {
        ui->incorrect_login->show();
        return;
    }

    // Get the desktop directory path
    QString desktopDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    // Create the full file path
    QString filePath = desktopDir + "/users.txt";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open users.txt for reading:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    QString line;
    bool loggedIn = false;

    while (!(line = in.readLine()).isNull()) {
        QStringList fields = line.split(',');

        QString csvUsername = fields[0].trimmed();
        QString csvPassword = fields[1].trimmed();
        QString User = fields[2].trimmed(); // Assuming user type is stored in the third field

        if (csvUsername == username && csvPassword == password) {
            loggedIn = true;
            userDetails = fields;
            if (User == "TRUE") {
                ui->manageProductsBtn->show();
                ui->manageUsersBtn->show();
                ui->delete_prod_button->show();
            } else {
                ui->cart->show();
            }
            break;
        }
    }

    file.close();

    if (loggedIn) {
        ui->incorrect_login->hide();
        qDebug() << "Logged in successfully!";
        ui->userNameBox->deleteLater();
        ui->passwordBox->deleteLater();
        ui->loginButton->deleteLater();
        ui->label_2->deleteLater();
        ui->signup->deleteLater();
        ui->helloLabel->setText("Hello " + username);
    } else {
        ui->incorrect_login->show();
        qDebug() << "Incorrect username or password";
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
    Item::items.clear();
    readProductsFromFile();

    if(sort_type=="price")
        Item::sort_by_price();
    if(sort_type=="brand")
        Item::sort_by_brand();
    if(sort_type=="name")
        Item::sort_by_name();

     setButtonNames(this);

}


//////sorting by categories

void MainWindow::on_fruit_category_clicked()
{
    Item::items.clear();
    readProductsFromFile();
    Item::fruit();
}


void MainWindow::on_meat_category_clicked()
{

    Item::items.clear();
    readProductsFromFile();
    Item::meat();

}


void MainWindow::on_dairy_category_clicked()
{
    Item::items.clear();
    readProductsFromFile();
    Item::dairy();
}


void MainWindow::on_grains_category_clicked()
{
    Item::items.clear();
    readProductsFromFile();
    Item::grain();
}


void MainWindow::on_desert_category_clicked()
{
    Item::items.clear();
    readProductsFromFile();
    Item::desert();
}


void MainWindow::on_frozen_category_clicked()
{
    Item::items.clear();
    readProductsFromFile();
    Item::frozen();
}


void MainWindow::on_drinks_category_clicked()
{
    Item::items.clear();
    readProductsFromFile();
    Item::drinks();
}


void MainWindow::on_all_categories_clicked()
{
    Item::items.clear();
    readProductsFromFile();
    readProductsFromFile();
}

int getText(QString productName) {
    // Open the file
    QString desktopDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    // Create the full file path
    QString filePath = desktopDir + "/products.txt";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open products.txt for reading:" << file.errorString();
        return 0; // Return 0 if file cannot be opened
    }

    // Read the file line by line
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        if (fields.size() == 6) { // Ensure line has correct number of fields
            QString name = fields[0].trimmed();
            if (name == productName) {
                file.close();
                return fields[5].trimmed().toInt(); // Return the ID of the matching product
            }
        }
    }

    file.close();
    return 0; // Return 0 if product not found
}

void appendToUserCart(QString username, int productID) {
    // Open the file
    QString desktopDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    // Create the full file path
    QString filePath = desktopDir + "/users.txt";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open users.txt for reading and writing:" << file.errorString();
        return; // Return if file cannot be opened
    }

    // Read the file line by line and find the user
    QTextStream in(&file);
    QStringList lines;
    bool userFound = false;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        if (fields.size() == 4) { // Ensure line has correct number of fields
            QString csvUsername = fields[0].trimmed();
            if (csvUsername == username) {
                userFound = true;
                // Append the product ID to the shopping cart
                fields[3] = fields[3].trimmed();
                if (!fields[3].isEmpty()) {
                    fields[3] += "-";
                }
                // Add the product ID without extra double quotes
                fields[3] += QString::number(productID);
            }
            lines.append(fields.join(','));
        }
    }

    // If user not found, append a new line for the user
    if (!userFound) {
        lines.append(username + ",,," + QString::number(productID));
    }

    file.resize(0); // Clear the file content
    // Write the updated lines back to the file
    for (const QString& line : qAsConst(lines)) {
        in << line << '\n';
    }

    file.close();
}

void MainWindow::on_p00_clicked()
{
    QString text = ui->p00->text();
    if (text != "" && userDetails[0] != "" && userDetails[2] == "FALSE") // empty box
        appendToUserCart(userDetails[0], getText(text));
}

