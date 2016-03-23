#include "dialog.h"
#include "networking.h"
#include "ui_dialog.h"
#include "mainwindow.h"

Dialog::Dialog(QWidget *parent, MainWindow *mainWindow) :
    QDialog(parent),
    mainUi(mainWindow),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->okayDialogButton, SIGNAL (rejected()),this, SLOT (reject()));

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_okayDialogButton_accepted()
{
    int port;
    std::string host;
    char* hostIP;

    QString username = ui->usernameText->text();

    // convert qstring message into char * message for sending
    std::string msg = username.toStdString();
    char* msgToSend = new char [msg.size()+1];
    strcpy(msgToSend, msg.c_str());

    port = ui->portText->text().toInt();

    host = ui->ipText->text().toStdString();

    hostIP = new char [host.size()+1];
    strcpy(hostIP, host.c_str());

    qDebug() << msgToSend << " " << port << " " << hostIP;

    initConnection(port, hostIP);

    qt = new QThread();
    thread = new Thread();

    thread->moveToThread(qt);

    connect(thread, SIGNAL(recvBufferSignal(QString)), mainUi, SLOT (AddToChat(QString)));
    connect(qt, SIGNAL(started()), thread, SLOT (receiveData()));
    // close dialog
    close();
}
