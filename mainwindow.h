#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "form.h"
#include "ui_form.h"
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString pathCache;
    int id;

private:
    Ui::MainWindow *ui;
    Form *form;
    int i;

private slots:
    void on_pushButtonLogin_clicked();
    void changeAvatar(QString);
    void replyPixmapAccount(QNetworkReply*);
    //void replyPixmapContact(QNetworkReply*);
    void formRegister();

protected:
    //void paintEvent(QPaintEvent *event);

};

#endif // MAINWINDOW_H