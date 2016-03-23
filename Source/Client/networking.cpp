#include "networking.h"
#include "mainwindow.h"
#include "dialog.h"

MainWindow *win;

int sd;

void initConnection(int port, char* ip) {
    struct sockaddr_in server;
    struct hostent  *hp;

    QMessageBox messageBox;

    qDebug() << port << " " << ip;

    // Create a TCP Socket
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
      perror("Cannot create socket");

    // Set up address structure
    bzero((char *)&server, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    if ((hp = gethostbyname(ip)) == NULL)
    {
        messageBox.critical(0,"Error","Hostname could not be found.");
        messageBox.setFixedSize(500,200);
    }
    bcopy(hp->h_addr, (char *)&server.sin_addr, hp->h_length);

    // Connecting to the server
    if (::connect (sd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        messageBox.critical(0,"Error","No good, Can not connect.");
        messageBox.setFixedSize(500,200);
    }
}

void sendDataToServer(const char* msg) {

    qDebug() << msg;

    send (sd, msg, BUFLEN, 0);
}

void receiveDataFromServer() {

}

void endConnection() {

}

