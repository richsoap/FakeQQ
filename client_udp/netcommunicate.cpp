#include "netcommunicate.h"
#include <QObject>

NetCommunicate::NetCommunicate(QObject* parent): QObject(parent) {
    mSocket = new QUdpSocket();
    mSocket->bind(mSocket->localAddress(), mSocket->localPort(), QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(mSocket,&QUdpSocket::readyRead,this,&NetCommunicate::receiveData);
    IP = QHostAddress();
    port = (qint16)0;
}
NetCommunicate::~NetCommunicate() {}
void NetCommunicate::setIP(QString _IP) {
    IP = QHostAddress(_IP);
}
void NetCommunicate::setPort(int _port) {
    port = (qint16)_port;
}
void NetCommunicate::receiveData() {
    QByteArray array;
    QHostAddress address;
    quint16 port;
    array.resize(mSocket->bytesAvailable());
    mSocket->readDatagram(array.data(),array.size(),&address,&port);
    QJsonObject jsonObject = QJsonDocument::fromBinaryData(array).array().at(0).toObject();
    switch(jsonObject.value("command").toInt()) {
        case ReceiveVerify:
            onReceiveVerify(jsonObject.value("result").toInt());
            break;
        case ReceiveMessage:
            onReceiveMessage(jsonObject.value("friendid").toString(), jsonObject.value("message").toString(), jsonObject.value("timemark").toInt());
            break;
        case ReceiveNewFriend:
            onReceiveNewFriend(jsonObject.value("friendid").toString(), jsonObject.value("state").toInt());
            break;
        case ReceiveChangeFriend:
            onReceiveChangeFriend(jsonObject.value("friendid").toString(), jsonObject.value("state").toInt());
    }
}
void NetCommunicate::sendVerifyData(QString userID, QString password) {
    QJsonObject jsonObject;
    jsonObject.insert("command",SendVerify);
    jsonObject.insert("userid",userID);
    jsonObject.insert("passwrod",password);
    mSocket->writeDatagram(QJsonDocument(jsonObject).toBinaryData(),IP, port);
}
void NetCommunicate::sendMessageData(QString userID, QString friendID, QString Message, int timemask) {
    QJsonObject jsonObject;
    jsonObject.insert("command", SendMessage);
    jsonObject.insert("userid", userID);
    jsonObject.insert("friendid", friendID);
    jsonObject.insert("message",Message);
    jsonObject.insert("timemask", timemask);
    mSocket->writeDatagram(QJsonDocument(jsonObject).toBinaryData(), IP, port);
}
