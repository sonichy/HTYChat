#include "formchat.h"
#include "ui_formchat.h"
#include "formprofile.h"
#include "ui_formprofile.h"
#include <QDesktopServices>
#include <QDesktopWidget>
#include <QDebug>
#include <QDateTime>
#include <QShortcut>
#include <QFileDialog>
#include <QSqlQuery>

FormChat::FormChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormChat)
{
    ui->setupUi(this);
    move((QApplication::desktop()->width() - width())/2, (QApplication::desktop()->height() - height())/2);
    show();
    connect(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Return),this), SIGNAL(activated()),this, SLOT(send()));
    connect(new QShortcut(QKeySequence(Qt::ALT + Qt::Key_C),this), SIGNAL(activated()),this, SLOT(close()));
    connect(ui->pushButtonAvartar,SIGNAL(pressed()),this,SLOT(profile()));
    connect(ui->pushButtonSend,SIGNAL(clicked(bool)),this,SLOT(send()));
    connect(ui->pushButtonHomepage,SIGNAL(clicked(bool)),this,SLOT(openURL()));
    connect(ui->pushButtonClose,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ui->pushButtonHistory,SIGNAL(pressed()),this,SLOT(history()));
}

FormChat::~FormChat()
{
    delete ui;
}

void FormChat::send()
{
    if(ui->plainTextEdit->toPlainText()!=""){
        //QDateTime time = QDateTime::currentDateTime();
        //QString stime = time.toString("yyyy-M-d H:mm:ss");
        //ui->textBrowser->insertHtml("<div style='color:blue;'>" + stime + "</div><table><tr><td><img src='"+ pathCache + "/" + QString::number(id) +".jpg' width=30 height=30></td><td>" + ui->plainTextEdit->toPlainText() + "</td></tr></table>");
        //ui->textBrowser->moveCursor(QTextCursor::End);

        QSqlQuery query;
        QDateTime now = QDateTime::currentDateTime();
        QString sql = "insert into m" + QString::number(id) + "(idfrom,idto,message,time) values(" + QString::number(id) + "," + QString::number(idc) + ",'" + ui->plainTextEdit->toPlainText() + "','" + now.toString("yyyy-M-d H:m:s") + "')";
        bool b = query.exec(sql);
        qDebug() << sql << b;
        sql = "insert into m" + QString::number(idc) + "(idfrom,idto,message,time) values(" + QString::number(id) + "," + QString::number(idc) + ",'" + ui->plainTextEdit->toPlainText() + "','" + now.toString("yyyy-M-d H:m:s") + "')";
        b = query.exec(sql);
        qDebug() << sql << b;
        ui->plainTextEdit->setPlainText("");
        history();
    }
}

void FormChat::openURL()
{
    QDesktopServices::openUrl(homepagec);
}

void FormChat::on_pushButtonImg_clicked()
{
    if(filename==""){
        filename = QFileDialog::getOpenFileName(this, "打开文本", QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).first(),"图片 (*.png *.jpg *.bmp)");
    }else{
        filename = QFileDialog::getOpenFileName(this, "打开文本", filename, "图片 (*.png *.jpg *.bmp)");
    }
    if(!filename.isEmpty())
    {
        QDateTime time = QDateTime::currentDateTime();
        QString stime = time.toString("yyyy-MM-dd hh:mm:ss");
        ui->textBrowser->insertHtml("<div style='color:blue;'>" + stime + "</div><table><tr><td><img src='"+ pathCache + "/" + QString::number(id) +".jpg' width=30 height=30></td><td><img src=" + filename + "></td></tr></table>");
        ui->textBrowser->moveCursor(QTextCursor::End);
    }
}

void FormChat::profile()
{
    FormProfile *formProfile=new FormProfile;
    formProfile->ui->pushButtonEdit->setVisible(false);
    formProfile->ui->labelID->setText(QString::number(idc));    
    formProfile->ui->labelName->setText(namec);
    formProfile->ui->labelSignature->setText(signaturec);
    formProfile->ui->labelDomicile->setText(domicilec);
    formProfile->ui->labelHomepage->setText(homepagec);
    formProfile->ui->labelSex->setText(sexc);
    formProfile->ui->labelEmail->setText(emailc);
    formProfile->ui->labelBirthday->setText(birthdayc);
    formProfile->ui->labelRegTime->setText(regtimec);
    //QString path=pathCache + "/" + QString::number(idc) + ".jpg";
    //QPixmap pixmap(path);
    formProfile->ui->labelAvantar->setPixmap(ui->pushButtonAvartar->icon().pixmap(60,60));
    formProfile->show();
}

void FormChat::history()
{
    ui->textBrowser->setText("");
    QSqlQuery query;
    QString sql = "select * from m" + QString::number(id) + " where idfrom=" + QString::number(idc) + " or idto="+QString::number(idc) + " order by time asc";
    bool b = query.exec(sql);
    qDebug() << sql << b;
    while(query.next())
    {
        if(query.value("idfrom").toInt()==idc){
            ui->textBrowser->insertHtml("<table><tr><td colspan=2 style='color:gray;'>" + query.value("time").toDateTime().toString("yyyy-M-d H:mm:ss") + "</td></tr><tr><td><img src='"+ pathCache + "/" + QString::number(idc) +".jpg' width=30 height=30></td><td style='border:1px solid blue;border-radius:5px;'>" + query.value("message").toString() + "</td></tr></table>");
        }
        if(query.value("idto").toInt()==idc){
            ui->textBrowser->insertHtml("<table align=right><tr><td colspan=2 style='color:gray;text-align:right;'>" + query.value("time").toDateTime().toString("yyyy-M-d H:mm:ss") + "</td></tr><tr><td>" + query.value("message").toString() + "</td><td><img src='"+ pathCache + "/" + QString::number(id) +".jpg' width=30 height=30></td></tr></table>");
        }
        ui->textBrowser->moveCursor(QTextCursor::End);
    }
}
