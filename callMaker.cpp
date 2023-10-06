#include "lib.h"

using namespace std;

void Setup_Call(string senderIp, int senderPort, string receiverIp, int receiverPort){
  int sender_socket, receiver_socket;             // File descriptors for sending and receiving messages
  struct sockaddr_in6 sender_addr, receiver_addr; // Predefined struct for sender and receiver addresses
  socklen_t addr_len = sizeof(struct sockaddr_in6);

  // Create sockets
  sender_socket = socket(AF_INET6, SOCK_DGRAM, 0); // AF_INET6 means IPv6, SOCK_DGRAM means UDP
  receiver_socket = socket(AF_INET6, SOCK_DGRAM, 0);
  if (sender_socket == -1 || receiver_socket == -1){// Error handles
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  // Configure sender address
  memset(&sender_addr, 0, addr_len); // Set all bytes of sender_addr to 0 to avoid garbage values
  sender_addr.sin6_family = AF_INET6;
  sender_addr.sin6_port = htons(senderPort);               // htons converts the port number to network byte order
  inet_pton(AF_INET6, senderIp.c_str(), &(sender_addr.sin6_addr)); // Converts the IP address from text to binary form

  // Configure receiver address
  memset(&receiver_addr, 0, addr_len);
  receiver_addr.sin6_family = AF_INET6;
  receiver_addr.sin6_port = htons(receiverPort);
  inet_pton(AF_INET6, receiverIp.c_str(), &(receiver_addr.sin6_addr));

  // Bind receiver socket to address
  if (bind(receiver_socket, (struct sockaddr *)&receiver_addr, addr_len) == -1){
    perror("Receiver socket binding failed");
    exit(EXIT_FAILURE);
  }

  // Sending data from sender to receiver
  const char *sender_message = "Hello, receiver!\0";
  sendto(sender_socket, sender_message, strlen(sender_message), 0,
         (struct sockaddr *)&receiver_addr, addr_len);

  // Receiving data at receiver
  char receiver_buffer[1024];
  recvfrom(receiver_socket, receiver_buffer, sizeof(receiver_buffer), 0,
           (struct sockaddr *)&sender_addr, &addr_len);
  cout << "Received message: " << receiver_buffer << endl;

  // Close sockets
  close(sender_socket);
  close(receiver_socket);
}
