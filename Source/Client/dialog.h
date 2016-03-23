#ifndef DIALOG_H
#define DIALOG_H

#include "global.h"
#include "mainwindow.h"
#include "thread.h"
#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0, MainWindow *mainWindow = 0);
    QThread *qt;
    Thread *thread;
    ~Dialog();

private slots:
    void on_okayDialogButton_accepted();

private:
    Ui::Dialog *ui;
    Ui::MainWindow *mainUi;
};

#endif // DIALOG_H
