#include "registrationwindow.h"
#include "ui_registrationwindow.h"
#include "mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QStandardPaths>
#include <QDir>

Registrationwindow::Registrationwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Registrationwindow)
{
    ui->setupUi(this);
    ui->passwarning->hide();
    ui->fieldwarning->hide();
    ui->userwarning->hide();
}

Registrationwindow::~Registrationwindow()
{
    delete ui;
}


bool Registrationwindow::usernameExists(const QString &username)
{
    // Get the desktop directory path
    QString desktopDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    // Create the full file path
    QString filePath = desktopDir + "/users.txt";

    // Open the file for reading
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Error: Could not open file for reading -" << file.errorString();
        return false;
    }

    // Read from the file and check if the username exists
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList parts = line.split(',');
        QString m_username = parts.at(0).trimmed();
        // Case-insensitive comparison
        if (m_username.compare(username, Qt::CaseInsensitive) == 0)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}



void Registrationwindow::on_registerButton_clicked()
{
    QString username = ui->usernameedit->text().trimmed(); // Trimmed username
    QString pass1 = ui->passwordedit->text();
    QString pass2 = ui->retypeedit->text();

    // Check for empty username
    if (username.isEmpty()) {
        ui->fieldwarning->show();
        return;
    }

    // Check for duplicate username
    if (usernameExists(username)) {
        ui->userwarning->show();
        return;
    }

    // Check for matching passwords
    if (pass1 != pass2) {
        ui->passwarning->show();
        return;
    }

    // Get the desktop directory path
    QString desktopDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    // Create the full file path
    QString filePath = desktopDir + "/users.txt";

    // Open the file for appending
    QFile file(filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        qDebug() << "Error: Could not open file for writing -" << file.errorString();
        return;
    }

    // Write username and password to the file
    QTextStream out(&file);
    out << username << "," << pass1 << "\n";
    file.close();

    hide();
    MainWindow* main = new MainWindow;
    main->show();
}
