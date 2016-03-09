#include "global.h"
#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->okDialogButton, SIGNAL (released()),this, SLOT (onOkayButtonClicked()));

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::onOkayButtonClicked()
{
    std::string nice = ui->usernameText->text().toStdString();
    //qStdOut() << nice;
}

