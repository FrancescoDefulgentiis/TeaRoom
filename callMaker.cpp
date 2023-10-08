#include "lib.h"

using namespace std;

/*
  the function that will later be given to the thread, sender_socket is the socket that will send the message, 
  receiver_addr is the address of the receiver, addr_len is the length of the address
*/

bool shouldTerminate = false;
sem_t sem;

void SenderFun(int sender_socket, const struct sockaddr_in6 &receiver_addr, socklen_t addr_len)
{
  string user_message;
  while(!shouldTerminate){
    cout << "Enter the message to send (\"end!\" to end the call): ";
    getline(cin, user_message);//get message from user

    ssize_t bytesSent = sendto(sender_socket, user_message.c_str(), user_message.size(), 0,
                              (struct sockaddr *)&receiver_addr, addr_len);
    //error handling
    if (bytesSent == -1){
      cerr << "Error sending data: " << strerror(errno) << endl;
    }else{
      cout << "Sent " << endl;
    }
    

    // check if user wants to end the call
    if (user_message == "end!")
    {
      cout << "Call ended." << endl;
      sem_wait(&sem);
      shouldTerminate = true;
      sem_post(&sem);
    }
  }
  cout << "sender thread joined" << endl;
}

/*
  the function that will later be given to the thread, receiver_socket is the socket that will receive the message,
  sender_addr is the address of the sender, addr_len is the length of the address
*/
void ReceiverFun(int receiver_socket, struct sockaddr_in6 &receiver_addr, socklen_t addr_len)
{
  char receiver_buffer[1024];
  while(!shouldTerminate){
    ssize_t bytesReceived = recvfrom(receiver_socket, receiver_buffer, sizeof(receiver_buffer), 0,
                                    (struct sockaddr *)&receiver_addr, &addr_len);
    //error handling
    if (bytesReceived == -1){
      cerr << "Error receiving data from sender." << endl;
    }else{
      receiver_buffer[bytesReceived] = '\0'; // Null-terminate the received data
      if (strcmp(receiver_buffer, "end!") == 0){
        cout << "Call ended." << endl;
        sem_wait(&sem);
        shouldTerminate=true;
        sem_post(&sem);
      }else{
        cout << "\nReceived message: " << receiver_buffer << endl;
      }
    }
  }
  cout << "receiver thread joined" << endl;
}

/*
  once given the ips and ports of the sender and receiver, this function will set up the sockets and threads
*/
void Setup_Call(string senderIp, int senderPort, string receiverIp, int receiverPort)
{
  int sender_socket, receiver_socket;
  struct sockaddr_in6 sender_addr, receiver_addr;//pre-defined structure for the address
  socklen_t addr_len = sizeof(struct sockaddr_in6);//length of the address

  //create the sockets
  sender_socket = socket(AF_INET6, SOCK_DGRAM, 0);
  receiver_socket = socket(AF_INET6, SOCK_DGRAM, 0);
  if (sender_socket == -1 || receiver_socket == -1)
  {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(&sender_addr, 0, addr_len);//use memset to avoid garbage values
  sender_addr.sin6_family = AF_INET6;//ipv6
  sender_addr.sin6_port = htons(senderPort);//htons convert the port number to network byte order
  inet_pton(AF_INET6, senderIp.c_str(), &(sender_addr.sin6_addr));//convert the ip to network byte order

  memset(&receiver_addr, 0, addr_len);
  receiver_addr.sin6_family = AF_INET6;
  receiver_addr.sin6_port = htons(receiverPort);
  inet_pton(AF_INET6, receiverIp.c_str(), &(receiver_addr.sin6_addr));

  if (bind(receiver_socket, (struct sockaddr *)&receiver_addr, addr_len) == -1 || bind(sender_socket, (struct sockaddr *)&sender_addr, addr_len) == -1)
  {
    perror("Socket binding failed");
    exit(EXIT_FAILURE);
  }

  sem_init(&sem, 0, 1);

  //start the threads
  thread sender_thread(SenderFun, sender_socket, std::ref(receiver_addr), addr_len);
  thread receiver_thread(ReceiverFun, receiver_socket, std::ref(receiver_addr), addr_len);

  //wait for the threads to finish
  sender_thread.join();
  receiver_thread.join();
  cout << "thread joined." << endl;

  //close the sockets
  close(sender_socket);
  close(receiver_socket);
}
