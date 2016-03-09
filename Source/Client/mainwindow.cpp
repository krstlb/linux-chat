#include "mainwindow.h"
#include "dialog.h"
#include "ui_mainwindow.h"

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

    // std::string msg (text.toStdString());

    // send message to server
    // sendDataToServer(msg.c_str());

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

void MainWindow::onConnectClicked()
{

   Dialog *dialog = new Dialog(this);
   dialog->show();

  //  QMessageBox::information(this, tr("Hello"), tr("Enter a nickname."));
}

