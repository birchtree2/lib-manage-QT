#include "user.h"
#include "ui_user.h"
#include<QSqlQuery>
#include<QSqlError>
#include<QDateTime>
#include<QMessageBox>
#include<QCryptographicHash>
#include<QUuid>
user::user(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::user)
{
    ui->setupUi(this);
    ui->password->setEchoMode(QLineEdit::Password);
    ui->confirm_password->setEchoMode(QLineEdit::Password);
}

user::~user()
{
    delete ui;
}

void user::on_add_clicked()
{
    QString id=ui->id->text();
    QString name=ui->name_2->text();
    QString password=ui->password->text();
    QString confirm_password=ui->confirm_password->text();
    QString contact=ui->contact->text();
    if(password!=confirm_password){
        QMessageBox::information(this, "新增失败", "两次输入的密码不一致");
        return;
    }
    QSqlQuery query;
    query.prepare("select id from user where id = :id");
    query.bindValue(":id", id);
    query.exec();
    //生成盐(用uuid)，对明文密码进行加盐hash  给出需要的头文件
    /*参考登录过程
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
    */
    QString salt = QUuid::createUuid().toString().replace("{","").replace("}","").replace("-","");
    QCryptographicHash hasher(QCryptographicHash::Sha256);
    hasher.addData((password+salt).toUtf8());
    QString hashedPassword = hasher.result().toHex();
    qDebug()<<hashedPassword<<salt<<password<<confirm_password;
    if(query.next()){
        QMessageBox::information(this, "新增失败", "用户ID"+id+"已经存在");
    }else{
        query.prepare("insert into user(id,password,salt,name,contact) values(:id,:password,:salt,:name,:contact)");
        query.bindValue(":id", id);
        query.bindValue(":name",name);
        query.bindValue(":password",hashedPassword);
        query.bindValue(":salt",salt);
        query.bindValue(":contact",contact);
        if(query.exec()){
            QMessageBox::information(this,"新增用户成功","用户ID"+id+"新增成功");
        }else{
            QMessageBox::information(this,"新增失败","用户ID"+id+"新增失败");
        }
    }
}

