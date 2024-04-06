#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QApplication>
#include <QSqlDatabase>
namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::login *ui;
    QString username;
    int id;
};

#endif // LOGIN_H
