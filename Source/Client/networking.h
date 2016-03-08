#ifndef NETWORKING_H
#define NETWORKING_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_TCP_PORT 7000	// Default port
#define BUFLEN	255         //Buffer length
#define TRUE	1
#define LISTENQ	5
#define MAXLINE 4096

void initConnection();
void endConnection();
void sendDataToServer();
void receiveDataFromServer();


#endif // NETWORKING_H
