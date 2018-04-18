#include "mainwindow.h"
#include "netcommunicate.h"
#include "chatwindow.h"
#include <QApplication>
#include "login.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NetCommunicate* communicator = new NetCommunicate();
    MainWindow w(0,communicator);
    Login login(0,communicator);
    //login.show();
    w.show("TestUser");
    //QObject::connect(&login,&Login::signinSuccessfully,&w,&MainWindow::show);
    return a.exec();
}
