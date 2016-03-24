#ifndef RECEIVEWORKER_H
#define RECEIVEWORKER_H

#include <QObject>

class ReceiveWorker : public QObject
{
    Q_OBJECT

public:
    ReceiveWorker();

    bool m_running;

public slots:
    void doWork();
    void stopWork();

signals:
    void receiveData();
    void finished();
    void updateChatWindowSignal(QString msgText, QString usernameText);
    void updateUserListSignal(QString username);
    void clearUserListSignal();
};

#endif // RECEIVEWORKER_H
