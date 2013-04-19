#include <QtGui/QApplication>
#include <QtDBus/QtDBus>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusConnectionInterface>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    QDBusConnection connection = QDBusConnection::sessionBus();
//    bool ret=connection.registerService("chaudhary");
//    ret=connection.registerObject("/");
    return a.exec();
}
