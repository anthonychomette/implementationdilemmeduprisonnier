/* 
 * Fichier de gestion de l'envoi des données du client au serveur
 * 
 * @autor noeline
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include "../packetmanager.h"
#include "envoiClientToServ.h"
#include "receptionServToClient.h"

/**
 * @brief Envoi du paquet : informations du client
 * @param sockfd Socket de la connexion
 * @param clientID Numéro d'identification du client
 */
void clientInitClient(int sockfd, int clientID) {
    packetClientInit *packetCInit = createPacketClientInit(clientID);
    write(sockfd, packetCInit, sizeof (packetCInit));
    free(packetCInit);
}

/**
 * @brief Envoi du paquet : en attente de partie
 * @param sockfd Socket de la connexion
 */
void ClientWaitingGame(int sockfd) {
    packetClientWaitingGame *packetWaiting = createPacketClientWaitingGame();
    write(sockfd, packetWaiting, sizeof(packetWaiting));
    free(packetWaiting);
}

/**
 * @brief Envoi du paquet : client prêt
 * @param sockfd Socket de la connexion
 */
void clientPlayerReady(int sockfd) {
    packetClientPlayerReady *packetCPlayerReady = createPacketClientPlayerReady();
    write(sockfd, packetCPlayerReady, sizeof (packetCPlayerReady));
    free(packetCPlayerReady);
}

/**
 * Envoi du paquet : client collabore
 * @param sockfd Socket de la connexion
 */
void clientChoiceCollabore(int sockfd) {
    packetClientPlayerChoice *packetCPlayerChoice = createPacketClientPlayerChoice(0);
    write(sockfd, packetCPlayerChoice, sizeof (packetCPlayerChoice));
    free(packetCPlayerChoice);
    choiceToScore();
}

/**
 * Envoi du packet : client trahis
 * @param sockfd Socket de la connexion
 */
void clientChoiceBetray(int sockfd) {
    packetClientPlayerChoice *packetCPlayerChoice = createPacketClientPlayerChoice(1);
    write(sockfd, packetCPlayerChoice, sizeof (packetCPlayerChoice));
    free(packetCPlayerChoice);
    choiceToScore();
}

