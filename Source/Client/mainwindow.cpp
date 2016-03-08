#include "mainwindow.h"
#include "connectdialog.h"
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
    QScrollBar *sb = ui->textWindow->verticalScrollBar();
    QString msgText = ui->sendMessageContent->toPlainText();
    QTime time(QTime::currentTime());

    // std::string msg (text.toStdString());

    // send message to server
    // sendDataToServer(msg.c_str());

    // time format
    QString timeFormatString = "[" + time.toString() + "]";
    QString divFormat = "<div style = \"background-color: #0078EE;color: white;\">";
   // QString divFormat2 = "<div style = \"background-color: #0078EE;color: white;text-align:right\">";

    // inserts html code formatting
    ui->textWindow->insertHtml(divFormat + timeFormatString + "<div></div>" +
                               msgText + "</div>" + "<div></div>");

    // clear text after you send
    ui->sendMessageContent->clear();

    // always scroll to bottom after sending
    sb->setValue(sb->maximum());

    // focus user back to text field
    ui->sendMessageContent->setFocus();

}

