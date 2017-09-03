#include "mainwindow.h"
#include "form.h"
#include "ui_form.h"
#include "formfind.h"
#include "ui_formfind.h"
#include "formchat.h"
#include "ui_formchat.h"
#include "formprofile.h"
#include "ui_formprofile.h"
#include <QDesktopWidget>
#include <QMenu>
#include <QMessageBox>
#include <QDebug>
#include <QUrl>
#include <QDesktopServices>
#include <QStandardItem>
#include <QSqlQuery>

QMenu *submenu;
QStandardItemModel *SIM;
FormProfile *formProfile;

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    setStyleSheet("QPushButton::menu-indicator{width:0px;}");
    setWindowFlags((windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);
    move(QApplication::desktop()->width() - width() - 100, 0);
    for(int c=2;c<11;c++){
        ui->tableWidgetContact->setColumnHidden(c,true);
    }
    connect(ui->pushButtonAvantar,SIGNAL(pressed()),this,SLOT(profile()));

    submenu=new QMenu(this);
    //setContextMenuPolicy(Qt::CustomContextMenu);
    QAction *logout=new QAction("注销",this);
    QAction *lock=new QAction("锁定",this);
    QAction *about=new QAction("关于",this);
    QAction *quit=new QAction("退出",this);
    submenu->addAction(logout);
    submenu->addAction(lock);
    submenu->addAction(about);
    submenu->addAction(quit);
    ui->pushButtonMenu->setMenu(submenu);
    //connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showMenu(const QPoint&)));
    connect(logout,SIGNAL(triggered()),this,SLOT(logout()));
    connect(lock,SIGNAL(triggered()),this,SLOT(lock()));
    connect(about,SIGNAL(triggered()),this,SLOT(about()));
    connect(quit,SIGNAL(triggered()),qApp,SLOT(quit()));
    connect(ui->tableWidgetContact,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(chat(int,int)));
    connect(ui->tableWidgetContact, SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(TWContextMenu(QPoint)));
}

Form::~Form()
{
    delete ui;
}

void Form::about(){
    QMessageBox MBAbout(QMessageBox::NoIcon, "关于", "海天鹰聊天 1.0 Alpha\n一款基于 Qt + MYSQL 的聊天程序。\n作者：黄颖\nE-mail: sonichy@163.com\n主页：sonichy.96.lt\n参考：\n腾讯QQ");
    MBAbout.setIconPixmap(QPixmap(":/icon.png"));
    MBAbout.exec();
}

void Form::logout(){
    qDebug() << "logout";
    MainWindow *w=new MainWindow;
    w->move((QApplication::desktop()->width() - w->width())/2, (QApplication::desktop()->height() - w->height())/2);
    w->setWindowFlags((w->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);
    w->show();
    close();
}

void Form::lock(){

}

void Form::showMenu(const QPoint &point)
{
    qDebug() << point;
    //submenu->exec(point);
    //submenu->exec(mapToGlobal(point));
}

void Form::on_pushButtonMenu_clicked()
{
    QPoint pos;
    pos.setX(0);
    pos.setY(-submenu->sizeHint().height());
    qDebug() << pos;
    submenu->exec(ui->pushButtonMenu->mapToGlobal(pos));
}

void Form::on_pushButtonHomepage_clicked()
{
    QUrl url(homepage);
    QDesktopServices::openUrl(url);
}

void Form::on_pushButtonAdd_clicked()
{
    FormFind *formfind=new FormFind;
    formfind->id=id;
    //qDebug() << id << ":FormFind";
    formfind->move((QApplication::desktop()->width() - formfind->width())/2, (QApplication::desktop()->height() - formfind->height())/2);
    formfind->setWindowFlags((formfind->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);
    formfind->show();
}

void Form::chat(int row,int column)
{   
    FormChat *formchat=new FormChat;
    formchat->pathCache=pathCache;
    formchat->id=id;
    formchat->name=name;
    formchat->namec=ui->tableWidgetContact->item(row,1)->text();
    formchat->sexc=ui->tableWidgetContact->item(row,3)->text();
    formchat->domicilec=ui->tableWidgetContact->item(row,4)->text();
    formchat->homepagec=ui->tableWidgetContact->item(row,6)->text();
    formchat->signaturec=ui->tableWidgetContact->item(row,7)->text();
    formchat->emailc=ui->tableWidgetContact->item(row,8)->text();
    formchat->regtimec=ui->tableWidgetContact->item(row,9)->text();
    formchat->birthdayc=ui->tableWidgetContact->item(row,10)->text();
    formchat->ui->pushButtonName->setText(ui->tableWidgetContact->item(row,1)->text());
    //QString path=pathCache + "/" + ui->tableWidgetContact->item(row,2)->text() + ".jpg";
    //qDebug() << "Chat Icon:" << path;
    //formchat->ui->pushButtonAvartar->setIcon(QIcon(path));
    formchat->ui->pushButtonAvartar->setIcon(ui->tableWidgetContact->item(row,0)->icon());
    formchat->setWindowIcon(ui->tableWidgetContact->item(row,0)->icon());
    formchat->idc=ui->tableWidgetContact->item(row,2)->text().toInt();
    formchat->history();
}

void Form::profile()
{
    formProfile=new FormProfile;    
    formProfile->ui->labelID->setText(QString::number(id));

    QSqlQuery query;
    QString sql="select * from user where id=" + QString::number(id);
    bool b=query.exec(sql);
    qDebug() << sql << b;
    if(query.next()){
        name = query.value("name").toString();
        signature = query.value("signature").toString();
        phonenumber=query.value("phonenumber").toInt();
        homepage = query.value("homepage").toString();
        email = query.value("email").toString();
        domicile = query.value("domicile").toString();
        sex = query.value("sex").toString();
        regtime = query.value("regtime").toDateTime();
        birthday = query.value("birthday").toDate();
        urlAvantar=query.value("avantar").toString();

        formProfile->ui->labelName->setText(name);
        formProfile->ui->labelSignature->setText(signature);
        formProfile->ui->labelEmail->setText(email);
        formProfile->ui->labelDomicile->setText(domicile);
        formProfile->ui->labelHomepage->setText(homepage);
        formProfile->ui->labelPhoneNumber->setText(QString::number(phonenumber));
        formProfile->ui->labelSex->setText(sex);
        formProfile->ui->labelRegTime->setText(regtime.toString("yyyy-M-d H:m:s"));
        formProfile->ui->labelBirthday->setText(birthday.toString("yyyy-M-d"));
        formProfile->ui->labelAvantar->setPixmap(ui->pushButtonAvantar->icon().pixmap(60,60));
    }
    formProfile->show();
}

//void Form::replyPixmap(QNetworkReply* reply)
//{
//    qDebug() << "reply" << reply->error();
//    QPixmap pixmap;
//    pixmap.loadFromData(reply->readAll());
//    ui->pushButtonAvantar->setIcon(QIcon(pixmap.scaled(60,60)));
//}

void Form::TWContextMenu(const QPoint &position)
{
    QList<QAction *> actions;
    QAction *action_delete=new QAction(this);
    action_delete->setText("删除");
    actions.append(action_delete);
    QAction *result_action = QMenu::exec(actions,ui->tableWidgetContact->mapToGlobal(position));
    if(result_action == action_delete){
        QMessageBox MB(QMessageBox::NoIcon, "删除好友", "删除 " + ui->tableWidgetContact->item(ui->tableWidgetContact->currentRow(),1)->text() + "(" + ui->tableWidgetContact->item(ui->tableWidgetContact->currentRow(),2)->text()+") 后你将从对方联系人列表中消失，且以后不再接收此人的会话消息。", QMessageBox::Yes | QMessageBox::No, NULL);
        MB.setIconPixmap(ui->tableWidgetContact->item(ui->tableWidgetContact->currentRow(),0)->icon().pixmap(60,60,QIcon::Normal,QIcon::On));
        if(MB.exec() == QMessageBox::Yes)
        {
            qDebug() << "delete" << ui->tableWidgetContact->item(ui->tableWidgetContact->currentRow(),2)->text();
            QSqlQuery query;
            QString sql = "delete from c" + QString::number(id) + " where id=" + ui->tableWidgetContact->item(ui->tableWidgetContact->currentRow(),2)->text();
            bool b=query.exec(sql);
            qDebug() << sql << b;
            sql = "delete from c" + ui->tableWidgetContact->item(ui->tableWidgetContact->currentRow(),2)->text() + " where id=" + QString::number(id);
            b=query.exec(sql);
            qDebug() << sql << b;
            ui->tableWidgetContact->removeRow(ui->tableWidgetContact->currentRow());
        }
        return;
    }
}
