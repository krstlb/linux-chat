#include <QApplication>

#include "receiveworker.h"
#include "networking.h"

/*---------------------------------------------------------------------------------------
--  SOURCE FILE:    receiveworker.cpp
--
--  PROGRAM:        Linux Chat application
--
--  FUNCTIONS:
--
--      ReceiveWorker::ReceiveWorker() : m_running(true)
--      void ReceiveWorker::doWork()
--      void ReceiveWorker::stopWork()
--      void ReceiveWorker::stopWork()
--
--
--  DATE:           March 23, 2016
--
--  REVISIONS:      (Date and Description)
--
--  DESIGNERS:      Krystle Bulalakaw
--
--  PROGRAMMER:     Krystle Bulalakaw
--
--  NOTES:
---------------------------------------------------------------------------------------*/

ReceiveWorker::ReceiveWorker()
    : m_running(true)
{

}

void ReceiveWorker::doWork()
{
    QString msgText;
    QString tempUsernameText;
    QString usernameText;
    QString tokenString;
    std::string token;

    while (m_running) {
        msgText = receiveDataFromServer();

        qDebug() << "GOT" << msgText;

        if (msgText.contains("closesd")) {
            endConnection();
        }

        if (msgText.contains("thisisausernameguud")) {
            qDebug() << "GOT YOUR USERNAME";
            tempUsernameText = msgText;
            tempUsernameText.remove("thisisausernameguud");
            usernameText = tempUsernameText;
            if (usernameText == "") {
                usernameText = "xXxQtGuRlOs1c4xXx";
            }

            emit updateUserListSignal(usernameText);
        } else {
            std::stringstream ss(msgText.toStdString());
            while(std::getline(ss, token, '|')) {
                tokenString = QString::fromUtf8(token.c_str());
                qDebug() << "TESTING:" << tokenString;
            }

            msgText.remove(QRegExp("([|][^|]*$)"));
            emit updateChatWindowSignal(msgText, tokenString);
        }
    }
    emit finished();
}

void ReceiveWorker::stopWork()
{
    m_running = false;
}
