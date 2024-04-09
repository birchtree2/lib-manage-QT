#include "qbook.h"
#include "ui_qbook.h"
#include<QSqlQuery>
#include<QSqlError>
qbook::qbook(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::qbook)
{
    ui->setupUi(this);
}

qbook::~qbook()
{
    delete ui;
}

void qbook::on_pushButton_clicked()
{
    QSqlQuery query;
    //根据勾选的条件生成查询,用and连接
    QString baseQuery = "SELECT bno,category,title,publisher,year,author,price,total_stock,stock FROM book WHERE 1=1";
    //加一个true的条件，防止一个条件时where后面直接跟and
    if (ui->checkauthor->checkState() == Qt::Checked) {
        baseQuery += " AND author = :author";
    }
    if (ui->checktitle->checkState() == Qt::Checked) {
        baseQuery += " AND title = :title";
    }
    if (ui->checkpress->checkState() == Qt::Checked) {
        baseQuery += " AND publisher = :press";
    }
    if (ui->checkcategory->checkState() == Qt::Checked) {
        baseQuery += " AND category = :category";
    }
    if (ui->checkyear->checkState() == Qt::Checked) {
        if (!ui->year1->text().isEmpty()) {
        baseQuery += " AND year >= :year1";
        }
        if (!ui->year2->text().isEmpty()) {
        baseQuery += " AND year <= :year2";
        }
    }
    if (ui->checkprice->checkState() == Qt::Checked) {
        if (!ui->price1->text().isEmpty()) {
            baseQuery += " AND price >= :price1";
        }
        if (!ui->price2->text().isEmpty()) {
            baseQuery += " AND price <= :price2";
        }
    }
    query.prepare(baseQuery);//准备查询
    //bindValue防止sql注入
    if (ui->checkauthor->checkState() == Qt::Checked) {
        query.bindValue(":author", ui->author->text());
    }
    if (ui->checktitle->checkState() == Qt::Checked) {
        query.bindValue(":title", ui->title->text());
    }
    if (ui->checkpress->checkState() == Qt::Checked) {
        query.bindValue(":press", ui->press->text());
    }
    if (ui->checkcategory->checkState() == Qt::Checked) {
        query.bindValue(":category", ui->category->text());
    }
    if (ui->checkyear->checkState() == Qt::Checked) {
        if (!ui->year1->text().isEmpty()) {
            query.bindValue(":year1", ui->year1->text());
        }
        if (!ui->year2->text().isEmpty()) {
            query.bindValue(":year2", ui->year2->text());
        }
    }
    if (ui->checkprice->checkState() == Qt::Checked) {
        if (!ui->price1->text().isEmpty()) {
            query.bindValue(":price1", ui->price1->text());
        }
        if (!ui->price2->text().isEmpty()) {
            query.bindValue(":price2", ui->price2->text());
        }
    }
    //根据qcombobox选择排序方式 
    switch (ui->orderkey->currentIndex()) {
        case 0:
            baseQuery += " order by title";
            break;
        case 1:
            baseQuery += " order by bno";
            break;
        case 2:
            baseQuery += " order by year";
            break;
        case 3:
            baseQuery += " order by price";
            break;
        case 4:
            baseQuery += " order by author";
            break;
        default: 
            baseQuery += " order by title";
            break;
    }
    switch (ui->orderway->currentIndex()) {
        case 0:
            baseQuery += " asc";
            break;
        case 1:
            baseQuery += " desc";
            break;
        default: break;
    }
    //输出准备好的sql
    qDebug()<<baseQuery;
    // qDebug()<<"ok";
    query.exec();
    // qDebug()<<query.next();
    QStringList header;
    header<<"书号"<<"类别"<<"书名"<<"出版社"<<"年份"<<"作者"<<"价格"<<"总藏书量"<<"库存量";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->clearContents();
    ui->tableWidget->setColumnCount(9);
    while(query.next()){
        qDebug()<<query.value(0).toString();
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        for(int i = 0; i < 9; i++){
            ui->tableWidget->setItem(row, i, new QTableWidgetItem(query.value(i).toString()));
        }
    }
    
}

