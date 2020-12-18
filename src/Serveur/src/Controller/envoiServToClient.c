/**
 * @file envoiServToClient.c
 * @author noeline
 * @brief Fichier de gestion de l'envoi des données du serveur au client
 * @version 0.1
 * @date 2020-12-17
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../packetmanager.h"
#include "../srvcxnmanager.h"
#include "receptionClientToServ.h"
#include <unistd.h>

/**
 * @brief Envoi un paquet pour demander si le client est pret
 * 
 * @param sockfd Socket de la connexion
 */
void serverIsPlayerReady(int sockfd) {
    packetServerIsPlayerReady *packetSIsPlayerReady = createPacketServerIsPlayerReady();
    write(sockfd, packetSIsPlayerReady, sizeof (packetSIsPlayerReady));
    free(packetSIsPlayerReady);
}

/**
 * @brief Envoi un paquet pour sortir le client de l'attente
 * 
 * @param Player Joueur à sortir de l'attente
 * @param packetCWaitingGame Dernier paquet reçu du client à traiter
 */
void serverWaitingEnd(player* Player, packetClientWaitingGame* packetCWaitingGame) {

    printf("Client number %d is waiting\n", Player->ID);
    game* gameToWait = searchGame(Player);
    
    //Se souvenir que le joueur est prêt et attendre l'autre joueur
    setPlayerReady(gameToWait, Player);
    waitGame(gameToWait);
    
    if(gamePool[Player->lobby]->roundNumber <=0) { //si il n'y a plus de round
        //Envoi du paquet pour terminer la partie
        packetServerIsThisTheEnd *packetSItIsTheEnd = createPacketServerIsThisTheEnd(true);
        write(Player->connection->sockfd, packetSItIsTheEnd, sizeof (packetServerIsThisTheEnd));
        free(packetSItIsTheEnd);
    }
    else {
        //Envoi du paquet pour commencer le round
        packetServerWaitingEnd *packetSWaitingEnd = createPacketServerWaitingEnd();
        write(Player->connection->sockfd, packetSWaitingEnd, sizeof (packetServerWaitingEnd));
        printf("Server send a waitingEnd packet to Client %d\n", Player->ID);
        free(packetSWaitingEnd);
    }


    //WorkArround Ne pas supprimer !!! 
    usleep(2000);                  ///La désactivation de l'Algorithme de Nagle ne fonctionne pas !
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    //Remise à zéro de l'attente client
    gameToWait->firstPlayerIsReady = false;
    gameToWait->secondPlayerIsReady = false;

    printf("Server send a IsPlayerReady packet to Client %d\n", Player->ID);

    //Envoyer un paquet pour demander si le jouer est prêt
    serverIsPlayerReady(Player->connection->sockfd);
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

        //Se souvenir que le joueur est prêt et attendre l'autre joueur
        setPlayerReady(gamePool[Player->lobby], Player);
        waitGame(gamePool[Player->lobby]);

        //WorkArround Ne pas supprimer !!! 
        usleep(1000);                  ///La désactivation de l'Algorithme de Nagle ne fonctionne pas !
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        //Remise à zéro de l'attente client
        gamePool[Player->lobby]->firstPlayerIsReady = false;
        gamePool[Player->lobby]->secondPlayerIsReady = false;


        //Envoyer le paquet
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
        result = 5; //les 2 ont dénoncés
    }

    if(Player->choice == false && Opponent->choice == true) {
        result = 10; //l'autre à dénnoncé et lui n'a rien dit 
    }

    printf("Result = %d\n", result);

    usleep(2000);
    //Reseting Player lock
    gamePool[Player->lobby]->firstPlayerIsReady = false;
    gamePool[Player->lobby]->secondPlayerIsReady = false;

    //Envoi du paquet
    packetServerScore *packetSScore = createPacketServerScore(result);
    write(Player->connection->sockfd, packetSScore, sizeof (packetServerScore));
    free(packetSScore);

    gamePool[Player->lobby]->roundNumber--;
}


/**
 * @brief Envoi du message de fin de l'experience
 * 
 * @param sockfd Socket de la connexion
 */
void serverIsThisTheEnd(int sockfd) {
    packetServerIsThisTheEnd *packetSIsThisTheEnd = createPacketServerIsThisTheEnd(1);
    write(sockfd, packetSIsThisTheEnd, sizeof (packetSIsThisTheEnd));
    free(packetSIsThisTheEnd);
}

/**
 * @brief Envoi d'un message qui stipule que ce n'est pas la fin
 * 
 * @param sockfd Socket de la connexion
 */
void serverItIsNotTheEnd(int sockfd) {
    packetServerIsThisTheEnd *packetSIsThisTheEnd = createPacketServerIsThisTheEnd(0);
    write(sockfd, packetSIsThisTheEnd, sizeof (packetSIsThisTheEnd));
    free(packetSIsThisTheEnd);
}

/**
 * @brief Envoi d'un message qui indique que le serveur a compris le client et qu'il est prêt
 * 
 * @param Player Joueur à modifier
 * @param packetCInit Paquet de type clientInit à traiter
 */
void serverInit(player* Player, packetClientInit* packetCInit) {

    Player->ID = packetCInit->numClient;
    
    printf("Client %d connected\n", Player->ID);
    packetServerInit *packetSInit = createPacketServerInit();
    write(Player->connection->sockfd, packetSInit, sizeof (packetServerInit));
    printf("Server send an ack to client %d\n", Player->ID);
    free(packetSInit);
}
