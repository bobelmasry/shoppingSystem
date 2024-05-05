#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_signup_clicked();

    void on_loginButton_clicked();

    void on_manageProductsBtn_clicked();

    void on_manageUsersBtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
