#ifndef NETWORKING_H
#define NETWORKING_H

#include "global.h"

#define SERVER_TCP_PORT 7000	// Default port
#define BUFLEN	6969         //Buffer length
#define TRUE	1
#define LISTENQ	5
#define MAXLINE 4096

int initConnection(int port, char* ip);
void endConnection();
void sendDataToServer(const char* sbuf);
QString receiveDataFromServer();

#endif // NETWORKING_H
