#include "editprofile.h"
#include "ui_editprofile.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QDesktopWidget>

EditProfile::EditProfile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditProfile)
{
    ui->setupUi(this);
    move((QApplication::desktop()->width() - width())/2, (QApplication::desktop()->height() - height())/2);
    setWindowFlags((windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);
    QStringList sexes;
    sexes << "男" << "女";
    ui->comboBoxSex->addItems(sexes);
    connect(ui->pushButtonSave,SIGNAL(pressed()),this,SLOT(save()));
    connect(ui->pushButtonClose,SIGNAL(pressed()),this,SLOT(close()));
    connect(ui->lineEditAvantar,SIGNAL(returnPressed()),this,SLOT(getAvantar()));
}

EditProfile::~EditProfile()
{
    delete ui;
}

void EditProfile::save()
{
    QSqlQuery query;
    QString sql = "update user set avantar='" + ui->lineEditAvantar->text() + "',name='" + ui->lineEditName->text() + "',sex='" + ui->comboBoxSex->currentText() + "',birthday='" + ui->dateEditBirthday->date().toString("yyyy/M/d") + "',domicile='" + ui->lineEditDomicile->text() + "',phonenumber=" + ui->lineEditPhoneNumber->text() + ",email='" + ui->lineEditEmail->text() + "',homepage='" + ui->lineEditHomepage->text() + "',signature='" + ui->textEditSignature->toPlainText() + "' where id=" + QString::number(id);
    bool b=query.exec(sql);
    qDebug() << sql << b;
    //ui->labelName->setText(ui->lineEditName->text());
    //ui->labelSignature->setText(ui->textEditSignature->toPlainText());
//    QFont font(ui->labelSignature->font());
//    QFontMetrics FM(font);
//    ui->labelSignature->setText(FM.elidedText(ui->textEditSignature->toPlainText(), Qt::ElideRight, ui->labelSignature->width()));
//    ui->labelSignature->setToolTip(ui->textEditSignature->toPlainText());
//    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
//    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyPixmap(QNetworkReply*)));
//    manager->get(QNetworkRequest(QUrl(ui->lineEditAvantar->text())));
    close();
}

void EditProfile::getAvantar()
{
    ui->lineEditAvantar->setCursorPosition(0);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyPixmap(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(ui->lineEditAvantar->text())));
}

void EditProfile::replyPixmap(QNetworkReply *reply)
{
    qDebug() << "reply" << reply->error();
    QPixmap pixmap;
    pixmap.loadFromData(reply->readAll());
    ui->labelAvantar->setPixmap(pixmap.scaled(60,60));
}
