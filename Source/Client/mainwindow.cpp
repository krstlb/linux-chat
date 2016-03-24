#include <QThread>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "networking.h"
#include "receiveworker.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sending(false)
{
    ui->setupUi(this);
    connect(ui->sendMessageContent, SIGNAL(returnPressed()), ui->sendDataButton, SIGNAL(clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTextWindow(QString msgText, QString userText)
{
    QScrollBar *sb = ui->textWindow->verticalScrollBar();

    QTime time(QTime::currentTime());

    // time format
    QString timeFormatString = "[" + time.toString() + "]";

    // inserts html code formatting
    ui->textWindow->insertHtml("<div>" + timeFormatString + "<span style = \"color: #A00691;\">" +
                               + "  " + userText + "</span>" + "<br>" + "<span style = \"color: #D8D8D8;\">" + msgText
                               + "</span>" + "</div>" + "<br>");

    // always scroll to bottom after sending
    sb->setValue(sb->maximum());
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
    QString usernameText = ui->usernameField->text();

    QScrollBar *sb = ui->textWindow->verticalScrollBar();
    QTime time(QTime::currentTime());

    // time format
    QString timeFormatString = "[" + time.toString() + "]";
    QString spanFormat = "<div>";

    // inserts html code formatting
    ui->textWindow->insertHtml(spanFormat + timeFormatString + "<span style = \"color: #00A3BC;\">" +
                               + "  " + usernameText + "</span>" + "<br>" + "<span style = \"color: white;\">" + msgText
                               + "</span>" + "</div>" + "<br>");

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

    username.append("thisisausernameguud");

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
    connect(worker, SIGNAL(updateChatWindowSignal(QString, QString)), this, SLOT(updateTextWindow(QString, QString)));
    connect(workerThread, SIGNAL(started()), worker, SLOT(doWork()));
    connect(worker, SIGNAL(finished()), workerThread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
    connect(worker, SIGNAL(finished()), this, SLOT(disconnectClicked()));
    //connect(ui->actionDisconnect, SIGNAL(clicked()), worker, SLOT(stopWork()));
    workerThread->start();

    connected = true;

    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::on_exportFileButton_clicked()
{
    QString log = ui->textWindow->toPlainText();
    QString filename="log.txt";
    QFile file( filename );
    if ( file.open(QIODevice::WriteOnly) )
    {
        QTextStream stream( &file );
        qDebug() << "Im creating a file";
        stream << log << endl;
    }

    file.close();
}
