#include <QThread>
#include "mainwindow.h"
#include "dialog.h"
#include "ui_mainwindow.h"
#include "networking.h"
#include "sendworker.h"
#include "receiveworker.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sending(false)
{
    ui->setupUi(this);
    connect(ui->sendDataButton, SIGNAL (clicked()),this, SLOT (OnSendClicked()));
    connect(ui->actionConnect, SIGNAL (triggered()),this, SLOT (onConnectClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTextWindow(QString msgText)
{
    QScrollBar *sb = ui->textWindow->verticalScrollBar();
    QTime time(QTime::currentTime());

    // time format
    QString timeFormatString = "[" + time.toString() + "]";
    QString divFormat = "<div style = \"border: 5px solid white;color: white;\">";

    // insert locally
    ui->textWindow->insertHtml(divFormat + timeFormatString + "<div style = \"background-color: rgba(0,0,0,0.5);\"></div>" +
                               msgText + "<div></div>" + "</div>");

    QString test = receiveDataFromServer();


    ui->textWindow->insertHtml("<div style = \"background-color: rgba(0,0,0,0.2);\"></div>" +
                                test + "<div></div>" + "</div>");

    // clear text after you send
    ui->sendMessageContent->clear();

    // always scroll to bottom after sending
    sb->setValue(sb->maximum());

    // focus user back to text field
    ui->sendMessageContent->setFocus();
}

void MainWindow::connectUser()
{
    Dialog *dialog = new Dialog(this);
    dialog->show();
}

// finite thread
void MainWindow::OnSendClicked()
{
    QThread      *workerThread;
    SendWorker   *worker;

    if (sending) {
        qDebug() << "Already sending!";
        return;
    }

    workerThread = new QThread;
    worker       = new SendWorker(ui->sendMessageContent->toPlainText());
    worker->moveToThread(workerThread);
    connect(workerThread, SIGNAL(started()), worker, SLOT(doWork()));
    connect(worker, SIGNAL(finished()), workerThread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(worker, SIGNAL(finished()), this, SLOT(sendFinished()));
    connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
    connect(worker, SIGNAL(updateTextWindow(QString)), this, SLOT(updateTextWindow(QString)));
    workerThread->start();

    sending = true;
}
// clear text after you send

// infinite thread
void MainWindow::onConnectClicked()
{
    QThread             *workerThread;
    ReceiveWorker       *worker;

    Dialog *dialog = new Dialog(this);
    dialog->show();
    /*
    workerThread = new QThread;
    worker       = new ReceiveWorker;
    worker->moveToThread(workerThread);
    connect(workerThread, SIGNAL(started()), worker, SLOT(doWork()));
    connect(worker, SIGNAL(finished()), workerThread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
    connect(worker, SIGNAL(finished()), this, SLOT(disconnectClicked()));
    connect(ui->actionDisconnect, SIGNAL(clicked()), worker, SLOT(stopWork()));
    workerThread->start();

    connected = true;
    */
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

