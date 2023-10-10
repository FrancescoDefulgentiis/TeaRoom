#ifndef Client_h
#define Client_h

#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <string>

struct Client
{
    // The network socket for handling connections.
    int socket;
    // Variables dealing with the specifics of a connection.
    int domain;
    int service;
    int protocol;
    int port;
    long interface;
    // The request method allows a client to make a request of a specified server.
    std::string (*request)(struct Client *client, std::string server_ip, std::string request, unsigned long size);
};

struct Client client_constructor(int domain, int service, int protocol, int port, long interface);
std::string request(struct Client *client, std::string server_ip, std::string request, unsigned long size);

#endif 