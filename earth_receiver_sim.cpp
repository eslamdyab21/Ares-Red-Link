#include <iostream>
#include <fstream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#include "logger/logger.h"

#define SERVER_PORT 8080
#define BUFFER_SIZE 4096  

void earthReceiver() {
    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_len = sizeof(clientAddr);
    char buffer[BUFFER_SIZE] = {0};

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Socket creation failed\n";
        logMessage("ERROR", "EarthReceiver -> Read line");
        return;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(SERVER_PORT);

    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Binding failed\n";
        logMessage("ERROR", "EarthReceiver -> Read line");
        return;
    }

    logMessage("INFO", "EarthReceiver -> Listening for incoming sensor data...");


    while (true) {
        int valread = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&clientAddr, &addr_len);
        if (valread > 0) {
            logMessage("INFO", "EarthReceiver -> Received a record...");
            std::cout << "Received Data:\n" << buffer;
        }
    }

    logMessage("INFO", "EarthReceiver -> Close socket connection...");
    close(sockfd);
}



int main() {
    earthReceiver();


    return 0;
}
