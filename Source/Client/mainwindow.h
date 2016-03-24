#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QMessageBox>
#include <QAbstractAnimation>
#include <QKeyEvent>
#include <QScrollBar>
#include <QDialog>

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
    void disconnectClicked();

    void on_sendDataButton_clicked();

    void on_pushButton_clicked();

    void on_exportFileButton_clicked();

private:
    void connectSignalSlots();

    bool sending;

    bool connected;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
