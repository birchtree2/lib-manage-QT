#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "borrow.h"
#include "qbook.h"
#include "addbook.h"
#include "card.h"
#include "user.h"
#include<QMessageBox>
MainWindow::MainWindow(const QString& uid,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),user_id(uid)
{
    ui->setupUi(this);
    qDebug()<<user_id;
    ui->cur_user->setText("当前管理员："+user_id);
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
    borrow *p=new borrow(this->user_id);
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


void MainWindow::on_borrow_3_clicked()
{
    card *p=new card();
    p->show();
}


void MainWindow::on_adduser_clicked()
{
    if(this->user_id!="2001"){
        QMessageBox::information(this,"错误","仅管理员有增删用户权限!");
        return;
    }

    user* p=new user();
    p->show();
}

