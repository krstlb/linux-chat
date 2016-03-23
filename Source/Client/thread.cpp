#include "thread.h"
#include "networking.h"

Thread::Thread(QObject *parent) : QObject(parent)
{

}

void Thread::createThread() {
    emit createThreadSignal();
}

void Thread::receiveData() {

    char  rbuf[BUFLEN];
    char  *bp;
    int bytes_to_read, n;

    bp = rbuf;
    bytes_to_read = BUFLEN;

    while(1) {
        while ((n = recv (sd, bp, bytes_to_read, 0)) < BUFLEN) {
          bp += n;
          bytes_to_read -= n;
        }

        qDebug() << rbuf;

        emit recvBufferSignal(rbuf);
    }
}
