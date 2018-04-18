#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "chatwindow.h"
#include "netcommunicate.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum onlineState{
        online = 0,
        offline = 1
    };
    explicit MainWindow(QWidget *parent = 0, NetCommunicate* _communicator = 0);
    ~MainWindow();
    virtual void show(QString _ID);

private:
    Ui::MainWindow *ui;
    QString ID;
    QStringList friendList;
    QStandardItemModel *model;
    QSqlDatabase database;
    ChatWindow* chatWindow;
    NetCommunicate* communictor;
    void addFriendID(QString UserID, int state);
    void changeFriendState(QString UserID, int state);
    QLinearGradient getBackground(onlineState state);
    void startChatWindow();
    void initDatabase();
    void saveSendMessage(QString friendID, QString Message, int time);
};

#endif // MAINWINDOW_H
