#include "addbook.h"
#include "ui_addbook.h"

addbook::addbook(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::addbook)
{
    ui->setupUi(this);
}

addbook::~addbook()
{
    delete ui;
}
