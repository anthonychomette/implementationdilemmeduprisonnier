/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>

#include "packetmanager.h"
#include "envoiClientToServ.h"

void clientInitClient(int sockfd, int clientID) {
    packetClientInit *packetCInit = createPacketClientInit(int clientID);
    write(sockfd, packetCInit, sizeof (packetCInit));
    free(packetCInit);
}

void clientPlayerReady(int sockfd) {
    packetClientPlayerReady *packetCPlayerReady = createPacketClientPlayerReady();
    write(sockfd, packetCPlayerReady, sizeof (packetCPlayerReady));
    free(packetCPlayerReady);
}

void clientChoiceCollabore(int &sockfd) {
    packetClientPlayerChoice *packetCPlayerChoice = createPacketClientPlayerChoice(0);
    write(sockfd, packetCPlayerChoice, sizeof (packetCPlayerChoice));
    free(packetCPlayerChoice);
}

void clientChoiceBetray(int &sockfd) {
    packetClientPlayerChoice *packetCPlayerChoice = createPacketClientPlayerChoice(1);
    write(sockfd, packetCPlayerChoice, sizeof (packetCPlayerChoice));
    free(packetCPlayerChoice);
}