#include "registrationwindow.h"
#include "ui_registrationwindow.h"

Registrationwindow::Registrationwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Registrationwindow)
{
    ui->setupUi(this);
}

Registrationwindow::~Registrationwindow()
{
    delete ui;
}
