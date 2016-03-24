#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "networking.h"

/*---------------------------------------------------------------------------------------
--  SOURCE FILE:    mainwindow.cpp
--
--  PROGRAM:        Linux Chat application
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
--      void MainWindow::on_disconnectButton_clicked()
--      void MainWindow::on_exportFileButton_clicked()
--      void MainWindow::closeEvent(QCloseEvent *event)
--      void MainWindow::goOffline();
--
--
--  DATE:           March 23, 2016
--
--  REVISIONS:      March 23 - add disconnect functionality (Krystle)
--                  March 23 - add connection validation (Krystle)
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
    connected = false;
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
    if (!worker->m_running || msgText == "") {
        return;
    }

    QScrollBar *sb = ui->textWindow->verticalScrollBar();

    QTime time(QTime::currentTime());

    // time format
    QString timeFormatString = "[" + time.toString() + "]";
    QString div = "<div>";

    // inserts html code formatting
    ui->textWindow->insertHtml(div + "<span style = \"color: #9AA8D6;\">" + userText + "</span>" + " - " +
                               timeFormatString + "<br>" + "<span style = \"color: #D8D8D8;\">" + msgText
                               + "</span>" + "</div>" + "<br>");

    // always scroll to bottom after sending
    sb->setValue(sb->maximum());
}

void MainWindow::updateUserList(QString username) {
    ui->listWidget->clear();

    if (!worker->m_running) {
        return;
    }

    std::string userListNotParsed = username.toStdString();

    std::stringstream ss(userListNotParsed);
    std::string token;
    while(std::getline(ss, token, '<')){
        QString tokenString = QString::fromUtf8(token.c_str());
        qDebug() << tokenString;
        ui->listWidget->addItem(tokenString);
    }
}

void MainWindow::sendFinished()
{
    sending = false;
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
    QMessageBox messageBox;

    if (!connected) {
        messageBox.critical(0,"Error","Cannot send, not connected.");
        messageBox.setFixedSize(500,200);
        return;
    }

    QString msgText = ui->sendMessageContent->text();
    QString usernameText = ui->usernameField->text();

    QScrollBar *sb = ui->textWindow->verticalScrollBar();
    QTime time(QTime::currentTime());

    // time format
    QString timeFormatString = "[" + time.toString() + "]";
    QString div = "<div>";

    // inserts html code formatting
    ui->textWindow->insertHtml(div + "<span style = \"color: #00A3BC; font: bold;\">"
                               + usernameText + "</span>" + " - " + timeFormatString + "<br>" + "<span style = \"color: #D8D8D8;\">" + msgText
                               + "</span>" + "</div>" + "<br>");


    // clear text after you send
    ui->sendMessageContent->clear();

    // always scroll to bottom after sending
    sb->setValue(sb->maximum());

    // focus user back to text field
    ui->sendMessageContent->setFocus();

    // convert qstring message into char * message for sending
    std::string msg (msgText.toStdString());
    msg.append("|");
    msg.append(usernameText.toStdString());
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
-- REVISIONS: March 23 - error checking (Krystle)
--
-- DESIGNER: Oscar Kwan
--
-- PROGRAMMER: Oscar Kwan, Krystle Bulalaakaw
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

    if (initConnection(port, hostIP) < 0) {
        return;
    }

    // send username
    std::thread sendThread(sendDataToServer, std::ref(msgToSend));
    sendThread.join();

    // QThread for receiving
    workerThread = new QThread;
    worker       = new ReceiveWorker;
    worker->moveToThread(workerThread);
    connect(worker, SIGNAL(updateChatWindowSignal(QString, QString)), this, SLOT(updateTextWindow(QString, QString)));
    connect(worker, SIGNAL(updateUserListSignal(QString)), this, SLOT(updateUserList(QString)));
    connect(workerThread, SIGNAL(started()), worker, SLOT(doWork()));
    connect(worker, SIGNAL(finished()), workerThread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));

    workerThread->start();

    // switch to chat tab
    ui->tabWidget->setCurrentIndex(0);

    // add local name to user list
    ui->listWidget->addItem(username);
    ui->connectionLabel->setStyleSheet("QLabel { color: green; }");
    ui->connectionLabel->setText("Online");

    connected = true;
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

/*---------------------------------------------------------------------------------------------------------------------
-- FUNCTION: on_disconnectButton_clicked
--
-- DATE: March 23, 2016
--
-- REVISIONS: None
--
-- DESIGNER: Krystle Bulalakaw
--
-- PROGRAMMER: Krystle Bulalakaw
--
-- INTERFACE:
--
--          void ()
--
-- RETURNS: void
--
-- NOTES:
-- This function is executed when the disconnect button is clicked. It stops the receive worker thread, closes the
-- socket, clears the connected clients list, and sets status to offline.
---------------------------------------------------------------------------------------------------------------------*/
void MainWindow::on_disconnectButton_clicked()
{
    goOffline();
}

/*---------------------------------------------------------------------------------------------------------------------
-- FUNCTION: closeEvent
--
-- DATE: March 23, 2016
--
-- REVISIONS: None
--
-- DESIGNER: Krystle Bulalakaw
--
-- PROGRAMMER: Krystle Bulalakaw
--
-- INTERFACE:
--
--          closeEvent(QCloseEvent *event)
--
-- RETURNS: void
--
-- NOTES:
-- Handles the even for when the main window is closed. It stops the receive worker thread, closes the
-- socket and clears the connected clients list.
---------------------------------------------------------------------------------------------------------------------*/
void MainWindow::closeEvent(QCloseEvent *event)
{
    goOffline();
}


/*---------------------------------------------------------------------------------------------------------------------
-- FUNCTION: goOffline
--
-- DATE: March 23, 2016
--
-- REVISIONS: None
--
-- DESIGNER: Krystle Bulalakaw
--
-- PROGRAMMER: Krystle Bulalakaw
--
-- INTERFACE:
--
--          void ()
--
-- RETURNS: void
--
-- NOTES:
-- Stops the receive worker thread, closes the socket, clears the connected clients list, and sets offline status.
---------------------------------------------------------------------------------------------------------------------*/
void MainWindow::goOffline() {
    sendDataToServer("closesd");
    worker->m_running = true;
    endConnection();
    ui->listWidget->clear();
    ui->connectionLabel->setStyleSheet("QLabel { color: red; }");
    ui->connectionLabel->setText("Offline");
}
