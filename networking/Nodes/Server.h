#ifndef Server_h
#define Server_h

#include "../../DataStructures/Dictionary/Dictionary.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Server
{
    int domain;
    int service;
    int protocol;
    u_long interface;
    int port;
    int backlog;
    struct sockaddr_in address;
    int socket;
    
    struct Dictionary routes;
    
    void (*register_routes)(struct Server *server, char *(*route_function)(void *arg), char *path);
};

struct ServerRoute
{
    char * (*route_function)(void *arg);
};

struct Server server_constructor(int domain, int service, int protocol, u_long interface, int port, int backlog);

#endif
