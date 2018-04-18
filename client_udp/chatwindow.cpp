#include "chatwindow.h"
#include "ui_chatwindow.h"
#include <QTextDocument>
#include <QStandardItem>
#include <QDate>
#include <QThread>

ChatWindow::ChatWindow(QWidget *parent, QString _userID, QString _friendID, NetCommunicate* _net) :
    QMainWindow(parent),
    ui(new Ui::ChatWindow),
    userID(_userID),
    friendID(_friendID),
    communictor(_net) {
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    QObject::connect(ui->sendbutton,&QPushButton::clicked,this,&ChatWindow::onButtonCliked);
    model = new QStandardItemModel(this);
    ui->DisplayList->setModel(model);
    QObject::connect(communictor,&NetCommunicate::onReceiveMessage,this,&ChatWindow::receiveMessage);
}

ChatWindow::~ChatWindow() {
    delete ui;
}

void ChatWindow::initMessages() {
    //read data from database
}
void ChatWindow::onButtonCliked() {
    QDateTime time = QDateTime::currentDateTime();
    QTextDocument* document;
    document = ui->EditArea->document();
    QString message = document->toRawText();
    document->clear();
    QStandardItem* item = new QStandardItem(time.toString() + "\n" + message);
    item->setBackground(getBackground(send));
    model->appendRow(item);
    sendMessage(friendID, message, time.toTime_t());
}
void receiveMessage(QString friendID, QString message, int timet);
QLinearGradient ChatWindow::getBackground(direction dir) {
    QLinearGradient background(QPointF(0,0),QPointF(200,200));
    if(dir == send) {
        background.setColorAt(0, Qt::darkGray);
        background.setColorAt(1, Qt::gray);
    }
    else {
        background.setColorAt(0, Qt::white);
        background.setColorAt(1, Qt::white);
    }
    return background;
}
