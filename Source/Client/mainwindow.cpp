#include <QThread>
#include "mainwindow.h"
#include "dialog.h"
#include "ui_mainwindow.h"
#include "networking.h"
#include "receiveworker.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sending(false)
{
    ui->setupUi(this);
   // connect(ui->sendDataButton, SIGNAL (clicked()),this, SLOT (OnSendClicked()));
    connect(ui->actionConnect, SIGNAL (triggered()),this, SLOT (onConnectClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTextWindow(QString msgText)
{
    qDebug() << "Inside Update Text Window";

    QScrollBar *sb = ui->textWindow->verticalScrollBar();
    QTime time(QTime::currentTime());

    // time format
    QString timeFormatString = "[" + time.toString() + "]";
    QString divFormat = "<div style = \"border: 5px solid white;color: white;\">";

    // inserts html code formatting
    ui->textWindow->insertHtml(divFormat + timeFormatString + "<div style = \"background-color: rgba(0,0,0,0.5);\"></div>" +
                               msgText + "<div></div>" + "</div>");

    // clear text after you send
    ui->sendMessageContent->clear();

    // always scroll to bottom after sending
    sb->setValue(sb->maximum());

    // focus user back to text field
    ui->sendMessageContent->setFocus();
}

void MainWindow::sendFinished()
{
    sending = false;
}

void MainWindow::disconnectClicked()
{
    //connected = false;
}

void MainWindow::connectSignalSlots()
{
    connect(ui->sendDataButton, SIGNAL (clicked()),this, SLOT (sendClicked()));
    connect(ui->actionConnect, SIGNAL (triggered()),this, SLOT (connectClicked()));
}


void MainWindow::on_sendDataButton_clicked()
{

    QString msgText = ui->sendMessageContent->text();

    QScrollBar *sb = ui->textWindow->verticalScrollBar();
    QTime time(QTime::currentTime());

    // time format
    QString timeFormatString = "[" + time.toString() + "]";
    QString divFormat = "<div style = \"border: 5px solid white;color: white;\">";

    // inserts html code formatting
    ui->textWindow->insertHtml(divFormat + timeFormatString + "<div style = \"background-color: rgba(0,0,0,0.5);\"></div>" +
                               msgText + "<div></div>" + "</div>");

    // clear text after you send
    ui->sendMessageContent->clear();

    // always scroll to bottom after sending
    sb->setValue(sb->maximum());

    // focus user back to text field
    ui->sendMessageContent->setFocus();

    // convert qstring message into char * message for sending
    std::string msg (msgText.toStdString());
    char* message = new char [msg.size()+1];
    strcpy(message, msg.c_str());

    // Send message
    std::thread sendThread(sendDataToServer, std::ref(message));
    sendThread.join();

}

// when connect button click
void MainWindow::on_pushButton_clicked()
{
    int port;
    std::string host;
    char* hostIP;

    QString username = ui->usernameField->text();

    // convert qstring message into char * message for sending
    std::string msg = username.toStdString();
    char* msgToSend = new char [msg.size()+1];
    strcpy(msgToSend, msg.c_str());

    port = ui->portField->text().toInt();

    host = ui->ipField->text().toStdString();

    hostIP = new char [host.size()+1];
    strcpy(hostIP, host.c_str());

    qDebug() << msgToSend << " " << port << " " << hostIP;

    initConnection(port, hostIP);

    std::thread sendThread(sendDataToServer, std::ref(msgToSend));
    sendThread.join();

    QThread             *workerThread;
    ReceiveWorker       *worker;

    workerThread = new QThread;
    worker       = new ReceiveWorker;
    worker->moveToThread(workerThread);
    connect(worker, SIGNAL(updateChatWindowSignal(QString)), this, SLOT(updateTextWindow(QString)));
    connect(workerThread, SIGNAL(started()), worker, SLOT(doWork()));
    connect(worker, SIGNAL(finished()), workerThread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
    connect(worker, SIGNAL(finished()), this, SLOT(disconnectClicked()));
    //connect(ui->actionDisconnect, SIGNAL(clicked()), worker, SLOT(stopWork()));
    workerThread->start();

    connected = true;

}
