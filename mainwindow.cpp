#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "formreg.h"
#include "ui_formreg.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(400,300);
    connect(ui->lineEditAccount,SIGNAL(textChanged(QString)),this,SLOT(changeAvatar(QString)));
    connect(ui->lineEditPassword,SIGNAL(returnPressed()),this,SLOT(on_pushButtonLogin_clicked()));
    connect(ui->pushButtonRegister,SIGNAL(pressed()),this,SLOT(formRegister()));
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    //db.setHostName("localhost");
    //db.setUserName("root");
    //db.setPassword("0106105");
    //db.setDatabaseName("htychat");
    db.setHostName("123.56.70.166");
    db.setUserName("devhaitian");
    db.setPassword("dYeAsreEM4");
    db.setDatabaseName("devhaitian");
    if(db.open()){
        qDebug()<<"Open database suceed";
        //db.exec("Create Database If Not Exists htychat");
        //QMessageBox::critical(NULL, "创建数据库错误", db.lastError().text());
        //db.exec("create table if not exists user(id INT, name TEXT, signature TEXT, password TEXT, memo TEXT, homepage TEXT, domicile TEXT, email TEXT, regtime DATETIME, birthday DATE, avantar TEXT, phonenumber INT, sex TEXT)");
        //QMessageBox::critical(NULL, "创建表错误", db.lastError().text());
    }else{
        QMessageBox::critical(NULL, "打开数据库错误", db.lastError().text());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeAvatar(QString sa)
{
    if(sa=="123"){
        ui->labelAvatar->setPixmap(QPixmap(":/Garen.jpg"));
    }else{
        ui->labelAvatar->setPixmap(QPixmap(":/icon.png"));
    }
}

void MainWindow::on_pushButtonLogin_clicked()
{

    QSqlQuery query;
    QString sql="select * from user where id=" + ui->lineEditAccount->text() + " and password='" + ui->lineEditPassword->text() + "'";
    bool b=query.exec(sql);
    qDebug() << sql << b;
    if(query.next())
    {
        id = query.value("id").toInt();
        QString name = query.value("name").toString();
        QString signature = query.value("signature").toString();

        form=new Form;
        form->pathCache=pathCache;
        form->id=id;
        qDebug() << "Login ID:" << id;
        form->phonenumber=query.value("phonenumber").toInt();
        form->ui->labelName->setText(name);
        QFont font(form->ui->labelSignature->font());
        QFontMetrics FM(font);
        form->ui->labelSignature->setText(FM.elidedText(signature, Qt::ElideRight, form->ui->labelSignature->width()));
        form->ui->labelSignature->setToolTip(signature);
        form->homepage = query.value("homepage").toString();
        form->email = query.value("email").toString();
        form->domicile = query.value("domicile").toString();
        form->sex = query.value("sex").toString();
        form->regtime = query.value("regtime").toDateTime();
        form->birthday = query.value("birthday").toDate();

        QString surl=query.value("avantar").toString();
        form->urlAvantar=surl;
        //qDebug() << "avantar" << surl;
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyPixmapAccount(QNetworkReply*)));
        manager->get(QNetworkRequest(QUrl(surl)));
        form->show();

        sql="create table if not exists c" + QString::number(id) + "(id INT,category TEXT)";
        b=query.exec(sql);
        qDebug() << sql << b;

        sql="create table if not exists m" + QString::number(id) + "(idfrom INT,idto INT,message TEXT,time DATETIME)";
        b=query.exec(sql);
        qDebug() << sql << b;

        //联系人列表
        //QSqlQuery query;QString
        sql="select * from user,c" + QString::number(id) + " where user.id=c" + QString::number(id) + ".id order by CONVERT(name USING gbk)";
        //bool
        b=query.exec(sql);
        qDebug() << sql << b;
        i=0;
        manager = new QNetworkAccessManager(this);
        QNetworkReply *reply;
        QEventLoop loop;
        while(query.next())
        {
            int idc = query.value("id").toInt();
            QString namec = query.value("name").toString();
            QString sexc = query.value("sex").toString();
            QString domicilec = query.value("domicile").toString();
            QString urlac=query.value("avantar").toString();
            QString homepagec=query.value("homepage").toString();
            QString signaturec=query.value("signature").toString();
            QString emailc=query.value("email").toString();
            QString regtimec = query.value("regtime").toDateTime().toString("yyyy-M-d H:m:s");
            QString birthdayc = query.value("birthday").toDate().toString("yyyy-M-d");

            form->ui->tableWidgetContact->insertRow(i);
            form->ui->tableWidgetContact->setItem(i,0,new QTableWidgetItem(QIcon(":/icon.png"),""));
            form->ui->tableWidgetContact->setItem(i,1,new QTableWidgetItem(namec));
            form->ui->tableWidgetContact->setItem(i,2,new QTableWidgetItem(QString::number(idc)));
            form->ui->tableWidgetContact->setItem(i,3,new QTableWidgetItem(sexc));
            form->ui->tableWidgetContact->setItem(i,4,new QTableWidgetItem(domicilec));
            form->ui->tableWidgetContact->setItem(i,5,new QTableWidgetItem(urlac));
            form->ui->tableWidgetContact->setItem(i,6,new QTableWidgetItem(homepagec));
            form->ui->tableWidgetContact->setItem(i,7,new QTableWidgetItem(signaturec));
            form->ui->tableWidgetContact->setItem(i,8,new QTableWidgetItem(emailc));
            form->ui->tableWidgetContact->setItem(i,9,new QTableWidgetItem(regtimec));
            form->ui->tableWidgetContact->setItem(i,10,new QTableWidgetItem(birthdayc));
            form->ui->tableWidgetContact->item(i,0)->setToolTip(namec+"\n"+signaturec);
            form->ui->tableWidgetContact->item(i,1)->setToolTip(namec+"\n"+signaturec);

            //connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyPixmapContact(QNetworkReply*)));
            //manager->get(QNetworkRequest(QUrl(urlac)));
            reply = manager->get(QNetworkRequest(urlac));
            connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
            loop.exec();
            QPixmap pixmap;
            pixmap.loadFromData(reply->readAll());
            form->ui->tableWidgetContact->item(i,0)->setIcon(QIcon(pixmap.scaled(50,50)));

            i++;
        }
        form->ui->tableWidgetContact->resizeColumnsToContents();
        form->ui->tableWidgetContact->resizeRowsToContents();
    }else{
        QMessageBox::critical(NULL, "错误", "账号或密码不正确！");
    }

}

void MainWindow::replyPixmapAccount(QNetworkReply* reply){
    qDebug() << "reply" << reply->error();
    QPixmap pixmap;
    pixmap.loadFromData(reply->readAll());
    QString path = pathCache + "/" + QString::number(id) + ".jpg";
    qDebug() << "pixmap.save(" << path << ")";
    pixmap.save(path,0,100);
    form->ui->pushButtonAvantar->setIcon(QIcon(pixmap.scaled(60,60)));
    close();
}

void MainWindow::formRegister()
{
    FormReg *formreg=new FormReg;
    formreg->show();
}

//void MainWindow::replyPixmapContact(QNetworkReply* reply)
//{
//    qDebug() << "reply" << reply->error();
//    QPixmap pixmap;
//    pixmap.loadFromData(reply->readAll());
//    form->ui->tableWidgetContact->item(i-1,0)->setIcon(QIcon(pixmap.scaled(50,50)));
//}
