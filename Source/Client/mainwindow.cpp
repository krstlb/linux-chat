#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "networking.h"
#include "receiveworker.h"

/*---------------------------------------------------------------------------------------
--  SOURCE FILE:    mainwindow.cpp
--
--  PROGRAM:        Linux Game
--
--  FUNCTIONS:
--
--      MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), sending(false)
--      MainWindow::~MainWindow()
--      void MainWindow::updateTextWindow(QString msgText, QString userText)
--      void MainWindow::sendFinished()
--      void MainWindow::disconnectClicked()
--      void MainWindow::on_sendDataButton_clicked()
--      void MainWindow::on_pushButton_clicked()
--      void MainWindow::on_exportFileButton_clicked()
--
--
--  DATE:           March 23, 2016
--
--  REVISIONS:      (Date and Description)
--
--  DESIGNERS:      Oscar Kwan, Krystle Bulalakaw
--
--  PROGRAMMER:     Oscar Kwan, Krystle Bulalakaw
--
--  NOTES:
--  This class contains the logic behind the main window gui elements. It contains the functions
--  needed when different elements are interacted with by the user. These functios including
--  hitting the send and connect button, or exporting a log file.
---------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------------------
-- FUNCTION: MainWindow
--
-- DATE: March 23, 2016
--
-- REVISIONS: None
--
-- DESIGNER: Oscar Kwan
--
-- PROGRAMMER: Oscar Kwan
--
-- RETURNS: constructor
--
-- NOTES:
-- Constructor that initializes the ui, and does any connect signals needed.
---------------------------------------------------------------------------------------------------------------------*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sending(false)
{
    ui->setupUi(this);
    connect(ui->sendMessageContent, SIGNAL(returnPressed()), ui->sendDataButton, SIGNAL(clicked()));
    ui->sendMessageContent->setClearButtonEnabled(true);
}

/*---------------------------------------------------------------------------------------------------------------------
-- FUNCTION: ~MainWindow
--
-- DATE: March 23, 2016
--
-- REVISIONS: None
--
-- DESIGNER: Oscar Kwan
--
-- PROGRAMMER: Oscar Kwan
--
-- RETURNS: destructor
--
-- NOTES:
-- destructor.
---------------------------------------------------------------------------------------------------------------------*/
MainWindow::~MainWindow()
{
    delete ui;
}

/*---------------------------------------------------------------------------------------------------------------------
-- FUNCTION: updateTextWindow
--
-- DATE: March 23, 2016
--
-- REVISIONS: None
--
-- DESIGNER: Oscar Kwan
--
-- PROGRAMMER: Oscar Kwan
--
-- INTERFACE:
--
--          void (QString msgText, QString userText)
--              QString msgText
--                  - message received from clients
--              QString userText
--                  - username
--
-- RETURNS: void
--
-- NOTES:
-- This function updates the gui whenever a message is received from other clients.
-- It also formats it into a nicely displayed html string with colours.
---------------------------------------------------------------------------------------------------------------------*/
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


/*---------------------------------------------------------------------------------------------------------------------
-- FUNCTION: on_sendDataButton_clicked
--
-- DATE: March 23, 2016
--
-- REVISIONS: None
--
-- DESIGNER: Oscar Kwan
--
-- PROGRAMMER: Oscar Kwan
--
-- INTERFACE:
--
--          void ()
--
-- RETURNS: void
--
-- NOTES:
-- This function updates the text window on local changes. So it echos your own text with different styling from
-- messages received from other clients. It also sends the message to the server so it can send it to other clients.
---------------------------------------------------------------------------------------------------------------------*/
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

/*---------------------------------------------------------------------------------------------------------------------
-- FUNCTION: on_pushButton_clicked
--
-- DATE: March 23, 2016
--
-- REVISIONS: None
--
-- DESIGNER: Oscar Kwan
--
-- PROGRAMMER: Oscar Kwan
--
-- INTERFACE:
--
--          void ()
--
-- RETURNS: void
--
-- NOTES:
-- This function is executed when the connect button is pressed. It takes in the user input's username, ip and port and
-- uses it to connect with the server. After a successful connect, it creates a QThread that begins infinetely waiting
-- for any messages to be received. Before it does this, it sends it's username to the server.
---------------------------------------------------------------------------------------------------------------------*/
void MainWindow::on_pushButton_clicked()
{
    int port;
    std::string host;
    char* hostIP;

    QThread             *workerThread;
    ReceiveWorker       *worker;

    QString tempUser;
    QString username = ui->usernameField->text();

    tempUser = username;
    tempUser.append("thisisausernameguud");

    // convert qstring message into char * message for sending
    std::string msg = tempUser.toStdString();
    char* msgToSend = new char [msg.size()+1];
    strcpy(msgToSend, msg.c_str());

    port = ui->portField->text().toInt();

    host = ui->ipField->text().toStdString();

    hostIP = new char [host.size()+1];
    strcpy(hostIP, host.c_str());

    qDebug() << msgToSend << " " << port << " " << hostIP;

    initConnection(port, hostIP);

    // send username
    std::thread sendThread(sendDataToServer, std::ref(msgToSend));
    sendThread.join();

    // QThread for receiving
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

    // switch to chat tab
    ui->tabWidget->setCurrentIndex(0);

    // add local name to user list
    ui->listWidget->addItem(username);
    ui->connectionLabel->setStyleSheet("QLabel { color: green; }");
    ui->connectionLabel->setText("Online");
}

/*---------------------------------------------------------------------------------------------------------------------
-- FUNCTION: on_exportFileButton_clicked
--
-- DATE: March 23, 2016
--
-- REVISIONS: None
--
-- DESIGNER: Oscar Kwan
--
-- PROGRAMMER: Oscar Kwan
--
-- INTERFACE:
--
--          void ()
--
-- RETURNS: void
--
-- NOTES:
-- This function is executed when the export button is clicked. It creates a file and takes in the textbrowsers text
-- and outputs it to a log file.
---------------------------------------------------------------------------------------------------------------------*/
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
