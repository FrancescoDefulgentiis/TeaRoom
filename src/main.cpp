#include "main.h"
#include "phonebook/phoneBook.h"
#include "networking/Networking.h"
#include "networking/Protocols/GetIp.h"

using namespace std;
/*
int main(){
  string MyIp = Get_Public_ipv4();//retrieve my public ipv4

  phoneBook phonebook;

  int choice;
  string friendName, friendIp;
  do{
    cout << "\nPhonebook Menu:" << endl;
    cout << "1. Add a friend and save phonebook" << endl;
    cout << "2. Display Friends" << endl;
    cout << "3. Call a friend" << endl;
    cout << "4. delete a friend from the phonebook" << endl;
    cout << "5. share your contact" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    system("clear");

    Friend friendInfo;

    switch (choice){
    case 1:
      //addFriend(phonebook, filename);
      std::cout << "Enter friend's name: ";
      cin>>friendInfo.name;
      cout << "Enter friend's ip address: ";
      cin>>friendInfo.ipAddress;
      phonebook.addFriend(friendInfo);
      break;
    case 2:
      //displayFriends(phonebook);
      phonebook.displayFriends();
      cin.ignore();
      getline(cin, friendName);
      break;
    case 3:
      cout << "Enter the name or the number the friend to call: ";
      cin.ignore();
      phonebook.displayFriends();
      getline(cin, friendInfo.name);
      friendInfo.ipAddress = phonebook.getFriendIp(friendInfo.name);
      startConnection(friendInfo.ipAddress);
      break;
    case 4:
      cout << "Enter the name or the number the friend to delete: ";
      cin.ignore();
      phonebook.displayFriends();
      getline(cin, friendName);
      phonebook.deleteFriend(friendName);
      break;
    case 5:
      cout << "Hi!, my ip address is: " << MyIp << endl;
      cin.ignore();
      getline(cin, friendName);
      break;
    case 6:
      cout << "Exiting program." << endl;
      break;
    default:
      cout << "Invalid choice. Please try again." << endl;
    }
  } while (choice != 6);

  return 0;
}
*/
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // IP address and port of your friend
    const char* friendIP = "friend_ip_address_here"; // Replace with your friend's IP address
    int friendPort = 12345; // Replace with the port your friend is listening on

    // Port for listening
    int listenPort = 12346; // Choose an available port for listening

    // Create a socket for sending
    int sendSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (sendSocket == -1) {
        perror("socket");
        return 1;
    }

    // Set up the friend's address
    struct sockaddr_in friendAddr;
    friendAddr.sin_family = AF_INET;
    friendAddr.sin_port = htons(friendPort);
    if (inet_pton(AF_INET, friendIP, &friendAddr.sin_addr) <= 0) {
        perror("inet_pton");
        close(sendSocket);
        return 1;
    }

    // Create a socket for listening
    int listenSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (listenSocket == -1) {
        perror("socket");
        close(sendSocket);
        return 1;
    }

    // Set up the local address for listening
    struct sockaddr_in listenAddr;
    listenAddr.sin_family = AF_INET;
    listenAddr.sin_port = htons(listenPort);
    listenAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the listening socket to the local address
    if (bind(listenSocket, (struct sockaddr*)&listenAddr, sizeof(listenAddr)) == -1) {
        perror("bind");
        close(sendSocket);
        close(listenSocket);
        return 1;
    }

    std::cout << "Listening on port " << listenPort << "..." << std::endl;

    // Message to send
    const char* message = "Hello, friend!";

    // Send the message to your friend
    if (sendto(sendSocket, message, strlen(message), 0, (struct sockaddr*)&friendAddr, sizeof(friendAddr)) == -1) {
        perror("sendto");
        close(sendSocket);
        close(listenSocket);
        return 1;
    }

    std::cout << "Message sent to your friend." << std::endl;

    // Buffer for receiving messages
    char buffer[1024];
    struct sockaddr_in senderAddr;
    socklen_t senderAddrSize = sizeof(senderAddr);

    // Receive a message
    ssize_t bytesReceived = recvfrom(listenSocket, buffer, sizeof(buffer), 0, (struct sockaddr*)&senderAddr, &senderAddrSize);
    if (bytesReceived == -1) {
        perror("recvfrom");
    } else {
        buffer[bytesReceived] = '\0';
        std::cout << "Received message: " << buffer << std::endl;
    }

    // Close both sockets
    close(sendSocket);
    close(listenSocket);

    return 0;
}