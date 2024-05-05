#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QDialog>

namespace Ui {
class userWindow;
}

class userWindow : public QDialog
{
    Q_OBJECT

public:
    explicit userWindow(QWidget *parent = nullptr);
    ~userWindow();

private:
    Ui::userWindow *ui;
};

#endif // USERWINDOW_H
