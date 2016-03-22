#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_TCP_PORT     7000    // Default port
#define BUFLEN              80        // Buffer length

int main (int argc, char **argv)
{
    int n, bytes_to_read;
    int sd, port;
    struct hostent    *hp;
    struct sockaddr_in server;
    char *host, *bp, rbuf[BUFLEN], sbuf[BUFLEN], **pptr;
    char str[16];

    switch(argc)
    {
        case 2:
            host = argv[1];    // Host name
            port = SERVER_TCP_PORT;
            break;
        case 3:
            host = argv[1];
            port = atoi(argv[2]);    // User specified port
            break;
        default:
            fprintf(stderr, "Usage: %s host [port]\n", argv[0]);
            exit(1);
    }

    // Create the socket
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Cannot create socket");
        exit(1);
    }
    bzero((char *)&server, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    if ((hp = gethostbyname(host)) == NULL)
    {
        fprintf(stderr, "Unknown server address\n");
        exit(1);
    }
    bcopy(hp->h_addr, (char *)&server.sin_addr, hp->h_length);

    // Connecting to the server
    if (connect (sd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        fprintf(stderr, "Can't connect to server\n");
        perror("connect");
        exit(1);
    }
    printf("Connected:        Server Name: %s\n", hp->h_name);
    pptr = hp->h_addr_list;
    printf("\t\tIP Address: %s\n", inet_ntop(hp->h_addrtype, *pptr, str, sizeof(str)));

    // Send
    if (fork() == 0) {
        while (1) {
            // Get user's text
            fgets (sbuf, BUFLEN, stdin);
            // Transmit data through the socket
            send (sd, sbuf, BUFLEN, 0);
        }
    } else { // Receive
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
            printf("Received:\n");
            printf ("%s\n", rbuf);

            // TODO: action to disconnect
            if (sbuf[0] == 'q') {
                break;
            }
        }
    }

    // Flush stdout and close socket
    fflush(stdout);
    close (sd);

    return (0);
}
