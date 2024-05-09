#include "cartwindow.h"
#include "checkout.h"
#include "ui_cartwindow.h"
#include "qstandardpaths.h"
#include <QFile>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

double cartWindow::payment;

cartWindow::cartWindow(const QString& username, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cartWindow)
{
    ui->setupUi(this);

    QString desktopDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    // Create the full file path
    QString filePath = desktopDir + "/users.txt";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open users.txt for reading:" << file.errorString();
        return;
    }
    qDebug() << "username:" << username;

    QTextStream in(&file);
    int totalField1 = 0; // Variable to accumulate the values from fields[1]
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        QString user = fields[0].trimmed();
        QString shoppingCart = fields[3].trimmed();
        qDebug() << user << "\n";
        if (user == username) {
            QStringList productIds = shoppingCart.split('-', Qt::SkipEmptyParts);

            QString desktopDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

            // Create the full file path
            QString filePath = desktopDir + "/products.txt";

            QFile productFile(filePath);
            if (!productFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug() << "Failed to open products.txt for reading:" << productFile.errorString();
                return;
            }

            QTextStream productIn(&productFile);
            while (!productIn.atEnd()) {
                QString productLine = productIn.readLine();
                QStringList productFields = productLine.split(',');
                if (productFields.size() < 6) {
                    qDebug() << "Invalid line format in products.txt:" << productLine;
                    continue;
                }

                QString productId = productFields[5].trimmed();
                if (productIds.contains(productId)) {
                    QString field1Value = productFields[1].trimmed();
                    totalField1 += field1Value.toInt(); // Accumulate the value from fields[1]
                    QString productName = productFields[0].trimmed();
                    QWidget *itemWidget = new QWidget();
                    QHBoxLayout *layout = new QHBoxLayout(itemWidget);

                    QLabel *label = new QLabel(productName);
                    layout->addWidget(label);

                    QPushButton *removeButton = new QPushButton("Remove");
                    layout->addWidget(removeButton);

                    connect(removeButton, &QPushButton::clicked, this, [=]() {
                        qDebug() << "Remove button clicked for product:" << productName;
                        removeProduct(productId, username);
                    });

                    QListWidgetItem *listItem = new QListWidgetItem();
                    listItem->setSizeHint(itemWidget->sizeHint());

                    ui->listWidget->addItem(listItem);
                    ui->listWidget->setItemWidget(listItem, itemWidget);


                }
                            }

            productFile.close();
            break;
        }
    }

    payment=totalField1; // Output the total value
    qDebug()<<payment;
    file.close();
}

    void cartWindow::removeProduct(QString productId, const QString& username) {
        QString desktopDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        QString filePath = desktopDir + "/users.txt";

        QFile file(filePath);
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            qDebug() << "Failed to open users.txt for writing:" << file.errorString();
            return;
        }

        QString updatedContent;
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            QStringList fields = line.split(',');
            if (fields.size() >= 1 && fields[0].trimmed() == username) {
                QString shoppingCart = fields.size() >= 4 ? fields[3].trimmed() : "";
                QStringList cartItems = shoppingCart.split('-', Qt::SkipEmptyParts);
                cartItems.removeAll(productId);
                updatedContent += fields[0].trimmed() + "," + fields[1].trimmed() + "," + fields[2].trimmed() + "," + cartItems.join('-') + "\n";
            } else {
                updatedContent += line + "\n";
            }
        }

        file.seek(0);
        file.write(updatedContent.toUtf8());

        file.resize(file.pos());

        file.close();
    }



cartWindow::~cartWindow()
{
    delete ui;
}

void cartWindow::on_pushButton_clicked()
{
    Checkout*checkout=new Checkout;
    hide();
    checkout->show();
}


void cartWindow::clear_cart(QString &username)
{
    QString desktopDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString filePath = desktopDir + "/users.txt";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open users.txt for writing:" << file.errorString();
        return;
    }

    QString updatedContent; // Variable to hold the updated content
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList fields = line.split(',');
        if (fields.size() >= 1 && fields[0].trimmed() == username) {
            // Found the user, remove the shopping cart data
            updatedContent += fields[0].trimmed() + "," + fields[1].trimmed() + "," + fields[2].trimmed() +","+ "\n";
        } else {
            // Keep the line unchanged for other users
            updatedContent += line + "\n";
        }
    }

    // Write the updated content back to the file
    file.seek(0); // Move to the beginning of the file
    file.write(updatedContent.toUtf8());

    // Truncate the file to the current position
    file.resize(file.pos());

    file.close();

    return;
}
