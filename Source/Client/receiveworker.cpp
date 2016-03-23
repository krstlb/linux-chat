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
    qDebug() << "inside ReceiveDoWork";
    while (m_running) {
        msgText = receiveDataFromServer();

        emit updateChatWindowSignal(msgText);
    }
    emit finished();
}

void ReceiveWorker::stopWork()
{
    m_running = false;
}
