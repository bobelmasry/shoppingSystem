#ifndef CARTWINDOW_H
#define CARTWINDOW_H

#include <QDialog>

namespace Ui {
class cartWindow;
}

class cartWindow : public QDialog
{
    Q_OBJECT

public:
    explicit cartWindow(QWidget *parent = nullptr);
    ~cartWindow();

private:
    Ui::cartWindow *ui;
};

#endif // CARTWINDOW_H
