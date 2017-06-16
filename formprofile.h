#ifndef FORMPROFILE_H
#define FORMPROFILE_H

#include <QWidget>

namespace Ui {
class FormProfile;
}

class FormProfile : public QWidget
{
    Q_OBJECT

public:
    explicit FormProfile(QWidget *parent = 0);
    ~FormProfile();
    Ui::FormProfile *ui;


private slots:    
    void edit();
};

#endif // FORMPROFILE_H
