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
    void on_login_clicked();

    void on_borrow_clicked();

    void on_return2_clicked();

    void on_query_clicked();

    void on_borrow_2_clicked();

    void on_borrow_3_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
