#ifndef FORMREG_H
#define FORMREG_H

#include <QWidget>
#include <QNetworkReply>

namespace Ui {
class FormReg;
}

class FormReg : public QWidget
{
    Q_OBJECT

public:
    explicit FormReg(QWidget *parent = 0);
    ~FormReg();

private:
    Ui::FormReg *ui;
    void genID();

private slots:
    void displayPassword(bool checked);
    void registerAccount();
    void getAvantar();
    void replyPixmap(QNetworkReply*);
    void genVerificationCode();

};

#endif // FORMREG_H