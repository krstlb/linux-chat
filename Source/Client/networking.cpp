#include "networking.h"
#include "mainwindow.h"
#include "receiveworker.h"

/*---------------------------------------------------------------------------------------
--  SOURCE FILE:    networking.cpp
--
--  PROGRAM:        Linux Chat application
--
--  FUNCTIONS:
--
--      void initConnection(int port, char* ip)
--      void sendDataToServer(const char* msg)
--      QString receiveDataFromServer()
--      void endConnection()
--
--
--  DATE:           March 23, 2016
--
--  REVISIONS:      (Date and Description)
--
--  DESIGNERS:      Oscar Kwan, Krystle Bulalakaw
--
--  PROGRAMMER:     Oscar Kwan, Krystle Bulalakaw
--
--  NOTES:
--  This class contains the logic behind client side networking. It includes functions
--  that initiates a TCP connection and do sending and receiving.
---------------------------------------------------------------------------------------*/

MainWindow *win;

int sd;
int n, bytes_to_read;
char *host, *bp, rbuf[BUFLEN], sbuf[BUFLEN];

/*---------------------------------------------------------------------------------------------------------------------
-- FUNCTION: initConnection
--
-- DATE: March 23, 2016
--
-- REVISIONS: None
--
-- DESIGNER: Oscar Kwan
--
-- PROGRAMMER: Oscar Kwan
--
-- INTERFACE:
--
--          void (int port, char* ip)
--              int port
--                  - port form user input
--              char* ip
--                  - ip address from user input
--
-- RETURNS: void
--
-- NOTES:
-- This function initializes the connection with the client and the server by creating a tcp socket and
-- calling connect to the server.
---------------------------------------------------------------------------------------------------------------------*/
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

/*---------------------------------------------------------------------------------------------------------------------
-- FUNCTION: sendDataToServer
--
-- DATE: March 23, 2016
--
-- REVISIONS: None
--
-- DESIGNER: Oscar Kwan
--
-- PROGRAMMER: Oscar Kwan
--
-- INTERFACE:
--
--          void (const char* msg)
--              const char* msg
--                  - message to be sent to the server
--
-- RETURNS: void
--
-- NOTES:
-- This function is a wrapper function for the network send call.
---------------------------------------------------------------------------------------------------------------------*/
void sendDataToServer(const char* msg) {
    qDebug() << msg;

    send (sd, msg, BUFLEN, 0);
}

/*---------------------------------------------------------------------------------------------------------------------
-- FUNCTION: receiveDataFromServer
--
-- DATE: March 23, 2016
--
-- REVISIONS: None
--
-- DESIGNER: Oscar Kwan
--
-- PROGRAMMER: Oscar Kwan
--
-- RETURNS: QString
--
-- NOTES:
-- This function is the main function that deals with receiving strings from the server. It checks if it is either
-- a username or an actual message. This function is called inside a QThread that emits signals to the gui for updating.
---------------------------------------------------------------------------------------------------------------------*/
QString receiveDataFromServer() {
    qDebug("Receiving data from server");
    while (1) {
        bp = rbuf;
        bytes_to_read = BUFLEN;

        // Client makes repeated calls to recv until no more data is expected to arrive
        n = 0;
        while ((n = recv (sd, bp, bytes_to_read, 0)) < BUFLEN)
        {
           bp += n;
           bytes_to_read -= n;
        }

        qDebug() << "Received: "<< rbuf;

        QString temp(rbuf);
        return temp;
    }
}

/*--------------------------------------------------------------------------------------
-- FUNCTION: endConnection();
--
-- DATE: March 23, 2016
--
-- REVISIONS: None
--
-- DESIGNER: Krystle Bulalakaw
--
-- PROGRAMMER: Krystle Bulalakaw
--
-- INTERFACE:
--
--          void ()
--
-- RETURNS: void
--
-- NOTES:
-- Close the socket connection to the server.
---------------------------------------------------------------------------------------*/
void endConnection() {
    qDebug() << "closing socket";
    close(sd);
}

