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
    QString search;
    void handleButtonClick();
    static QString username;
    ~MainWindow();

private slots:
    void on_signup_clicked();

    void on_loginButton_clicked();

    void on_manageProductsBtn_clicked();

    void on_manageUsersBtn_clicked();

    void on_sort_clicked();

    void on_fruit_category_clicked();

    void on_meat_category_clicked();


    void on_dairy_category_clicked();


    void on_grains_category_clicked();


    void on_desert_category_clicked();


    void on_frozen_category_clicked();


    void on_drinks_category_clicked();


    void on_all_categories_clicked();

    void on_search_clicked();

    void on_cart_clicked();

    void on_delete_prod_button_clicked();

    void on_checkout_clicked();

private:
    Ui::MainWindow *ui;
    QString sort_type;
    bool loggedIn;
    bool cart_empty;
    int click_counter=0;
};
#endif // MAINWINDOW_H
