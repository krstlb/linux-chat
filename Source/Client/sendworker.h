#ifndef SENDWORKER_H
#define SENDWORKER_H

#include <QObject>
#include <QMainWindow>

class SendWorker : public QObject
{
    Q_OBJECT

public:
    SendWorker(QString msgText);

public slots:
    void doWork();

signals:
    void updateTextWindow(QString);
    void finished();

 private:
    QString msgText;
};

#endif // SENDWORKER_H
