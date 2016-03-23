#ifndef THREAD_H
#define THREAD_H

#include <QObject>

class Thread : public QObject
{
    Q_OBJECT
public:
    explicit Thread(QObject *parent = 0);
    void createThread();

signals:
    void recvBufferSignal(QString rbuf);
    void createThreadSignal();

public slots:
    void receiveData();
};

#endif // THREAD_H
