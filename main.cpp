#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("JunSun");
     QCoreApplication::setOrganizationDomain("jprogram@bk.ru");
     QCoreApplication::setApplicationName("Safe zone");
   QApplication::applicationVersion() = "1.0.0";
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Safe zone");
    w.setFixedSize(921, 628);
    w.show();
    return a.exec();
}
