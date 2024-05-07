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
    ~cartWindow();

private:
    Ui::cartWindow *ui;
};

#endif // CARTWINDOW_H
