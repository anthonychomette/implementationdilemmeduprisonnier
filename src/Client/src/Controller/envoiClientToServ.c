/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "../packetmanager.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

void clientInitClient(int sockfd, int clientID) {

    packetClientInit *packetInit = createPacketClientInit(clientID);
    write(sockfd, packetInit, sizeof(packetInit));
    free(packetInit);
}

void ClientWaitingGame(int sockfd) {
    packetClientWaitingGame *packetWaiting = createPacketClientWaitingGame();
    write(sockfd, packetWaiting, sizeof(packetWaiting));
    free(packetWaiting);
}