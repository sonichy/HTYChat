#include "formreg.h"
#include "ui_formreg.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QtGlobal>
#include <QDebug>
#include <QDesktopWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>

FormReg::FormReg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormReg)
{
    ui->setupUi(this);
    //setFixedSize(300,421);
    ui->pushButton_genVerificationCode->setFlat(true);
    QStringList sexes;
    sexes << "男" << "女";
    ui->comboBoxSex->addItems(sexes);
    move((QApplication::desktop()->width() - width())/2, (QApplication::desktop()->height() - height())/2);
    setWindowFlags((windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);
    connect(ui->pushButtonRegister,SIGNAL(pressed()),this,SLOT(registerAccount()));
    connect(ui->pushButtonDisplayPassword,SIGNAL(toggled(bool)),this,SLOT(displayPassword(bool)));
    connect(ui->lineEditAvantar,SIGNAL(returnPressed()),this,SLOT(getAvantar()));
    connect(ui->pushButton_genVerificationCode, SIGNAL(pressed()), this, SLOT(genVerificationCode()));
    genID();
    genVerificationCode();
}

FormReg::~FormReg()
{
    delete ui;
}

void FormReg::registerAccount()
{
    if(ui->lineEdit_verificationCode->text() == ui->pushButton_genVerificationCode->text()){
        QSqlQuery query;
        QDateTime now = QDateTime::currentDateTime();
        QString sql = "insert into user(id,avantar,name,password,sex,birthday,domicile,phonenumber,email,homepage,regtime) values(" + ui->labelAccount->text() + ",'" + ui->lineEditAvantar->text() + "','" + ui->lineEditName->text() + "','" + ui->lineEditPassword->text() + "','" + ui->comboBoxSex->currentText() + "','" + ui->dateEditBirthday->date().toString("yyyy-M-d") + "','" + ui->lineEditDomicile->text() + "'," + ui->lineEditPhoneNumber->text() + ",'" + ui->lineEditEmail->text() + "','" + ui->lineEditHomepage->text() + "','" + now.toString("yyyy-M-d H:m:s") + "')";
        bool b = query.exec(sql);
        qDebug() << sql << b;
        if(b){
            QMessageBox::information(NULL, "信息", "注册成功！");
        }else{
            QMessageBox::critical(NULL, "错误", "注册失败！");
        }
        sql="create table u" + ui->labelAccount->text() + "(id INT,group TEXT)";
        b = query.exec(sql);
        qDebug() << sql << b;
        sql="create table m" + ui->labelAccount->text() + "(idfrom INT,idto INT,message TEXT,time DATETIME)";
        b = query.exec(sql);
        qDebug() << sql << b;
    }else{
        QMessageBox::critical(NULL, "错误", "验证码不正确！");
    }
}

void FormReg::displayPassword(bool checked)
{
    if(checked){
        ui->lineEditPassword->setEchoMode(QLineEdit::Normal);
    }else{
        ui->lineEditPassword->setEchoMode(QLineEdit::Password);
    }
}

void FormReg::getAvantar()
{
    ui->lineEditAvantar->setCursorPosition(0);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyPixmap(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(ui->lineEditAvantar->text())));
}

void FormReg::replyPixmap(QNetworkReply *reply)
{
    qDebug() << "reply" << reply->error();
    QPixmap pixmap;
    pixmap.loadFromData(reply->readAll());
    ui->labelAvantar->setPixmap(pixmap.scaled(60,60));
}

void FormReg::genID()
{
    int r=qrand()%10000;
    QSqlQuery query;
    QString sql = "select * from user where id=" + QString::number(r);
    bool b = query.exec(sql);
    qDebug() << sql << b;
    if(query.next()){
        genID();
        return;
    }
    ui->labelAccount->setText(QString::number(r));
}

void FormReg::genVerificationCode()
{
    QString s = "A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,0,1,2,3,4,5,6,7,8,9";
    QStringList SL = s.split(",");
    QString VC = "";
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i=0; i<4; i++){
        int n = qrand() % 62;
        qDebug() << n;
        VC += SL.at(n);
    }
    ui->pushButton_genVerificationCode->setText(VC);
}