#ifndef SERVER_H
#define SERVER_H

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

#endif // SERVER_H