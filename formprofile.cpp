#include "formprofile.h"
#include "ui_formprofile.h"
#include "editprofile.h"
#include "ui_editprofile.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QDesktopWidget>

FormProfile::FormProfile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormProfile)
{
    ui->setupUi(this);
    ui->labelAvantarUrl->setVisible(false);
    move((QApplication::desktop()->width() - width())/2, (QApplication::desktop()->height() - height())/2);
    setWindowFlags((windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);
    setFixedSize(380,450);
    connect(ui->pushButtonEdit,SIGNAL(pressed()),this,SLOT(edit()));
}

FormProfile::~FormProfile()
{
    delete ui;
}

void FormProfile::edit()
{
    EditProfile *editprofile=new EditProfile;    
    editprofile->id=ui->labelID->text().toInt();    
    editprofile->ui->labelAvantar->setPixmap(*ui->labelAvantar->pixmap());
    editprofile->setWindowIcon(QIcon(*ui->labelAvantar->pixmap()));
    editprofile->ui->lineEditAvantar->setText(ui->labelAvantarUrl->text());
    editprofile->ui->lineEditAvantar->setCursorPosition(0);
    editprofile->ui->lineEditName->setText(ui->labelName->text());
    editprofile->ui->lineEditDomicile->setText(ui->labelDomicile->text());
    editprofile->ui->comboBoxSex->setCurrentText(ui->labelSex->text());
    editprofile->ui->lineEditEmail->setText(ui->labelEmail->text());
    editprofile->ui->lineEditHomepage->setText(ui->labelHomepage->text());
    editprofile->ui->lineEditHomepage->setCursorPosition(0);
    editprofile->ui->lineEditPhoneNumber->setText(ui->labelPhoneNumber->text());
    editprofile->ui->dateEditBirthday->setDate(QDate::fromString(ui->labelBirthday->text(), "yyyy-M-d"));
    editprofile->ui->textEditSignature->setText(ui->labelSignature->text());
    editprofile->show();
}
