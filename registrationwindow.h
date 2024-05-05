#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QDialog>

namespace Ui {
class Registrationwindow;
}

class Registrationwindow : public QDialog
{
    Q_OBJECT

public:
    explicit Registrationwindow(QWidget *parent = nullptr);
    ~Registrationwindow();


private slots:
    void on_registerButton_clicked();

private:
    Ui::Registrationwindow *ui;
    bool usernameExists(const QString &username);


};

#endif // REGISTRATIONWINDOW_H
