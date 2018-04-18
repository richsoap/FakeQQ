#ifndef NETCOMMUNICATE_H
#define NETCOMMUNICATE_H
#include <QUdpSocket>
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
class NetCommunicate: public QObject {
    Q_OBJECT
public:
    NetCommunicate(QObject* parent = 0);
    ~NetCommunicate();
    void setIP(QString _IP);
    void setPort(int _port);
    void sendVerifyData(QString userID, QString password);
    void sendMessageData(QString userID, QString friendID, QString Message, int timemask);
    enum NETCOMMAND {
        SendVerify=0,
        ReceiveVerify=1,
        SendMessage=2,
        ReceiveMessage=3,
        ReceiveNewFriend=4,
        ReceiveChangeFriend=5
    };

private:
    QUdpSocket* mSocket;
    QHostAddress IP;
    qint16 port;
    void receiveData();
signals:
    void onReceiveVerify(int result);
    void onReceiveMessage(QString friendID, QString Message, int timemark);
    void onReceiveNewFriend(QString friendID, int state);
    void onReceiveChangeFriend(QString friendID, int state);

};

#endif // NETCOMMUNICATE_H
