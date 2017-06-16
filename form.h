#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QModelIndex>
#include <QDateTime>
#include <QDate>
#include <QNetworkReply>
#include <QListWidgetItem>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    int id,phonenumber;
    QString name,urlAvantar,sex,homepage,email,domicile,signature,pathCache;
    QDateTime regtime;
    QDate birthday;
    Ui::Form *ui;

private:

private slots:
    void on_pushButtonHomepage_clicked();
    void on_pushButtonMenu_clicked();
    void on_pushButtonAdd_clicked();
    void showMenu(const QPoint &point);
    void logout();
    void about();
    void lock();
    void chat(int row, int column);
    void profile();
    void replyPixmap(QNetworkReply*);
    void replyPixmapProfile(QNetworkReply*);
    void TWContextMenu(const QPoint &position);
};

#endif // FORM_H
