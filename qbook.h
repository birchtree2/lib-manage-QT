#ifndef QBOOK_H
#define QBOOK_H

#include <QMainWindow>

namespace Ui {
class qbook;
}

class qbook : public QMainWindow
{
    Q_OBJECT

public:
    explicit qbook(QWidget *parent = nullptr);
    ~qbook();

private slots:
    void on_pushButton_clicked();

private:
    Ui::qbook *ui;
};

#endif // QBOOK_H
