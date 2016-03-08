#include "networking.h"
#include "mainwindow.h"

MainWindow *win;

int listen_sd;

void initConnection() {
    struct sockaddr_in server, client_addr;

    // Create a stream socket
    if ((listen_sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
     //   SystemFatal("Cannot Create Socket!");


    // Bind an address to the socket
    bzero((char *)&server, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
 //   server.sin_port = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_ANY); // Accept connections from any client

    if (bind(listen_sd, (struct sockaddr *)&server, sizeof(server)) == -1)
   //     SystemFatal("bind error");

    // Listen for connections
    // queue up to LISTENQ connect requests
    listen(listen_sd, LISTENQ);

}

void endConnection() {

}

void sendDataToServer() {

}

void receiveDataFromServer() {

}
