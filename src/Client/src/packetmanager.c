#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "packetmanager.h"

//Création des paquets client

packetClientInit * createPacketClientInit(int clientID) {
    
    packetClientInit *clientInit;
    clientInit = malloc(1 * sizeof(packetClientInit));     //free() liberer espace

    clientInit->type = 1; //Type 1 Message je suis connecté et je suis le client X
    clientInit->numClient = clientID;

    return clientInit;
}

packetClientWaitingGame * createPacketClientWaitingGame() {

    packetClientWaitingGame *WaitingGame;
    WaitingGame = malloc(1 * sizeof(WaitingGame));

    WaitingGame->type = 2; //Type 2 Je suis en attente d'une partie

    return WaitingGame;
}

packetClientPlayerReady * createPacketClientPlayerReady() {
    
    packetClientPlayerReady *PlayerReady;
    PlayerReady = malloc(1 * sizeof(packetClientPlayerReady));

    PlayerReady->type = 3; //Type 3 Mon Joueur est prêt / pas prêt
    PlayerReady->playerIsReady = true;

    return PlayerReady;
}

packetClientPlayerChoice * createPacketClientPlayerChoice(bool choice) {

    packetClientPlayerChoice *playerChoice;
    playerChoice = malloc(1 * sizeof(packetClientPlayerChoice));

    playerChoice->type = 4; //Type 4 Le choix du joueur est collaborer : 0 ou trahir : 1
    playerChoice->choice = true;

    return playerChoice;

}


//Création des paquets serveur
packetServerInit * createPacketServerInit() {
    
    packetServerInit *serverInit;
    serverInit = malloc(1 * sizeof(packetServerInit));

    serverInit->type = 10; //Type 10 Message Bonjour Client X, la connexion a été établie
    serverInit->ServerReady = true;

    return serverInit;
}

packetServerWaitingEnd * createPacketServerWaitingEnd() {

    packetServerWaitingEnd *WaitingEnd;
    WaitingEnd = malloc(1 * sizeof(packetServerInit));

    WaitingEnd->type = 11; //Type 11 Message Sortez de votre attente SVP une partie va démarrer !

    return WaitingEnd;
}

packetServerIsPlayerReady * createPacketServerIsPlayerReady() {
    
    packetServerIsPlayerReady *IsPlayerReady;
    IsPlayerReady = malloc(1 * sizeof(packetServerIsPlayerReady));

    IsPlayerReady->type = 12; //Type 12 Message Demander a votre joueur si il est prêt

    return IsPlayerReady;
}

packetServerMakeChoice * createPacketServerMakeChoice() {

    packetServerMakeChoice *MakeChoice;
    MakeChoice = malloc(1 * sizeof(packetServerIsPlayerReady));

    MakeChoice->type = 13; //Type 13 Message Faites vos jeux.

    return MakeChoice;

}

packetServerIsThisTheEnd * createPacketServerIsThisTheEnd(bool end){

    packetServerIsThisTheEnd *IsThisTheEnd;
    IsThisTheEnd = malloc(1 * sizeof(packetServerIsThisTheEnd));

    IsThisTheEnd->type = 14; //Type 14 Message Est-ce la fin ?
    IsThisTheEnd->gameEnd = end;
    return IsThisTheEnd;
}

packetServerScore * createPacketServerScore(int score) {

    packetServerScore *Score;
    Score = malloc(1 * sizeof(packetServerScore));

    Score->type = 15; //Type 15 Voici votre score
    Score->score = score;
    return Score;
}

void receivePacket(char *buffer_in) {

    int *type = buffer_in;

    printf("Client received a %d packet", *type);

    switch (*type)
    {
    case 10: {
        packetServerInit *packetSInit = malloc(1 * sizeof(packetServerInit));
        memcpy(packetSInit, buffer_in, sizeof(packetServerInit));
        free(packetSInit);
        break;
    }
    case 11: {
        packetServerWaitingEnd *packetSWaitingEnd = malloc(1 * sizeof(packetServerWaitingEnd));
        memcpy(packetSWaitingEnd, buffer_in, sizeof(packetServerWaitingEnd));
        printf("Fin de l'attente : Demarrage de la partie !");
        serverWaitingEnd();
        free(packetSWaitingEnd);
        break;
    }
    case 12: {
        packetServerIsPlayerReady *packetSIsPlayerReady= malloc(1 * sizeof(packetServerIsPlayerReady));
        memcpy(packetSIsPlayerReady, buffer_in, sizeof(packetServerIsPlayerReady));
        serverIsPlayerReady();
        free(packetSIsPlayerReady);
        break;
    }
    case 13: {
        packetServerMakeChoice *packetSMakeChoice = malloc(1 * sizeof(packetServerMakeChoice));
        memcpy(packetSMakeChoice, buffer_in, sizeof(packetServerMakeChoice));
        serverMakeChoice();
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
        //serverScore();
        free(packetSScore);
        break;
    }
    default: {
        perror("Erreur de reception du paquet : type non défini !!!");
        //printf("%d",type);
        break;
    }

    }
}