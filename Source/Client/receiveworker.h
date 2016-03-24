#ifndef RECEIVEWORKER_H
#define RECEIVEWORKER_H

#include <QObject>

class ReceiveWorker : public QObject
{
    Q_OBJECT

public:
    ReceiveWorker();

public slots:
    void doWork();
    void stopWork();

signals:
    void receiveData();
    void finished();
    void updateChatWindowSignal(QString msgText, QString usernameText);
    void updateUserListSignal(QString username);

private:
    bool m_running;
};

#endif // RECEIVEWORKER_H
