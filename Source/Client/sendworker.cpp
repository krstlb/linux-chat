#include <QApplication>

#include "sendworker.h"
#include "networking.h"

SendWorker::SendWorker(QString msgText)
{
    this->msgText = msgText;
}

void SendWorker::doWork()
{
    // convert qstring message into char * message for sending
    std::string msg (msgText.toStdString());
    char* message = new char [msg.size()+1];
    strcpy(message, msg.c_str());

    // Send message
    std::thread sendThread(sendDataToServer, std::ref(message));
    sendThread.join();

    emit finished();
}
