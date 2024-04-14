#include "card.h"
#include "ui_card.h"
#include<QSqlQuery>
#include<QMessageBox>
#include<QSqlError>
card::card(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::card)
{
    ui->setupUi(this);
}

card::~card()
{
    delete ui;
}

void card::on_qcard_clicked()
{
    //根据输入的卡号，在card表中查询是否存在
    QString cno=ui->cno->text();
    QSqlQuery query;
    query.prepare("select cno,name,organization,category from card where cno = :cno");
    query.bindValue(":cno", cno);
    query.exec();
    if(query.next()){
        ui->cno->setStyleSheet("color: green");
        //ui中更新姓名，类别，单位的信息
        ui->name->setText(query.value(1).toString());
        ui->organization->setText(query.value(2).toString());
        ui->category->setText(query.value(3).toString());
    }else{
        ui->cno->setStyleSheet("color: red");
        QMessageBox::information(this, "查询失败", "卡号不存在");
    }
}


void card::on_add_clicked()
{
    //新增借书证，检查卡号是否已经存在
    QString cno=ui->cno->text();
    QSqlQuery query;
    query.prepare("select cno from card where cno = :cno");
    query.bindValue(":cno", cno);
    query.exec();
    if(query.next()){
        QSqlQuery q2;
        q2.exec("select max(cno)+1 from card");
        q2.next();
        QString available_cno=q2.value(0).toString();
        QMessageBox::information(this, "新增失败", "卡号"+cno+"已经存在,最小可用卡号为"+available_cno);
    }else{
        query.prepare("insert into card(cno,name,organization,category) values(:cno,:name,:organization,:category)");
        query.bindValue(":cno", cno);
        query.bindValue(":name",ui->name->text());
        query.bindValue(":organization",ui->organization->text());
        query.bindValue(":category",ui->category->text());
        if(query.exec()){
            QMessageBox::information(this,"新增借书卡成功","卡号"+cno+"新增成功");
        }else{
            QMessageBox::information(this,"新增借书卡失败",query.lastError().text());
        }
        
    }    
}


void card::on_upd_clicked()
{
    QString cno=ui->cno->text();
    QSqlQuery query;
    query.prepare("select cno from card where cno = :cno");
    query.bindValue(":cno", cno);
    query.exec();
    if(query.next()){
        query.prepare("update card set name=:name,organization=:organization,category=:category where cno=:cno");
        query.bindValue(":cno", cno);
        query.bindValue(":name",ui->name->text());
        query.bindValue(":organization",ui->organization->text());
        query.bindValue(":category",ui->category->text());
        if(query.exec()){
            QMessageBox::information(this,"修改借书卡成功","卡号"+cno+"修改成功");
        }else{
            QMessageBox::information(this,"修改借书卡失败",query.lastError().text());
        }
        
    }else{
        QMessageBox::information(this, "修改借书卡失败", "卡号"+cno+"不存在");
        
    }    
}


void card::on_del_clicked()
{
    QString cno=ui->cno->text();
    QSqlQuery query;
    query.prepare("select cno from card where cno = :cno");
    query.bindValue(":cno", cno);
    query.exec();
    if(query.next()){
        //查询是否有书未归还
        query.prepare("select bno from borrows where cno = :cno and return_date>now()");
        query.bindValue(":cno", cno);
        query.exec();
        if(query.next()){
            QMessageBox::information(this, "删除失败", "卡号"+cno+"还有书未归还");
            return;
        }
        query.prepare("delete from card where cno=:cno");
        query.bindValue(":cno", cno);
        if(query.exec()){
            QMessageBox::information(this,"删除借书卡成功","卡号"+cno+"删除成功");
        }else{
            QMessageBox::information(this,"删除借书卡失败",query.lastError().text());
        }
    }else{
        QMessageBox::information(this, "删除失败", "卡号"+cno+"不存在");
    }
}

