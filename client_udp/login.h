#ifndef LOGIN_H
#define LOGIN_H
#include <QUdpSocket>
#include <QObject>
#include <QMainWindow>
#include "netcommunicate.h"
namespace Ui {
class Login;
}

class Login : public QMainWindow {
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0, NetCommunicate *_communicat = 0);
    ~Login();
    enum errorType{
        noError,
        idError,
        passwordError,
        ipError
    };

private:
    Ui::Login *ui;
    QString ID;
    QString password;
    QString IP;
    NetCommunicate* communictor;
    int port;
    void verifyID();
    void getVerifyResult(int result);
    errorType processInput();
    virtual void accept();

signals:
    void sendVerifyID(QString id, QString password);
    void signinSuccessfully(QString id);
};

#endif // LOGIN_H
