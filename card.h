#ifndef CARD_H
#define CARD_H

#include <QMainWindow>

namespace Ui {
class card;
}

class card : public QMainWindow
{
    Q_OBJECT

public:
    explicit card(QWidget *parent = nullptr);
    ~card();

private slots:
    void on_qcard_clicked();

    void on_add_clicked();

    void on_upd_clicked();

    void on_del_clicked();

private:
    Ui::card *ui;
};

#endif // CARD_H
