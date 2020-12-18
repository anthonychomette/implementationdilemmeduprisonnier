/**
 * @file packetmanager.c
 * @author Thomas
 * @brief Gestion des paquets du Client: Création, aiguillage pour la réception
 * @version 0.1
 * @date 2020-12-17
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "packetmanager.h"
#include "Controller/envoiClientToServ.h"
#include "Controller/receptionServToClient.h"




/**
 * 
 * @brief Créer un paquet de type 1 : Initialisation Client, ClientInit
 * 
 * @param clientID Numéro d'identification du client
 * @return packetClientInit* pointeur sur le paquet
 */
packetClientInit * createPacketClientInit(int clientID) {
    
    packetClientInit *clientInit;
    clientInit = malloc(1 * sizeof(packetClientInit));     //free() liberer espace

    clientInit->type = 1; //Type 1 Message je suis connecté et je suis le client X
    clientInit->numClient = clientID;

    return clientInit;
}

/**
 * @brief Créer un paquet de type 2 : Attente Client, ClientWaitingGame
 * 
 * @return packetClientWaitingGame* pointeur sur le paquet
 */
packetClientWaitingGame * createPacketClientWaitingGame() {

    packetClientWaitingGame *WaitingGame;
    WaitingGame = malloc(1 * sizeof(WaitingGame));

    WaitingGame->type = 2; //Type 2 Je suis en attente d'une partie

    return WaitingGame;
}

/**
 * @brief Créer un paquet de type 3 : Joueur Prêt ?, ClientPlayerReady
 * 
 * @return packetClientPlayerReady* pointeur sur le paquet
 */
packetClientPlayerReady * createPacketClientPlayerReady() {
    
    packetClientPlayerReady *PlayerReady;
    PlayerReady = malloc(1 * sizeof(packetClientPlayerReady));

    PlayerReady->type = 3; //Type 3 Mon Joueur est prêt / pas prêt
    PlayerReady->playerIsReady = true;

    return PlayerReady;
}

/**
 * @brief Créer un paquet de type 4 : choix Client, ClientPlayerChoice
 * 
 * @param choice choix du client : false si il collabore, true si il trahis
 * @return packetClientPlayerChoice* pointeur sur le paquet
 */
packetClientPlayerChoice * createPacketClientPlayerChoice(bool choice) {

    packetClientPlayerChoice *playerChoice;
    playerChoice = malloc(1 * sizeof(packetClientPlayerChoice));

    //printf("Packet manager a pris votre thrahison en compte!!!!!!\n");
    playerChoice->type = 4; //Type 4 Le choix du joueur est collaborer : 0 ou trahir : 1
    playerChoice->choice = choice;

    return playerChoice;

}

/**
 * @brief Aiguillage des paquets reçu du serveur vers les bonnes fonctions de traitement
 * 
 * @param buffer_in buffer d'entrée
 * @param socket Socket de la connexion
 */
void receivePacket(char *buffer_in, int socket) {

    int *type = buffer_in;
    
    printf("Client received a %d packet\n", *type);

    switch (*type)
    {
    case 10: {
        packetServerInit *packetSInit = malloc(1 * sizeof(packetServerInit));
        memcpy(packetSInit, buffer_in, sizeof(packetServerInit));

        //Reponse Client : Je suis en attente d'une partie
        ClientWaitingGame(socket);
        printf("Client send a WaitingGame packet\n");

        free(packetSInit);
        break;
    }
    case 11: {
        packetServerWaitingEnd *packetSWaitingEnd = malloc(1 * sizeof(packetServerWaitingEnd));
        memcpy(packetSWaitingEnd, buffer_in, sizeof(packetServerWaitingEnd));
        printf("Fin de l'attente : Demarrage de la partie !\n");
        serverWaitingEnd();
        free(packetSWaitingEnd);
        break;
    }
    case 12: {
        packetServerIsPlayerReady *packetSIsPlayerReady= malloc(1 * sizeof(packetServerIsPlayerReady));
        memcpy(packetSIsPlayerReady, buffer_in, sizeof(packetServerIsPlayerReady));
        serverIsPlayerReady();
        clientPlayerReady(socket);
        free(packetSIsPlayerReady);
        break;
    }
    case 13: {
        packetServerMakeChoice *packetSMakeChoice = malloc(1 * sizeof(packetServerMakeChoice));
        memcpy(packetSMakeChoice, buffer_in, sizeof(packetServerMakeChoice));
        serverMakeChoice(socket);
        free(packetSMakeChoice);
        break;
    }
    case 14: {
        packetServerIsThisTheEnd *packetSIsThisTheEnd = malloc(1 * sizeof(packetServerIsThisTheEnd));
        memcpy(packetSIsThisTheEnd, buffer_in, sizeof(packetServerIsThisTheEnd));
        free(packetSIsThisTheEnd);
        break;
    }
    case 15: {
        packetServerScore *packetSScore = malloc(1 * sizeof(packetServerScore));
        memcpy(packetSScore, buffer_in, sizeof(packetServerScore));
        serverScore(packetSScore);
        free(packetSScore);
        break;
    }
    default: {
        perror("Erreur de reception du paquet : type non défini !!!");
        break;
    }

    }
}