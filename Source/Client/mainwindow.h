#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QMessageBox>
#include <QAbstractAnimation>
#include <QKeyEvent>
#include <QScrollBar>
#include <QDialog>
#include "receiveworker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void updateTextWindow(QString msgText, QString userText);
    void updateUserList(QString username);

    void sendFinished();

    void on_sendDataButton_clicked();

    void on_pushButton_clicked();

    void on_exportFileButton_clicked();

    void on_disconnectButton_clicked();

signals:
    void disconnectClicked();

private:
    void connectSignalSlots();
    void closeEvent(QCloseEvent *event);
    void goOffline();

    bool sending;
    bool connected;

    Ui::MainWindow *ui;
    QThread             *workerThread;
    ReceiveWorker       *worker;
};

#endif // MAINWINDOW_H
