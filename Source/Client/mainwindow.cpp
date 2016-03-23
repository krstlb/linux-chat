#include "mainwindow.h"
#include "dialog.h"
#include "ui_mainwindow.h"
#include "networking.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->sendDataButton, SIGNAL (clicked()),this, SLOT (OnSendClicked()));
    connect(ui->actionConnect, SIGNAL (triggered()),this, SLOT (onConnectClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnSendClicked()
{
    QScrollBar *sb = ui->textWindow->verticalScrollBar();
    QString msgText = ui->sendMessageContent->toPlainText();
    QTime time(QTime::currentTime());

    // convert qstring message into char * message for sending
    std::string msg (msgText.toStdString());
    char* message = new char [msg.size()+1];
    strcpy(message, msg.c_str());

    // Send message
    std::thread sendThread(sendDataToServer, std::ref(message));
    sendThread.join();

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
// clear text after you send

void MainWindow::onConnectClicked()
{

   Dialog *dialog = new Dialog(this);
   dialog->show();

}

