#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <cstring>

//call maker
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

//camera capture
/*
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio/videoio.hpp>
*/

//phonebook
#include <vector>
#include <fstream>

#define PORT_NUMBER 42069

// Structure to represent a friend's information
struct Friend
{
  std::string name;
  std::string ipv6Address;
};

void Setup_Call(std::string senderIp, int senderPort, std::string receiverIp, int receiverPort);
int Mic_capture();
std::string Get_Public_ipv6();
//int Cam_capture();
void addFriend(std::vector<Friend> &phonebook, const std::string &filename);
void displayFriends(const std::vector<Friend> &phonebook);
std::string getFriendIp(const std::vector<Friend> &phonebook, const std::string &friendName);
