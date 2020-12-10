/* 
 * Fichier de gestion de l'envoi des données du serveur au client
 * 
 * @autor noeline
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../packetmanager.h"
#include "receptionClientToServ.h"

/**
 * Demander si le client est pret
 * 
 * @autor noeline
 * @param sockfd
 */
void serverIsPlayerReady(int sockfd) {
    packetServerIsPlayerReady *packetSIsPlayerReady = createPacketServerIsPlayerReady();
    write(sockfd, packetSIsPlayerReady, sizeof (packetSIsPlayerReady));
    free(packetSIsPlayerReady);
}

/**
 * Sort le client de l'attente
 * 
 * @autor noeline
 * @param sockfd
 */
void serverWaitingEnd(int sockfd) {
    packetServerWaitingEnd *packetSWaitingEnd = createPacketServerWaitingEnd();
    write(sockfd, packetSWaitingEnd, sizeof (packetSWaitingEnd));
    free(packetSWaitingEnd);
}

/**
 * Demande au cient de faire un choix
 * 
 * @autor noeline
 * @param sockfd
 */
void serverMakeChoice(int sockfd) {
    packetServerMakeChoice *packetSMakeChoice = createPacketServerMakeChoice();
    write(sockfd, packetSMakeChoice, sizeof (packetSMakeChoice));
    free(packetSMakeChoice);
}

/**
 * Envoi du score du round
 * 
 * @autor noeline
 * @param sockfd
 */
void serverScore(int sockfd) {
    //TODO lecture du résultat dans le csv et remplacer le zéro par le résultat lu dans le sv
    int result = 0;
    packetServerScore *packetSScore = createPacketServerScore(result);
    write(sockfd, packetSScore, sizeof (packetSScore));
    free(packetSScore);
}


/**
 * Envoi du message de fin de l'experience
 * 
 * @autor noeline
 * @param sockfd
 */
void serverIsThisTheEnd(int sockfd) {
    packetServerIsThisTheEnd *packetSIsThisTheEnd = createPacketServerIsThisTheEnd(1);
    write(sockfd, packetSIsThisTheEnd, sizeof (packetSIsThisTheEnd));
    free(packetSIsThisTheEnd);
}

/**
 * Envoi d'un message qui stipule que ce n'est pas la fin
 * 
 * @autor noeline
 * @param sockfd
 */
void serverIsNotThisTheEnd(int sockfd) {
    packetServerIsThisTheEnd *packetSIsThisTheEnd = createPacketServerIsThisTheEnd(0);
    write(sockfd, packetSIsThisTheEnd, sizeof (packetSIsThisTheEnd));
    free(packetSIsThisTheEnd);
}

/**
 * Envoi d'un message qui indique que le serveur a compris le client et qu'il est prêt
 * 
 * @autor Thomas
 * @param sockfd
 */
void serverInit(int sockfd) {
    packetServerInit *packetSInit = createPacketServerInit();
    write(sockfd, packetSInit, sizeof (packetServerInit));
    free(packetSInit);
}