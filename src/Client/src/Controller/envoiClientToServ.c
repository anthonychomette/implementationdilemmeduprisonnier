/* 
 * Fichier de gestion de l'envoi des données du client au serveur
 * 
 * @autor noeline
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <gtk/gtk.h>
#include "../packetmanager.h"
//#include "envoiClientToServ.h"

/**
 * Envoi du packet des informations du client
 * 
 * @autor noeline
 * @param sockfd
 * @param clientID
 */
void clientInitClient(int sockfd, int clientID) {
    packetClientInit *packetCInit = createPacketClientInit(clientID);
    write(sockfd, packetCInit, sizeof (packetCInit));
    free(packetCInit);
}

/**
 * @brief  Envoi du packet En attente de partie
 * @autor Thomas
 * @param sockfd 
 */
void ClientWaitingGame(int sockfd) {
    packetClientWaitingGame *packetWaiting = createPacketClientWaitingGame();
    write(sockfd, packetWaiting, sizeof(packetWaiting));
    free(packetWaiting);
}

/**
 * Envoi du packet client pret
 * 
 * @autor noeline
 * @param sockfd
 */
void clientPlayerReady(int sockfd) {
    packetClientPlayerReady *packetCPlayerReady = createPacketClientPlayerReady();
    write(sockfd, packetCPlayerReady, sizeof (packetCPlayerReady));
    free(packetCPlayerReady);
    gtk_main_quit();
}

/**
 * Envoi du packet client collabore
 * 
 * @autor noeline
 * @param sockfd
 */
void clientChoiceCollabore(int sockfd) {
    packetClientPlayerChoice *packetCPlayerChoice = createPacketClientPlayerChoice(0);
    write(sockfd, packetCPlayerChoice, sizeof (packetCPlayerChoice));
    free(packetCPlayerChoice);
    gtk_main_quit();
}

/**
 * Envoi du packet client trahis
 * 
 * @autor noeline
 * @param sockfd
 */
void clientChoiceBetray(int sockfd) {
    packetClientPlayerChoice *packetCPlayerChoice = createPacketClientPlayerChoice(1);
    write(sockfd, packetCPlayerChoice, sizeof (packetCPlayerChoice));
    free(packetCPlayerChoice);
    gtk_main_quit();
}