#include "manageproducts.h"
#include "mainwindow.h"
#include "ui_manageproducts.h"
#include "qstandardpaths.h"
#include <QFile>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>


map<pair<int, int>, vector<Item>>manageProducts:: del;

// Constructor: Load initial data into line edits
manageProducts::manageProducts(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::manageProducts)
{
    ui->setupUi(this);

    // Load initial data into line edits
    setEditLinesText(this);
}

// Function to set initial data into line edits
void manageProducts::setEditLinesText(manageProducts* itemWindow) {
    int index = 0; // Index for accessing items in the Item::items list
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 6; ++col) { // Changed to 6 fields per line edit
            QString editName = "e" + QString::number(row) + QString::number(col); // Edit line name format
            QLineEdit *editLine = itemWindow->findChild<QLineEdit*>(editName); // Find the edit line by name
            if (editLine) {
                if (index < Item::items.size())
                {
                    QString itemName = Item::items[index].getName();
                    QString itemBrand = Item::items[index].getBrand();
                    double itemPrice = Item::items[index].getPrice();
                    int itemStock = Item::items[index].getQuantity();
                    QString category = Item::items[index].getCategory();
                    int id = Item::items[index].getId();
                    // Set initial data into line edit
                    editLine->setText(itemName + "," + QString::number(itemPrice) + "," + itemBrand + "," + QString::number(itemStock) + "," + category + "," + QString::number(id));
                } else {
                    // If no more items in the list, set empty text
                    editLine->clear();
                }
                ++index; // Move to the next item index
            }
        }
    }
}

// Destructor
manageProducts::~manageProducts()
{
    delete ui;
}

// Button click event handler
void manageProducts::on_pushButton_clicked() {
    QString desktopDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString filename = desktopDir + "/products.txt";

    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        const int numRows = 8;
        const int numCols = 4;
        for (int row = 0; row < numRows; ++row) {
            QString data;
            bool emptyRow = true;
            for (int col = 0; col < numCols; ++col) {
                QString editName = "e" + QString::number(row) + QString::number(col);
                QLineEdit* editLine = this->findChild<QLineEdit*>(editName);
                if (editLine) {
                    QString text = editLine->text().trimmed();
                    if (!text.isEmpty()) {
                        data += text + ",";
                        emptyRow = false;
                    }
                }
            }
            if (!emptyRow) {
                data.chop(1); // Remove the trailing comma
                out << data << "\n"; // Write data to the file
            }
        }
        qDebug() << "File updated with new content: " << filename;

        file.close();
    } else {
        qDebug() << "Error: Unable to open file for writing: " << filename;
    }

    hide();
}
