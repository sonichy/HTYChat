#include "itemfind.h"
#include "ui_itemfind.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

ItemFind::ItemFind(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemFind)
{
    ui->setupUi(this);
    ui->labelAccount->setVisible(false);
    connect(ui->pushButtonAdd,SIGNAL(pressed()),this,SLOT(addAccount()));
}

ItemFind::~ItemFind()
{
    delete ui;
}

void ItemFind::addAccount()
{
    ui->pushButtonAdd->setStyleSheet("");
    ui->pushButtonAdd->setEnabled(false);
    if(ui->labelAccount->text().toInt()==id){
        QMessageBox::critical(NULL, "错误", "不能添加自己为好友！");
    }else{
        QSqlQuery query;
        QString sql="select * from c" + QString::number(id) + " where id=" + ui->labelAccount->text();
        bool b=query.exec(sql);
        qDebug() << sql << b;
        if(query.next()){
            QMessageBox::critical(NULL, "错误", "你已经添加过这个好友，不能重复添加！");
        }else{
            sql="insert into c" + QString::number(id) + "(id) values(" + ui->labelAccount->text() + ")";
            b=query.exec(sql);
            qDebug() << sql << b;
            if(b){
                QMessageBox::information(NULL, "信息", "添加好友成功！");
            }else{
                QMessageBox::critical(NULL, "错误", "添加好友失败！");
            }
        }
    }
}

void ItemFind::getPixmap(QString url)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyPixmap(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(url)));
}

void ItemFind::replyPixmap(QNetworkReply* reply)
{
    //qDebug() << "reply" << reply->error();
    QPixmap pixmap;
    pixmap.loadFromData(reply->readAll());
    ui->labelAvantar->setPixmap(pixmap.scaled(60,60));
}
