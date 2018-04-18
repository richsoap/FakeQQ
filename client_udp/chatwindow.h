#ifndef CHATWINDOW_H
#define CHATWINDOW_H
#include <QUdpSocket>
#include <QMainWindow>
#include <QStandardItemModel>
#include "netcommunicate.h"

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = 0, QString userID = "Empty", QString friendID = "Void", NetCommunicate* _communictor = 0);
    ~ChatWindow();
    enum direction {
        send,
        receive
    };

private:
    QString userID;
    QString friendID;
    Ui::ChatWindow *ui;
    QStandardItemModel *model;
    NetCommunicate* communictor;
    void initMessages();
    void onButtonCliked();
    void receiveMessage(QString friendID, QString message, int timet);
    QLinearGradient getBackground(direction dir);
signals:
    void sendMessage(QString friendID, QString message, int timeT);
};

#endif // CHATWINDOW_H
