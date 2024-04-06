#include "qbook.h"
#include "ui_qbook.h"

qbook::qbook(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::qbook)
{
    ui->setupUi(this);
}

qbook::~qbook()
{
    delete ui;
}
