#include "registrationwindow.h"
#include "ui_registrationwindow.h"
#include <QDebug>
#include <QFile>

Registrationwindow::Registrationwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Registrationwindow)
{
    ui->setupUi(this);
    ui->fieldwarning->hide();
}

Registrationwindow::~Registrationwindow()
{
    delete ui;
}

void Registrationwindow::on_registerButton_clicked()
{
    QString username = ui->usernameedit->text();
    QString pass1 = ui->passwordedit->text();
    QString pass2 = ui->retypeedit->text();
    qDebug() << pass1 << "\n";
    qDebug() << pass2 << "\n";
    if (pass1 != pass2){
        ui->matchingwarning->setText("* Not Matching");
    }

    // Open the users.csv file for reading
    QFile file(":/assets/users.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open users.csv for reading:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    bool usernameExists = false;
    while (!in.atEnd()) {
        QString line = in.readLine();
        qDebug() << line << "\n";
        QStringList fields = line.split(',');
        if (fields.size() > 0 && fields[0] == username) {
            // Username already exists
            usernameExists = true;
            break;
        }
    }

    file.close();

    if (usernameExists) {
        // Username already exists, display a warning
        ui->alreadywarning->setText("* Username already taken");
        return;
    }
    else if (pass1 == pass2) {
        ui->alreadywarning->setText("");
        QFile file("D://python_projects//other shit//CS//shoppingSysyte//assets//users.csv");
        file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);

        if (!file.isOpen()) {
            qDebug() << "Failed to open users.csv for appending:" << file.errorString();
            return;
        }

        QTextStream out(&file);
        out << username << "," << pass1 << ",FALSE" << ",\"\"\"\"\"\"" << "\n";
        file.close();
        qDebug() << "User added successfully.";

        // Clear input fields after successful registration
        ui->usernameedit->clear();
        ui->passwordedit->clear();
        ui->retypeedit->clear();
    }


}

