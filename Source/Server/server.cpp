#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <map>
using namespace std;

#define SERVER_TCP_PORT 7000    // Default port
#define BUFLEN          6969      //Buffer length
#define TRUE            1
#define LISTENQ         5
#define MAXLINE         4096

map<int, string> clientlist;
map<int, string> usernamelist;
const string usernametag = "thisisausernameguud";
const string closesdtag = "closesd";
int client[FD_SETSIZE];

// Function Prototypes
static void SystemFatal(const char* );
void print_clientlist(map<int, string> &cl);
void print_usernamelist(map<int, string> &ul);
string create_s_clientlist();
void close_connection(map<int, string> &cl, map<int, string> &ul, int sockfd, int maxi, string ip);


int main (int argc, char **argv)
{
    int i, maxi, nready, bytes_to_read, arg;
    int listen_sd, new_sd, sockfd, port, maxfd;
    struct sockaddr_in server, client_addr;
    char *bp, buf[BUFLEN];
    socklen_t client_len;
    size_t bytes_read;
    fd_set rset, allset;

    switch(argc)
    {
        case 1:
            port = SERVER_TCP_PORT; // Use the default port
            break;
        case 2:
            port = atoi(argv[1]);   // Get user specified port
            break;
        default:
            fprintf(stderr, "Usage: %s [port]\n", argv[0]);
            exit(1);
    }

    // Create a stream socket
    if ((listen_sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        SystemFatal("Cannot Create Socket!");

    // set SO_REUSEADDR so port can be resused imemediately after exit, i.e., after CTRL-c
    arg = 1;
    if (setsockopt (listen_sd, SOL_SOCKET, SO_REUSEADDR, &arg, sizeof(arg)) == -1)
        SystemFatal("setsockopt");

    // Bind an address to the socket
    bzero((char *)&server, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_ANY); // Accept connections from any client

    if (bind(listen_sd, (struct sockaddr *)&server, sizeof(server)) == -1)
        SystemFatal("bind error");

    // Listen for connections
    // queue up to LISTENQ connect requests
    printf("Listening for connections on port %d...\n", port);
    listen(listen_sd, LISTENQ);

    maxfd   = listen_sd;    // initialize
    maxi    = -1;           // index into client[] array

    for (i = 0; i < FD_SETSIZE; i++) {
        client[i] = -1;     // -1 indicates available entry
    }
    FD_ZERO(&allset);
    FD_SET(listen_sd, &allset);

    while (1)
    {
        rset = allset;         // structure assignment
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);

        // new client connection
        if (FD_ISSET(listen_sd, &rset)) {
            client_len = sizeof(client_addr);

            if ((new_sd = accept(listen_sd, (struct sockaddr *) &client_addr, &client_len)) == -1)
                SystemFatal("accept error");

            clientlist.insert(pair<int, string>(new_sd, inet_ntoa(client_addr.sin_addr)));
            print_clientlist(clientlist);

            for (i = 0; i < FD_SETSIZE; i++)
                if (client[i] < 0) {
                    client[i] = new_sd; // save descriptor
                    break;
                }


            if (i == FD_SETSIZE) {
                SystemFatal ("Too many clients");
                continue;
            }

            FD_SET (new_sd, &allset);     // add new descriptor to set

            if (new_sd > maxfd)
                maxfd = new_sd; // for select

            if (i > maxi)
                maxi = i;   // new max index in client[] array

            if (--nready <= 0)
                continue;   // no more readable descriptors
         }
        // receive data from client
        for (i = 0; i <= maxi; i++) {
            if ((sockfd = client[i]) < 0)
                continue;

            if (FD_ISSET(sockfd, &rset)) {
                bp = buf;
                bytes_to_read = BUFLEN;

                bytes_read = read(sockfd, bp, bytes_to_read);
                if (bytes_read > 0) {
                    bp += bytes_read;
                    bytes_to_read -= bytes_read;
                }
                printf("Received from client %s: %s\n", inet_ntoa(client_addr.sin_addr), buf);

                string rcvstring(buf);
                // Received username
                if (rcvstring.find(usernametag) != string::npos) {
                    printf("Got user name\n");
                    size_t index = 0;
                    while (true) {
                        index = rcvstring.find(usernametag, index);
                        if (index == std::string::npos) break;

                        string username = rcvstring.replace(index, rcvstring.length(), "");
                        usernamelist.insert(pair<int, string>(new_sd, username));
                        print_usernamelist(usernamelist);
                     }

                    string s_clientlist = create_s_clientlist();
                    for (int c = 0; c <= maxi; c++) {
                        write(client[c], s_clientlist.c_str(), BUFLEN);
                    }
                // Received disconnect message
                } else if (rcvstring.find(closesdtag) != string::npos) {
                    printf("Got disconnect message\n");
                    write(sockfd, buf, BUFLEN);
                    close_connection(clientlist, usernamelist, sockfd, maxi, inet_ntoa(client_addr.sin_addr));
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                    break;
                // Received regular message
                } else {
                    for (int c = 0; c <= maxi; c++) {
                        if (client[c] >= 0 && c != i) {
                            write(client[c], buf, BUFLEN);
                        }
                    }
                }

                printf("Sent to client %s: %s\n", inet_ntoa(client_addr.sin_addr), buf);

                // Client disconnected
                if (bytes_read == 0) {
                    /*
                    // Remove client from list
                    if (clientlist.find(sockfd) != clientlist.end()) {
                        clientlist.erase(sockfd);
                        print_clientlist(clientlist);
                    }
                    //printf("fd[%4d] IP[%15s] disconnected.\n", it->first->first, it->second->second.c_str());

                    // Remove username from list
                    if (usernamelist.find(sockfd) != usernamelist.end()) {
                        usernamelist.erase(sockfd);
                        string s_clientlist = create_s_clientlist();
                        print_usernamelist(usernamelist);
                        for (int c = 0; c <= maxi; c++) {
                            write(client[c], s_clientlist.c_str(), BUFLEN);
                        }
                    }
                    printf("Client %s disconnected.\n", inet_ntoa(client_addr.sin_addr));
                    close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                    */
                    close_connection(clientlist, usernamelist, sockfd, maxi, inet_ntoa(client_addr.sin_addr));
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;;
                    break;
                }
            }
        }
        continue;
    }
    return(0);
}

// Prints the error stored in errno and aborts the program.
static void SystemFatal(const char* message)
{
    perror (message);
    exit (EXIT_FAILURE);
}

void print_clientlist(map<int, string> &cl) {
    printf("Updated client list:\n");
    for (map<int, string>::iterator it = cl.begin(); it != cl.end(); ++it) {
        printf("fd[%d] IP[%s]\n", it->first, it->second.c_str());
    }
}

void print_usernamelist(map<int, string> &ul) {
    printf("Updated username list:\n");
    for (map<int, string>::iterator it = ul.begin(); it != ul.end(); ++it) {
        printf("fd[%d] name[%s]\n", it->first, it->second.c_str());
    }
}

string create_s_clientlist() {
    string result = "";
    int i = 1;

    for (map<int, string>::iterator it = usernamelist.begin(); it != usernamelist.end(); ++it, ++i)
    {
        result += it->second + "<" + usernametag;
    }

    return result;
}

void close_connection(map<int, string> &cl, map<int, string> &ul, int sockfd, int maxi, string ip) {
    // Remove client from list
    if (cl.find(sockfd) != cl.end()) {
        clientlist.erase(sockfd);
        print_clientlist(cl);
    }
    //printf("fd[%4d] IP[%15s] disconnected.\n", it->first->first, it->second->second.c_str());

    // Remove username from list
    if (ul.find(sockfd) != ul.end()) {
        ul.erase(sockfd);
        string s_clientlist = create_s_clientlist();
        print_usernamelist(ul);
        for (int c = 0; c <= maxi; c++) {
            write(client[c], s_clientlist.c_str(), BUFLEN);
        }
    }
    printf("Client %s disconnected.\n", ip.c_str());
    close(sockfd);
}