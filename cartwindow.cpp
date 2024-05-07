#include "cartwindow.h"
#include "ui_cartwindow.h"
#include "qstandardpaths.h"
#include <QFile>
#include <QDebug>

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
                    QString productName = productFields[0].trimmed();
                    QListWidgetItem *listItem = new QListWidgetItem(productName);
                    ui->listWidget->addItem(listItem);
                }
            }

            productFile.close();
            break;
        }
    }

    file.close();
}

cartWindow::~cartWindow()
{
    delete ui;
}
