/* 
 * Fichier de gestion de l'envoi des données du serveur au client
 * 
 * @autor noeline
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../packetmanager.h"
#include "../srvcxnmanager.h"
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
void serverWaitingEnd(player* Player, packetClientWaitingGame* packetCWaitingGame) {

    printf("Client number %d is waiting\n", Player->ID);
    game* gameToWait = searchGame(Player);
    
/*     if(gameToWait->firstOpponentID == Player->ID) {
        gameToWait->firstPlayerIsReady = true;
    }
    if(gameToWait->secondOpponentID == Player->ID) {
        gameToWait->secondPlayerIsReady = true;
    } */

    setPlayerReady(gameToWait, Player);

    waitGame(gameToWait);

    packetServerWaitingEnd *packetSWaitingEnd = createPacketServerWaitingEnd();
    write(Player->connection->sockfd, packetSWaitingEnd, sizeof (packetSWaitingEnd));

    printf("Server send a waitingEnd packet to Client %d\n", Player->ID);
    
    //WorkArround TODO
    usleep(1000);

    //Reseting Player lock
    gameToWait->firstPlayerIsReady = false;
    gameToWait->secondPlayerIsReady = false;

    printf("Server send a IsPlayerReady packet to Client %d\n", Player->ID);
    serverIsPlayerReady(Player->connection->sockfd);

    free(packetSWaitingEnd);
}

/**
 * @brief Envoi d'un message qui demande au client de jouer
 * 
 * @param Player Joueur à modifier
 * @param packetCPlayerReady Paquet de type clientPlayerReady à traiter 
 */
void serverMakeChoice(player* Player, packetClientPlayerReady* packetCPlayerReady) {

    if(packetCPlayerReady->playerIsReady == true) //Si le joueur est prêt
    {

        
        setPlayerReady(gamePool[Player->lobby], Player); //Stocker le fait quel est prêt
        waitGame(gamePool[Player->lobby]); //Attendre l'autre joueur


        usleep(1000);
        //Reseting Player lock
        gamePool[Player->lobby]->firstPlayerIsReady = false;
        gamePool[Player->lobby]->secondPlayerIsReady = false;

        packetServerMakeChoice *packetSMakeChoice = createPacketServerMakeChoice();
        write(Player->connection->sockfd, packetSMakeChoice, sizeof (packetServerMakeChoice));
        printf("Server send a MakeChoice packet to Client %d\n", Player->ID);
        free(packetSMakeChoice);
    }

}

/**
 * @brief Repond au client par son score
 * 
 * @param Player Joueur pour le quel le score est calculé
 * @param packetCPlayerChoice Paquet reçu contenant le choix
 */
void serverScore(player* Player, packetClientPlayerChoice* packetCPlayerChoice) {
    
    int result = 0;

    printf("Lobby du joueur %d : %d\n", Player->ID, Player->lobby);
    setPlayerReady(gamePool[Player->lobby], Player); //Stocker le fait quel est prêt

    Player->choice = packetCPlayerChoice->choice; //associé le choix au joueur

    waitGame(gamePool[Player->lobby]); //Attendre l'autre joueur
    player* Opponent = getOpponent(Player); //recupérer l'autre joueur

    if(Player->choice == true && Opponent->choice == false) {
        result = 0; //il a dénoncer et l'autre n'a rien dit
    }
    
    if(Player->choice == false && Opponent->choice == false) {
        result = 6; //les 2 n'ont rien dit
    }

    if(Player->choice == true && Opponent->choice == true) {
        result = 5; //les 2 ont dénoncer
    }

    if(Player->choice == false && Opponent->choice == true) {
        result = 10; //l'autre à dénnoncé et lui n'a rien dit 
    }

    printf("Result = %d\n", result);

    usleep(2000);
    //Reseting Player lock
    gamePool[Player->lobby]->firstPlayerIsReady = false;
    gamePool[Player->lobby]->secondPlayerIsReady = false;

    packetServerScore *packetSScore = createPacketServerScore(result);
    write(Player->connection->sockfd, packetSScore, sizeof (packetSScore));
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
/* void serverIsNotThisTheEnd(int sockfd) {
    packetServerIsThisTheEnd *packetSIsThisTheEnd = createPacketServerIsThisTheEnd(0);
    write(sockfd, packetSIsThisTheEnd, sizeof (packetSIsThisTheEnd));
    free(packetSIsThisTheEnd);
} */

/**
 * Envoi d'un message qui indique que le serveur a compris le client et qu'il est prêt
 * 
 * @autor Thomas
 * @param Player Joueur à modifier
 * @param packetCInit Paquet de type clientInit à traiter 
 */
void serverInit(player* Player, packetClientInit* packetCInit) {

    //playerPool[packetCInit->numClient]->connection->sockfd = newSocket;
    Player->ID = packetCInit->numClient;
    
    //playerPool[0].choice = true;

/*     printf("**********Le socket du client est %d\n",Player->connection->sockfd);
    printf("**********Le numClient  est %d\n",Player->ID); */
    printf("Client %d connected\n", Player->ID);
    packetServerInit *packetSInit = createPacketServerInit();
    write(Player->connection->sockfd, packetSInit, sizeof (packetServerInit));
    printf("Server send an ack to client %d\n", Player->ID);
    free(packetSInit);
}
