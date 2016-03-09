#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QLineEdit>

class ConnectDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConnectDialog(QWidget *parent = 0);

    QString searchString() const;

private:
    QLineEdit *m_lineEdit;
};

#endif // CONNECTDIALOG_H
