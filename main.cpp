#include "mainwindow.h"
// #include <QCoreApplication>
#include <QApplication>
#include <QSqlDatabase>
#include<QSqlQuery>
#include "login.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");//连接本机数据库，也可以填上某个IP去连接另一台设备的数据库
    db.setPort(3306);
    db.setDatabaseName("libtest");//数据库名称
    db.setUserName("root");//用户名
    db.setPassword("ypy20040307");//用户密码
    db.open();//连接数据库
    //测试数据库是否打开
    if(db.open())
    {
        qDebug()<<"数据库打开成功";
    }
    else
    {
        qDebug()<<"数据库打开失败";
    }
    // QSqlQuery q;
    // q.prepare("SELECT bno,category,title,publisher,year,author,price,total_stock,stock FROM book WHERE 1=1 order by price asc");
    // q.exec();
    // while(q.next()){
    //     qDebug()<<q.value(0).toString();
    // }
    login w;
    w.show();
    return a.exec();
}
