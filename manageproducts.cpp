#include "manageproducts.h"
#include "ui_manageproducts.h"
#include "qstandardpaths.h"
#include <QFile>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

manageProducts::manageProducts(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::manageProducts)
{
    ui->setupUi(this);

    QString desktopDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    QString filePath = desktopDir + "/products.txt";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open products.txt for reading:" << file.errorString();
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        QString productName = fields[0].trimmed();
        qDebug() << productName << "\n";
        if (productName != "Product Name"){
            QWidget *itemWidget = new QWidget();
            QHBoxLayout *layout = new QHBoxLayout(itemWidget);

            QLabel *label = new QLabel(productName);
            layout->addWidget(label);

            QPushButton *removeButton = new QPushButton("Remove");
            layout->addWidget(removeButton);

            connect(removeButton, &QPushButton::clicked, this, [=]() {
                qDebug() << "Remove button clicked for product:" << productName;
                removeProduct(productName);
            });

            QListWidgetItem *listItem = new QListWidgetItem();
            listItem->setSizeHint(itemWidget->sizeHint());

            ui->listWidget->addItem(listItem);
            ui->listWidget->setItemWidget(listItem, itemWidget);

        }
    }
    file.close();
}

void manageProducts::removeProduct(const QString& productName) {
    QString desktopDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    QString filePath = desktopDir + "/products.txt";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open products.txt for reading and writing:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        QString productNameInFile = fields[1].trimmed();
        if (productNameInFile != productName) {
            // exclude the line corresponding to the product to be removed
            lines.append(line);
        }
    }

    file.resize(0);  // clear the contents of the file
    QTextStream out(&file);
    for (const QString& line : lines) {
        out << line << "\n";  // rewrite the file without the removed product
    }

    file.close();
}

manageProducts::~manageProducts()
{
    delete ui;
}
