#include <QThread>
#include "dialog.h"
#include "networking.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include "receiveworker.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    connected(false)
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

    std::thread sendThread(sendDataToServer, std::ref(msgToSend));
    sendThread.join();

    // close dialog

    QThread             *workerThread;
    ReceiveWorker       *worker;

    if (connected) {
        qDebug() << "Already connected!";
        return;
    }

    workerThread = new QThread;
    worker       = new ReceiveWorker;
    worker->moveToThread(workerThread);
    connect(workerThread, SIGNAL(started()), worker, SLOT(doWork()));
    connect(worker, SIGNAL(finished()), workerThread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
    connect(worker, SIGNAL(finished()), this, SLOT(disconnectClicked()));
    //connect(ui->actionDisconnect, SIGNAL(clicked()), worker, SLOT(stopWork()));
    workerThread->start();

    connected = true;

    close();
}
