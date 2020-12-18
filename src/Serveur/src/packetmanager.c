/**
 * @file packetmanager.c
 * @author Thomas
 * @brief 
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

#include "Controller/envoiServToClient.h"
#include "packetmanager.h"



/**
 * @brief Fonction permettant de créer un paquet ServerInit
 * 
 * @return packetServerInit* Pointeur sur le paquet
 */
packetServerInit * createPacketServerInit() {
    
    packetServerInit *serverInit;
    serverInit = malloc(1 * sizeof(packetServerInit));

    serverInit->type = 10; //Type 10 Message Bonjour Client X, la connexion a été établie
    serverInit->ServerReady = true;

    return serverInit;
}

/**
 * @brief Fonction permettant de créer un paquet ServerWaitingEnd
 * 
 * @return packetServerWaitingEnd* Pointeur sur le paquet
 */
packetServerWaitingEnd * createPacketServerWaitingEnd() {

    packetServerWaitingEnd *WaitingEnd;
    WaitingEnd = malloc(1 * sizeof(packetServerWaitingEnd));

    WaitingEnd->type = 11; //Type 11 Message Sortez de votre attente SVP une partie va démarrer !

    return WaitingEnd;
}

/**
 * @brief Fonction permettant de créer un paquet ServerIsPlayerReady
 * 
 * @return packetServerIsPlayerReady* Pointeur sur le paquet
 */
packetServerIsPlayerReady * createPacketServerIsPlayerReady() {
    
    packetServerIsPlayerReady *IsPlayerReady;
    IsPlayerReady = malloc(1 * sizeof(packetServerIsPlayerReady));

    IsPlayerReady->type = 12; //Type 12 Message Demander a votre joueur si il est prêt

    return IsPlayerReady;
}

/**
 * @brief Fonction permettant de créer un paquet ServerMakeChoice
 * 
 * @return packetServerMakeChoice* Pointeur sur le paquet
 */
packetServerMakeChoice * createPacketServerMakeChoice() {

    packetServerMakeChoice *MakeChoice;
    MakeChoice = malloc(1 * sizeof(packetServerIsPlayerReady));

    MakeChoice->type = 13; //Type 13 Message Faites vos jeux.

    return MakeChoice;

}

/**
 * @brief Fonction permettant de créer un paquet ServerIsThisTheEnd
 * 
 * @param end True : C'est la fin, False ce n'est pas la fin
 * @return packetServerIsThisTheEnd* Pointeur sur le paquet
 */
packetServerIsThisTheEnd * createPacketServerIsThisTheEnd(bool end){

    packetServerIsThisTheEnd *IsThisTheEnd;
    IsThisTheEnd = malloc(1 * sizeof(packetServerIsThisTheEnd));

    IsThisTheEnd->type = 14; //Type 14 Message Est-ce la fin ?
    IsThisTheEnd->gameEnd = end;
    return IsThisTheEnd;
}

/**
 * @brief Fonction permettant de créer un paquet ServerScore
 * 
 * @param score Score du joueur
 * @return packetServerScore* pointeur sur le paquet
 */
packetServerScore * createPacketServerScore(int score) {

    packetServerScore *Score;
    Score = malloc(1 * sizeof(packetServerScore));

    Score->type = 15; //Type 15 Voici votre score
    Score->score = score;
    return Score;
}

/**
 * @brief Fonction permettant d'aiguiller les paquet reçu vers le bon traitement suivant leurs type
 * 
 * @param buffer_in Paquet brut a determiner
 * @param Player Structure player qui contient toute les données du joueur
 */
 void receivePacket(char *buffer_in, player* Player) {

    int *type = buffer_in;

    printf("Server received a packet of type %d\n", *type);

    switch (*type)
    {
    case 1: {
        packetClientInit *packetCInit = malloc(1 * sizeof(packetClientInit));
        memcpy(packetCInit, buffer_in, sizeof(packetClientInit));
        
        //Reponse du serveur a ce packet : Je suis disponible  : ACK
        serverInit(Player, packetCInit);
        
        free(packetCInit);
        break;
    }
     case 2: {
        packetClientWaitingGame *packetCWaitingGame = malloc(1 * sizeof(packetClientWaitingGame));
        memcpy(packetCWaitingGame, buffer_in, sizeof(packetClientWaitingGame));

        serverWaitingEnd(Player, packetCWaitingGame);
        
        free(packetCWaitingGame);
        break;
    }
    case 3: {
        packetClientPlayerReady *packetCPlayerReady = malloc(1 * sizeof(packetClientPlayerReady));
        memcpy(packetCPlayerReady, buffer_in, sizeof(packetClientPlayerReady));

        serverMakeChoice(Player, packetCPlayerReady);

        free(packetCPlayerReady);
        break;
    }
    case 4: {
        packetClientPlayerChoice *packetCPlayerChoice = malloc(1 * sizeof(packetClientPlayerChoice));
        memcpy(packetCPlayerChoice, buffer_in, sizeof(packetClientPlayerChoice));

        serverScore(Player, packetCPlayerChoice);

        free(packetCPlayerChoice);
        break;
    }
    default: {
        perror("Erreur de reception du paquet : type non défini !!!\n");
        break;
    }

    }
}