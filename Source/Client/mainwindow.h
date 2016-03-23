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
    void OnSendClicked();
    void onConnectClicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
