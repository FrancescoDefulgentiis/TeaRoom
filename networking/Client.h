#ifndef Client_h
#define Client_h

struct Client
{
    // The network socket for handling connections.
    int socket;
    // Variables dealing with the specifics of a connection.
    int domain;
    int service;
    int protocol;
    int port;
    u_long interface;
    // The request method allows a client to make a request of a specified server.
    char * (*request)(struct Client *client, char *server_ip, void *request, unsigned long size);
};

struct Client client_constructor(int domain, int service, int protocol, int port, u_long interface);


#endif 