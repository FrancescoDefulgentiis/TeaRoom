#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

void Setup_Call(const char* senderIp, int senderPort, const char* receiverIp, int receiverPort);
int Mic_capture();
int Cam_capture();
