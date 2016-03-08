#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->sendDataButton, SIGNAL (clicked()),this, SLOT (OnSendClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnSendClicked()
{
    QString msgText = ui->sendMessageContent->toPlainText();
    QTime time(QTime::currentTime());

    // std::string msg (text.toStdString());

    // send message to server
    // sendDataToServer(msg.c_str());

    // time format
    QString timeFormatString = "[" + time.toString() + "]";

    // inserts html code formatting
    ui->textWindow->insertHtml("<div>" + timeFormatString + " " + msgText + "</div>");

    // inserts new line
    ui->textWindow->append("");

    // clear text after you send
    ui->sendMessageContent->clear();

    // focus user back to text field
    ui->sendMessageContent->setFocus();

}

