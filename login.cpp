#include "login.h"
#include "ui_login.h"
#include <QMEssageBox>
#include <qDebug>
#include <QSqlQuery>
#include <mainwindow.h>
#include <QLineEdit>
login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    login::username=ui->lineEdit->text();
    QString password=ui->lineEdit_2->text();
    QSqlQuery query;//#include <QSqlQuery>
    if(login::username.length()!=0&&password.length()!=0){
        //写下将要执行的SQL语句
        QString instruction=QString("select password from users where number='%1'").arg(login::username);
        /*%1，百分号后面数字并没有什么特别含义，但是需要按照从小到大的顺序写，从前到后依次与后面.arg(对应)
        根据sql语句的格式可得，如果字段为字符串则需要加单引号，如果是数，则不需要加单引号*/
        query.exec(instruction);//用工具执行这个语句
        //如果返回结果为空
        if(!query.next()){
            QMessageBox::information(this, "登录失败", "用户名或者密码错误");
        }
        while(query.next())//循环执行结果的集合
        {//开始判定
            if(login::username=="0000"&&password=="123456"){//此处是我设定的管理员账号，如果是管理员，会跳转到MainWindow
                this->close();
                MainWindow* w=new MainWindow();
                w->show();
                break;
            }
            else//如果不是管理员，则跳转到userinterface
                if(login::username!="0000"&&query.value(0).toString()==password){
                    // this->close();
                    // userinterface* w2=new userinterface();
                    // w2->show();
                     QMessageBox::information(this, "登录成功", "");
                    break;
                }
                else{
                    QMessageBox::information(this, "登录失败", "用户名或者密码错误");
                    break;
                }
        }
    }
    else{
        QMessageBox::warning(this,"登录失败","不能为空！");
    }
    //在登录时获得登录用户的id，后面要用
    QString getId=QString("select id from users where number='%1'").arg(login::username);
    query.exec(getId);
    while(query.next()){
        login::id=query.value(0).toInt();
    }

}


void login::on_pushButton_3_clicked()
{//关闭窗口
    this->close();
}

