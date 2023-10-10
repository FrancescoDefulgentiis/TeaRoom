#include "Networking.h"

#include "../DataStructures/DataStructures.h"
#include "../Systems/Systems.h"

#define PORT 42069
#define mess_size 1024

using namespace std;

void *server_function(void *arg)
{

  struct Server server = server_constructor(AF_INET6, SOCK_DGRAM, 0, INADDR_ANY, PORT, 20); // AF_INET6 IS FOR IPV6, SOCK_DGRAM IS FOR UDP, INADDR_ANY

  struct sockaddr *address = (struct sockaddr *)&server.address; // pre-defined structure for socket address
  socklen_t address_length = (socklen_t)sizeof(server.address);

  while (1)
  { // to accept multiple connections or peers
    int client = accept(server.socket, address, &address_length);
    char request[mess_size];
    read(client, request, mess_size);
    cout << inet_ntoa(server.address.sin_addr) << " says: " << request << endl;
    close(client);
  }
  return NULL;
}

void client_function(string request)
{
  struct Client client = client_constructor(AF_INET6, SOCK_DGRAM, 0, PORT+1, INADDR_ANY); // AF_INET6 IS FOR IPV6, SOCK_DGRAM IS FOR UDP, INADDR_ANY
  client.request(&client, "::1", request, mess_size);
}

int startConnection()
{
  cout << "Starting connection..." << endl;
  pthread_t server_thread;
  pthread_create(&server_thread, NULL, server_function, NULL);

  while (1)
  {
    string request;
    cin.ignore();
    getline(cin, request);
    client_function(request);
  }
}