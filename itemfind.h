#ifndef ITEMFIND_H
#define ITEMFIND_H

#include <QWidget>
#include <QNetworkReply>

namespace Ui {
class ItemFind;
}

class ItemFind : public QWidget
{
    Q_OBJECT

public:
    explicit ItemFind(QWidget *parent = 0);
    ~ItemFind();
    Ui::ItemFind *ui;
    int id;
    void getPixmap(QString url);

private slots:
    void addAccount();
    void replyPixmap(QNetworkReply* reply);
};

#endif // ITEMFIND_H
