#include "ui_login.h"
#include "login.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

Login::Login(QWidget *parent, NetCommunicate* _net) :
    QMainWindow(parent),
    ui(new Ui::Login),
    communictor(_net){
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    QObject::connect(communictor,&NetCommunicate::onReceiveVerify,this,&Login::getVerifyResult);
}

Login::~Login() {
    delete ui;
}
void Login::verifyID() {
    switch (processInput()) {
    case noError:
        sendVerifyID(ID,password);
        break;
    case ipError:
        ui->state->setText("Invalid IP");
        break;
    case idError:
        ui->state->setText("Invalid ID");
        break;
    case passwordError:
        ui->state->setText("Invalid password");
        break;
    }
}

Login::errorType Login::processInput() {
    ID = ui->ID->text().toUtf8();
    if(ID.length() == 0)
        return idError;
    password = ui->ID->text().toUtf8();
    if(password.length() == 0)
        return passwordError;
    QString tempIP = ui->ID->text().toUtf8();
    QStringList ip_port = tempIP.split(":");
    if(ip_port.length() != 2)
        return ipError;
    port = ip_port.at(1).toInt();
    IP = ip_port.at(0);
    QStringList ip_list = ip_port.at(0).split(".");
    if(ip_list.length() != 4)
        return ipError;
    return noError;
}

void Login::getVerifyResult(int result) {
    if(result == 1) {
        signinSuccessfully(ID);
        this->close();
    }
    else {
        ui->state->setText("Not exist");
    }
}

void Login::accept() {
    verifyID();
}
