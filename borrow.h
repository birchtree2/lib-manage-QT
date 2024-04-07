#ifndef BORROW_H
#define BORROW_H

#include <QMainWindow>

namespace Ui {
class borrow;
}

class borrow : public QMainWindow
{
    Q_OBJECT

public:
    explicit borrow(const QString& uid,QWidget *parent = nullptr);
    ~borrow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    bool is_valid_cno(const QString& cno);
    bool is_valid_bno(const QString& bno);
    Ui::borrow *ui;
    QString user_id;
};

#endif // BORROW_H
