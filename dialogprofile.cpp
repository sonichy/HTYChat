#include "dialogprofile.h"
#include "ui_dialogprofile.h"

DialogProfile::DialogProfile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogProfile)
{
    ui->setupUi(this);
}

DialogProfile::~DialogProfile()
{
    delete ui;
}
