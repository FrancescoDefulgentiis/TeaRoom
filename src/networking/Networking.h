#ifndef Networking_h
#define Networking_h

#include "Nodes/Server.h"
#include "Nodes/Client.h"
#include "Nodes/PeerToPeer.h"
#include "Nodes/HTTPServer.h"
#include "Protocols/HTTPRequest.h"

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <arpa/inet.h>

void *server_function(void *arg);
void client_function(std::string request);
int startConnection(std::string FriendIp);

#endif