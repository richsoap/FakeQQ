#include "mainwindow.h"
#include "netcommunicate.h"
#include "ui_mainwindow.h"
#include <QListView>
#include <QObject>


MainWindow::MainWindow(QWidget *parent, NetCommunicate* _net) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    communictor(_net) {
    ui->setupUi(this);
    model = new QStandardItemModel(this);
    QObject::connect(ui->FriendList,&QListView::doubleClicked,this,&MainWindow::startChatWindow);
    ui->FriendList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->FriendList->setModel(model);
    QObject::connect(communictor, &NetCommunicate::onReceiveChangeFriend,this,&MainWindow::changeFriendState);
    QObject::connect(communictor,&NetCommunicate::onReceiveNewFriend,this,&MainWindow::addFriendID);
    //QObject::connect(communictor,&NetCommunicate::onReceiveMessage,this,&MainWindo);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
}

void MainWindow::show(QString _ID) {
    ui->ID->setText(_ID);
    ID = _ID;
    QMainWindow::show();
    initDatabase();
    ////
    QStandardItem* item = new QStandardItem("test1");
    item->setBackground(getBackground(online));
    model->appendRow(item);
    friendList.append("test1");
    item = new QStandardItem("test2");
    item->setBackground(getBackground(offline));
    model->appendRow(item);
    friendList.append("test2");//fake friend list
}
void MainWindow::addFriendID(QString UserID, int state) {
    QStandardItem* item = new QStandardItem(UserID);
    item->setBackground(getBackground((onlineState)state));
    model->appendRow(item);
    friendList.append(UserID);
}
void MainWindow::changeFriendState(QString UserID, int state) {
    QStandardItem* item = new QStandardItem(UserID);
    int i;
    item->setBackground(getBackground((onlineState)state));
    for(i = 0;i < friendList.length();i ++) {
        if(UserID == friendList.at(i))
            break;
    }
    model->setItem(i,0,item);
}

QLinearGradient MainWindow::getBackground(onlineState state) {
    QLinearGradient background(QPointF(0,0),QPointF(200,200));
    if(state == offline) {
        background.setColorAt(0, Qt::darkGray);
        background.setColorAt(1, Qt::gray);
    }
    else {
        background.setColorAt(0, Qt::white);
        background.setColorAt(1, Qt::white);
    }
    return background;
}

void MainWindow::startChatWindow() {
    int index;
    index = ui->FriendList->currentIndex().row();
    chatWindow = new ChatWindow(this, ID, friendList.at(index));
    chatWindow->show();
    connect(chatWindow,&ChatWindow::sendMessage,this,&MainWindow::saveSendMessage);
}
void MainWindow::saveSendMessage(QString friendID, QString Message, int time) {
    QSqlQuery sql_query;
    QString insert_sql = "insert into " + friendID + " values (?,?)";
    //sql_que
}
void MainWindow::initDatabase() {
    if(QSqlDatabase::contains("qt_sql_default_connection")) {
        database = (QSqlDatabase::database("qt_sql_default_connection"));
    }
    else {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName(ID + ".db");
        database.setUserName(ID);
        database.setPassword(ID);
    }
}
