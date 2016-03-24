#include <QApplication>

#include "receiveworker.h"
#include "networking.h"

ReceiveWorker::ReceiveWorker()
    : m_running(true)
{

}

void ReceiveWorker::doWork()
{
    QString msgText;
    QString tempUsernameText;
    QString usernameText;
    qDebug() << "inside ReceiveDoWork";
    while (m_running) {
        msgText = receiveDataFromServer();

        qDebug() << "GOT" << msgText;

        if (msgText.contains("thisisausernameguud")) {
            qDebug() << "GOT YOUR USERNAME";
            tempUsernameText = msgText;
            tempUsernameText.remove("thisisausernameguud");
            usernameText = tempUsernameText;
        }

        emit updateChatWindowSignal(msgText, usernameText);
    }
    emit finished();
}

void ReceiveWorker::stopWork()
{
    m_running = false;
}
