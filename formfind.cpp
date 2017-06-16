#include "formfind.h"
#include "ui_formfind.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QNetworkAccessManager>

FormFind::FormFind(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormFind)
{
    ui->setupUi(this);
    setFixedSize(600,450);
    connect(ui->pushButtonFind,SIGNAL(pressed()),this,SLOT(search()));
    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(search()));
}

FormFind::~FormFind()
{
    delete ui;
}

void FormFind::search()
{
    //if(ui->lineEdit->text()!=""){
        ui->listWidget->clear();
        QSqlQuery query;
        QString sql;
        if(ui->lineEdit->text().data()->isNumber()){
            sql="select * from user where id=" + ui->lineEdit->text();
        }else{
            sql="select * from user where name like '%" + ui->lineEdit->text() + "%'";
        }
        bool b=query.exec(sql);
        qDebug() << sql << b;
        while(query.next())
        {
            int ids = query.value("id").toInt();
            QString name = query.value("name").toString();
            QString sex = query.value("sex").toString();
            QString domicile = query.value("domicile").toString();
            QString urla=query.value("avantar").toString();
            //qDebug() << "data:" << id << name << sex << domicile << urla;
            ItemFind *itemfind=new ItemFind;
            itemfind->id=id;
            qDebug() << "ItemFind" << ids;
            itemfind->ui->labelAccount->setText(QString::number(ids));
            itemfind->ui->labelName->setText(name);
            itemfind->ui->labelSex->setText(sex);
            itemfind->ui->labelDomicile->setText(domicile);
            QListWidgetItem *LWI = new QListWidgetItem(ui->listWidget);
            ui->listWidget->addItem(LWI);
            ui->listWidget->setItemWidget(LWI,itemfind);
            LWI->setSizeHint(QSize(140,70));
            itemfind->getPixmap(urla);
        }
    //}
}
