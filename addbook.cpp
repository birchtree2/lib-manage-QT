#include "addbook.h"
#include "ui_addbook.h"
#include <QFileDialog>
#include<QMessageBox>
#include<QSqlQuery>
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

void addbook::on_pushButton_clicked()
{
    if(ui->checkBox->checkState()==Qt::Checked){//批量入库

        QString filePath=ui->filename->text();
        //qDebug()<<filePath;
        QFile file(filePath);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))//只读
        {
            QMessageBox::information(this, "入库失败", "不存在文件"+filePath);
            return;
        }
        //每条图书信息为一行. 一行中的内容如下
        //( 书号, 类别, 书名, 出版社, 年份, 作者, 价格, 数量 ) 
        //Note: 其中 年份、数量是整数类型； 价格是两位小数类型； 其余为字符串类型
        QTextStream in(&file);
        int total_cnt=0,succ_cnt=0;
        while (!in.atEnd()) {
            total_cnt++;
            QString line = in.readLine();
            QStringList list = line.split(",");
            if(list.size()!=8){
                QMessageBox::information(this, "入库失败", "文件格式错误,每行用逗号分隔，显示(书号, 类别, 书名, 出版社, 年份, 作者, 价格, 数量 )");
                return;
            }
            QString bno=list[0].trimmed();
            QString category=list[1].trimmed();
            QString title=list[2].trimmed();
            QString publisher=list[3].trimmed();
            QString year=list[4].trimmed();
            QString author=list[5].trimmed();
            QString price=list[6].trimmed();
            QString total_stock=list[7].trimmed();
            QSqlQuery query;
            query.prepare("INSERT INTO book (bno,category,title,publisher,year,author,price,total_stock,stock) VALUES (:bno,:category,:title,:publisher,:year,:author,:price,:total_stock,:stock)");
            query.bindValue(":bno", bno);
            query.bindValue(":category", category);
            query.bindValue(":title", title);
            query.bindValue(":publisher", publisher);
            query.bindValue(":year", year);
            query.bindValue(":author", author);
            query.bindValue(":price", price);
            query.bindValue(":total_stock", total_stock);
            query.bindValue(":stock", total_stock);
            //分别显示成功和失败
            if(query.exec()){
               succ_cnt++; 
            }
        }
        QMessageBox::information(this, "入库结果", QString("共%1条记录,成功入库%2条").arg(total_cnt,succ_cnt));

    }else{//单本入库
        QString bno=ui->lineEdit->text();
        QString category=ui->lineEdit_2->text();
        QString title=ui->lineEdit_3->text();
        QString publisher=ui->lineEdit_4->text();
        QString year=ui->lineEdit_5->text();
        QString author=ui->lineEdit_6->text();
        QString price=ui->lineEdit_8->text();
        QString total_stock=ui->lineEdit_7->text();
        QSqlQuery query;
        query.prepare("INSERT INTO book (bno,category,title,publisher,year,author,price,total_stock,stock) VALUES (:bno,:category,:title,:publisher,:year,:author,:price,:total_stock,:stock)");
        query.bindValue(":bno", bno);
        query.bindValue(":category", category);
        query.bindValue(":title", title);
        query.bindValue(":publisher", publisher);
        query.bindValue(":year", year);
        query.bindValue(":author", author);
        query.bindValue(":price", price);
        query.bindValue(":total_stock", total_stock);
        query.bindValue(":stock", total_stock);
        if(!query.exec()){
            QMessageBox::information(this, "入库失败", "插入失败");
            return;
        }

    }
}


void addbook::on_pushButton_2_clicked()
{
    QFileDialog *f=new QFileDialog(this);
    f->setWindowTitle("选择数据文件*.txt");
    f->setNameFilter("*.txt");
    f->setViewMode(QFileDialog::Detail);
    QString filePath;
    if(f->exec()==QDialog::Accepted){
        filePath=f->selectedFiles()[0];
        ui->filename->setText(filePath);
    }

}

