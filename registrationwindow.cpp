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
    QString userType; // To store the selected radio button's string

    // Check for empty username
    if (username.isEmpty()) {
        ui->fieldwarning->show();
        return;
    }

    // Check for duplicate username
    if (usernameExists(username))
    {
        ui->userwarning->show();
        return;
    }

    if(!usernameExists(username))
        ui->userwarning->hide();

    // Check for matching passwords
    if (pass1 != pass2) {
        ui->passwarning->show();
        return;
    }

    if(pass1==pass2)
        ui->passwarning->hide();

    // Check if admin or regular user is selected
    if(ui->admin_button->isChecked()) {
        userType = "TRUE";
    } else if (ui->user_button->isChecked() && ui->passwarning->isHidden() && ui->userwarning->isHidden()) {
        userType = "FALSE";
    } else {
        ui->fieldwarning->show();
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

    // Write username, password, and user type to the file
    QTextStream out(&file);
    out << username << "," << pass1 << "," << userType << "\n";
    file.close();

    hide();
}
