#ifndef FORMCHAT_H
#define FORMCHAT_H

#include <QWidget>
#include <QDate>
#include <QDateTime>

namespace Ui {
class FormChat;
}

class FormChat : public QWidget
{
    Q_OBJECT

public:
    explicit FormChat(QWidget *parent = 0);
    ~FormChat();
    Ui::FormChat *ui;
    QString pathCache,name,homepage,email,domicile,sex,signature,namec,homepagec,emailc,domicilec,sexc,signaturec,birthdayc,regtimec;
    int id,idc;
    QDate birthday;
    QDateTime regtime;

private:
    QString filename;

private slots:
    void send();
    void openURL();    
    void on_pushButtonImg_clicked();
    void profile();

public slots:
    void history();
};

#endif // FORMCHAT_H
