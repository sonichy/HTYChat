#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.move((QApplication::desktop()->width() - w.width())/2, (QApplication::desktop()->height() - w.height())/2);
    w.setWindowFlags((w.windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);
    w.show();

    QString pathCache = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).first() + "/HTYChatFiles";
    w.pathCache = pathCache;
    QDir dir(pathCache);
    qDebug() << pathCache << dir.exists();
    if(!dir.exists()){
        dir.mkpath(pathCache);
    }

    return a.exec();
}
