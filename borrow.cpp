#include "borrow.h"
#include "ui_borrow.h"
#include <QSqlQuery>
#include <QMessageBox>
borrow::borrow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::borrow)
{
    ui->setupUi(this);
}

borrow::~borrow()
{
    delete ui;
}
////检查字符串是否只包含数字,一个单独的函数
inline bool is_num(const QString & s){
    for(int i=0;i<s.length();i++){
        if(s[i]<'0' || s[i]>'9') return 0;
    }
    return 1;
}
bool borrow::is_valid_bno(const QString& bno){
    if(!is_num(bno)){
        QMessageBox::information(this, "查询失败", "书号只能包含数字");
        return 0;
    }
    QSqlQuery query;
    QString q1=QString(
     "select * from book where bno=%1"
     ).arg(bno);
    query.exec(q1);
    if(!query.next()){
        QMessageBox::information(this, "查询失败", "书号不存在");
        return 0;
    }
    return 1;
} 
bool borrow::is_valid_cno(const QString& cno){
    if(!is_num(cno)){
        QMessageBox::information(this, "查询失败", "借书证号只能包含数字");
        return 0;
    }
    QSqlQuery query;
    QString q1=QString(
     "select * from card where cno=%1"
     ).arg(cno);
    query.exec(q1);
    if(!query.next()){
        QMessageBox::information(this, "查询失败", "借书证号不存在");
        return 0;
    }
    return 1;
}
void borrow::on_pushButton_clicked()//查询已借书籍
{
    QString cno=ui->cno->text();
    QSqlQuery query;
    if(cno.length()!=0){
        if(!is_valid_cno(cno)) return;
        QString q2=QString(
           "select * from borrows \
            join book on borrows.bno=book.bno\
            where borrows.cno=%1 order by borrow_date asc").arg(cno);
        query.exec(q2);
        // qDebug()<<q2;
        int i=0;
        ui->tableWidget->setColumnCount(5);//记得设置row和column的count
        //设置表头
        QStringList header;
        header<<"书号"<<"书名"<<"借书日期"<<"还书日期"<<"管理员号";
        ui->tableWidget->setHorizontalHeaderLabels(header);
        while(query.next())//加入表格
        {
            qDebug()<<query.value("bno").toString();
            ui->tableWidget->setRowCount(i+1);

            ui->tableWidget->setItem(i,0,new QTableWidgetItem(query.value("bno").toString()));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value("title").toString()));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value("borrow_date").toString()));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(query.value("return_date").toString()));
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(query.value("admin_id").toString()));
            i++;
        }
        //无已借书籍
        if(i==0){
            QMessageBox::information(this, "查询失败", "无已借书籍");
            return;
        }
    }
}



void borrow::on_pushButton_2_clicked()//借书
{
    QString cno=ui->cno->text();
    QString bno=ui->bno->text();
    QString admin_id="2001";
    QSqlQuery query;
    if(cno.length()!=0 && bno.length()!=0 && admin_id.length()!=0){
        if(!is_valid_cno(cno)||!is_valid_bno(bno)) return;
        QString q4=QString(
           "select * from borrows where cno=%1 and bno=%2 where return_date>now()"
           ).arg(cno,bno);
        query.exec(q4);
        if(query.next()){
            QMessageBox::information(this, "借书失败", "已借阅该书籍");
            return;
        }
        //从book表中查询库存
        QString q6=QString(
            "select * from book where bno=%1"
        ).arg(bno);
        query.exec(q6);
        query.next();
        int stock=query.value("stock").toInt();
        if(stock<=0){//如果没有库存，从借书记录中找到离当前最近的还期
            QString q7=QString(
                "select * from borrows where bno=%1 and return_date>now() order by return_date asc limit 1"
            ).arg(bno);
            query.exec(q7);
            query.next();
            QString borrow_date=query.value("borrow_date").toString();
            QString return_date=query.value("return_date").toString();
            QMessageBox::information(this, "借书失败", "库存不足,最近借阅日期为"+
            borrow_date+"预计于"+return_date+"有人归还");
            return;
        }
        QString q5=QString(
           "insert into borrows(cno,bno,borrow_date,return_date,admin_id) values(%1,%2,now(),date_add(now(),interval 30 day),%3); \
            update book set stock=stock-1 where bno=%4"
           ).arg(cno,bno,admin_id,bno);//更新borrow和book
        qDebug()<<q5;
        query.exec(q5);
        QMessageBox::information(this, "借书成功", "借书成功");
    }
    else{
        QMessageBox::information(this, "借书失败", "信息不完整");
    }
}


void borrow::on_pushButton_3_clicked()//还书
{
    QString cno=ui->cno->text();
    QString bno=ui->bno->text();
    QString admin_id="2001";
    QSqlQuery query;
    if(cno.length()!=0 && bno.length()!=0 && admin_id.length()!=0){
        if(!is_valid_cno(cno)||!is_valid_bno(bno)) return;
        QString q4=QString(
           "select * from borrows where cno=%1 and bno=%2 and return_date>now()"
           ).arg(cno,bno);
        query.exec(q4);
        if(!query.next()){
            QMessageBox::information(this, "还书失败", "无未还该书籍记录");
            return;
        }
        QString q5=QString(
            "update book set stock=stock+1 where bno=%1;\
            update borrows set return_date=now() where cno=%2 and bno=%3 and return_date>now()"
           ).arg(bno,cno,bno);
        qDebug()<<q5;
        query.exec(q5);
        QMessageBox::information(this, "还书成功", "还书成功");
    }
    else{
        QMessageBox::information(this, "还书失败", "信息不完整");
    }
}

