#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "borrow.h"
#include "qbook.h"
#include "addbook.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_login_clicked()
{
    login *wlogin=new login();
    wlogin->show();

}

void MainWindow::on_borrow_clicked()
{
    borrow *p=new borrow();
    p->show();
}


void MainWindow::on_return2_clicked()//退出登录，返回密码登录界面
{
    this->close();
    login *wlogin=new login();
    wlogin->show();
}


void MainWindow::on_query_clicked()
{
    qbook *p=new qbook();
    p->show();
}


void MainWindow::on_borrow_2_clicked()
{
    addbook *p=new addbook();
    p->show();
}

