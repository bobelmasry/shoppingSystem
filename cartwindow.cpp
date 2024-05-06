#include "cartwindow.h"
#include "ui_cartwindow.h"

cartWindow::cartWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cartWindow)
{
    ui->setupUi(this);
}

cartWindow::~cartWindow()
{
    delete ui;
}
