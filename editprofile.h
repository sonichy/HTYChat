#ifndef EDITPROFILE_H
#define EDITPROFILE_H

#include <QWidget>
#include <QNetworkReply>

namespace Ui {
class EditProfile;
}

class EditProfile : public QWidget
{
    Q_OBJECT

public:
    explicit EditProfile(QWidget *parent = 0);
    ~EditProfile();
    Ui::EditProfile *ui;
    int id;

private slots:
    void save();
    void getAvantar();
    void replyPixmap(QNetworkReply*);
};

#endif // EDITPROFILE_H
