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

private:
    Ui::Registrationwindow *ui;
};

#endif // REGISTRATIONWINDOW_H
