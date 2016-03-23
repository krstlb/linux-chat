#include <QApplication>

#include "receiveworker.h"
#include "networking.h"

ReceiveWorker::ReceiveWorker()
    : m_running(true)
{

}

void ReceiveWorker::doWork()
{
    qDebug() << "inside ReceiveDoWork";
    while (m_running) {
        receiveDataFromServer();
    }
    emit finished();
}

void ReceiveWorker::stopWork()
{
    m_running = false;
}
