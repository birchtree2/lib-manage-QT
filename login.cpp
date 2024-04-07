#include "login.h"
#include "ui_login.h"
#include <QMEssageBox>
#include <qDebug>
#include <QSqlQuery>
#include <mainwindow.h>
#include <QLineEdit>
#include <QCryptographicHash>
login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    
    QString id=ui->lineEdit->text();
    QString password=ui->lineEdit_2->text();
    QSqlQuery query;//#include <QSqlQuery>
    //用id和密码登录  对密码进行hash,同时跟数据库里存储的密码hash值比较
    // 得到该账户对应的盐值
    query.prepare("SELECT salt FROM user WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
    QString salt;
    if(query.next()){
        salt=query.value(0).toString();
    }else{
        QMessageBox::information(this, "登录失败", "用户ID"+id+"不存在");
        return;
    }
    // 将密码和盐值连接后进行哈希
    QCryptographicHash hasher(QCryptographicHash::Sha256); 
    hasher.addData((password+salt).toUtf8());
    QString hashedPassword = hasher.result().toHex();
    qDebug()<<hashedPassword<<salt;
    // 利用哈希过的密码进行登录
    query.prepare("SELECT id FROM user WHERE id = :id AND password = :password");
    query.bindValue(":id", id);
    query.bindValue(":password", hashedPassword);
    query.exec();
    if(query.next()){
        qDebug()<<id;
        this->hide();
        MainWindow *w=new MainWindow(id);
        w->show();
    }else{
        QMessageBox::information(this, "登录失败", "用户名或密码错误");
    }
}


void login::on_pushButton_3_clicked()
{//关闭窗口
    this->close();
}

