#ifndef FORMFIND_H
#define FORMFIND_H
#include "itemfind.h"
#include "ui_itemfind.h"
#include <QWidget>

namespace Ui {
class FormFind;
}

class FormFind : public QWidget
{
    Q_OBJECT

public:
    explicit FormFind(QWidget *parent = 0);
    ~FormFind();
    int id;

private:
    Ui::FormFind *ui;    

private slots:
    void search();
};

#endif // FORMFIND_H
