#include "userwindow.h"
#include "ui_userwindow.h"
#include "qstandardpaths.h"
#include <QFile>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

userWindow::userWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::userWindow)
{
    ui->setupUi(this);

    QString desktopDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    QString filePath = desktopDir + "/users.txt";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open users.txt for reading:" << file.errorString();
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        QString user = fields[0].trimmed();
        QString isAdmin = fields[2].trimmed();
        qDebug() << user << "\n";
        if (user != "username" && isAdmin != "TRUE"){
            QWidget *itemWidget = new QWidget();
            QHBoxLayout *layout = new QHBoxLayout(itemWidget);

            QLabel *label = new QLabel(user);
            layout->addWidget(label);

            QPushButton *removeButton = new QPushButton("Remove");
            layout->addWidget(removeButton);

            connect(removeButton, &QPushButton::clicked, this, [=]() {
                qDebug() << "Remove button clicked for user:" << user;
                removeUser(user);
            });

            QListWidgetItem *listItem = new QListWidgetItem();
            listItem->setSizeHint(itemWidget->sizeHint());

            ui->listWidget->addItem(listItem);
            ui->listWidget->setItemWidget(listItem, itemWidget);

        }
        }
    file.close();
    }

void userWindow::removeUser(const QString& username) {
    QString desktopDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    QString filePath = desktopDir + "/users.txt";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open users.txt for reading and writing:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        QString user = fields[0].trimmed();
        if (user != username) {
            // exclude the line corresponding to the user to be removed
            lines.append(line);
        }
    }

    file.resize(0);  // clear the contents of the file
    QTextStream out(&file);
    for (const QString& line : lines) {
        out << line << "\n";  // rewrite the file without the removed user
    }

    file.close();
}



userWindow::~userWindow()
{
    delete ui;
}
