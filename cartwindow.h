#ifndef CARTWINDOW_H
#define CARTWINDOW_H

#include <QDialog>

namespace Ui {
class cartWindow;
}

class cartWindow : public QDialog
{

public:
    explicit cartWindow(const QString& username, QWidget *parent = nullptr);
    static double payment;
    ~cartWindow();
    static void clear_cart(QString &username);

private slots:
    void on_pushButton_clicked();

private:
    Ui::cartWindow *ui;
};

#endif // CARTWINDOW_H
